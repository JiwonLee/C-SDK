#include "coolsms.h"

user_opt user_opt_init(char *api_key, char *api_secret)
{
	user_opt user_info = { "\0", "\0", "\0", "\0", "\0", "\0" };
	char *uniq;

	strcpy(user_info.api_key, api_key);
	strcpy(user_info.api_secret, api_secret);
	getTimestamp(user_info.timestamp);
	uniq = getUniq();
	strcpy(user_info.salt, uniq);
	getSignature(user_info.timestamp, user_info.salt, user_info.api_secret, user_info.signature);

	free(uniq);
	return user_info;
}

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	response_struct *mem = (response_struct *)userp;

	mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory == NULL) {
		/* out of memory! */
		printf("not enough memory (realloc returned NULL)\n");
		return 0;
	}

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

/* Process curl */
int curlProcess(bool is_post, char *options, char *path, response_struct *output)
{
	CURL *curl;
	CURLcode res;
	char url[1024];
	struct curl_httppost *formpost = NULL;
	struct curl_httppost *lastptr = NULL;
	struct curl_slist *headerlist = NULL;
	response_struct response;
	response.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
	response.size = 0;    /* no data at this point */
	char *host = "http://rest2.coolsms.co.kr";
	char *api_name = "sms";
	char *api_version = "1.5";

	/* Set url. is_pose true = POST, false = GET */
	if (is_post) {
		sprintf(url, "%s/%s/%s/%s", host, api_name, api_version, path);
	}
	else {
		sprintf(url, "%s/%s/%s/%s?%s", host, api_name, api_version, path, options);
	}

	/* initialize curl */
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		if (is_post)
		{
			curl_easy_setopt(curl, CURLOPT_POST, 1);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, options);
		}
		else
		{
			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
		}
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L); /* CURLOPT_VERBOSE shows infomation about connected server. USEFUL for debugging */
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "REST SDK C&CPP/1.0");
		res = curl_easy_perform(curl);

		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		else
			printf("%lu bytes retrieved\n", (long)response.size);

		/* always cleanup */

		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	*output = response;

	return res;
}

/* Return user's current OS */
char* getOS(char* user_agent)
{
	char* os_platform = "Unknown OS Platform";
	char* os_array[2][25] = { { "/windows nt 10/i", "/windows nt 6.3/i", "/windows nt 6.2/i",
		"/windows nt 6.1/i", "/windows nt 6.0/i", "/windows nt 5.2/i",
		"/windows nt 5.1/i", "/windows xp/i", "/windows nt 5.0/i",
		"/windows me/i", "/win98/i", "/win95/i",
		"/win16/i", "/macintosh|mac os x/i", "/mac_powerpc/i",
		"/linux/i", "/ubuntu/i", "/iphone/i",
		"/ipod/i", "/ipad/i", "/android/i",
		"/blackberry/i", "/webos/i" },
		{ "Windows 10", "Windows 8.1", "Windows 8",
		"Windows 7", "Windows Vista", "Windows Server 2003/XP x64",
		"Windows XP", "Windows XP", "Windows 2000",
		"Windows ME", "Windows 98", "Windows 95",
		"Windwos 3.11", "Mac OS X", "Mac OS 9",
		"Linux", "Ubuntu", "iPhone",
		"iPod", "iPad", "Android",
		"BlackBerry", "Mobile" }
	};
	int i;

	for (i = 0; i < 25; i++) {
		if (user_agent == os_array[0][i]) {
			os_platform = os_array[1][i];
		}
	}

	return os_platform;
}

/* Return user's current browser */
char* getBrowser(char* user_agent) {
	char* browser = "Unknown Browser";
	char* browser_array[2][9] = { { "/msie/i", "/firefox/i", "safari/i",
		"/chrome/i", "/opera/i", "netscape/i",
		"/maxthon/i", "/konqueror/i", "/mobile/i" },
		{ "Internet Explorer", "Firefox", "Safari",
		"Chrome", "Opera", "Netscape",
		"Maxthon", "Konqueror", "Handheld Browser" }
	};
	int i;

	for (i = 0; i < 9; i++) {
		if (user_agent == browser_array[0][i]) {
			browser = browser_array[1][i];
		}
	}

	return browser;
}

void getTimestamp(char *output)
{
	time_t timestamp;
	time(&timestamp);
	sprintf(output, "%d", (int)timestamp);
}

char* getUniq()
{
	struct tm tm_val;
	char *buf;

	buf = (char *)malloc(40);
	memset(buf, 0, sizeof(buf));
	memset(&tm_val, 0, sizeof(tm_val));
#ifdef _WIN32
	SYSTEMTIME st;
	GetLocalTime(&st);
	sprintf(buf, "%u%u%u%u%u%u%u", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
#else
	t = time(NULL);
	(void)localtime_r(&t, &tm_val);
	strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", &tm_val);
#endif

	return buf;
}

void getSignature(const char *datetime, const char *salt, const char * api_secret, char *output)
{
	unsigned char signature[16];
	char data_unsigned[64];
	char * hash_data;
	hash_data = (char*)malloc(strlen(datetime) + strlen(salt) + 1);

	/*hash 예외처리*/
	sprintf(data_unsigned, "%s%s", datetime, salt);
	md5_hmac((unsigned char*)api_secret, strlen(api_secret), (unsigned char*)data_unsigned, strlen(data_unsigned), signature);
	for (int i = 0; i < sizeof(signature); i++)
	{
		sprintf(&output[i * 2], "%02x", signature[i]);
	}
}