#include "coolsms.h"

user_opt user_opt_init(char *api_key, char *api_secret)
{
	user_opt user_info = { "\0", "\0", "\0", "\0", "\0", "\0" };
	char *uniq;
	char *salt = (char*)malloc(2 * 20 + 1);
	char *buf_ptr = salt;

	user_info.api_key = api_key;
	user_info.api_secret = api_secret;
	user_info.timestamp = get_timestamp();
	uniq = get_uniq();
	buf_ptr += sprintf(buf_ptr, "%s", uniq);
	user_info.salt = salt;
	user_info.signature = get_signature(user_info.timestamp, user_info.salt, user_info.api_secret);
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
int curl_process(bool is_post, char *options, char *path, char *api_name, response_struct *output)
{
	CURL *curl;
	CURLcode res;
	char url[1024];
	struct curl_slist *headerlist = NULL;
	response_struct response;
	response.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */
	response.size = 0;    /* no data at this point */
	char *host = "http://api.coolsms.co.kr";
	char *api_version = "\0";

	if (api_name == "sms") {
		api_version = "2";
	} else {
		api_version = "1.1";
	}

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

char* time_to_string(const time_t time) {
	char *output;
	char *buf_str = malloc(sizeof(time) * 2 + 1);
	char *buf_ptr = buf_str;
	buf_ptr += sprintf(buf_ptr, "%d", (int)time);
	output = buf_str;

	return output;
}

char* get_timestamp()
{
	char *output;
	time_t timestamp;

	time(&timestamp);
	output = time_to_string(timestamp);

	return output;
}

char* get_uniq()
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

char* get_signature(const char *datetime, const char *salt, const char *api_secret)
{
	char *output;
	unsigned char signature[16];
	char data_unsigned[64];
	char * hash_data;
	hash_data = (char*)malloc(strlen(datetime) + strlen(salt) + 1);
	/*hash 예외처리*/
	sprintf(data_unsigned, "%s%s", datetime, salt);
	md5_hmac((unsigned char*)api_secret, strlen(api_secret), (unsigned char*)data_unsigned, strlen(data_unsigned), signature);

	char* buf_str = (char*)malloc(2 * sizeof(signature) + 1);
	char *buf_ptr = buf_str;
	for (int i = 0; i < sizeof(signature); i++)
	{
		buf_ptr += sprintf(buf_ptr, "%02x", signature[i]);
	}
	output = buf_str;
	
	return output;
}

void print_result(response_struct result)
{
	/* parsing json results */
	json_error_t error;
	json_t *root;
	root = json_loads(result.memory, 0, &error);
	if (!root) {
		fprintf(stderr, "error : root\n");
		fprintf(stderr, "error : online %d: %s\n", error.line, error.text);
		exit(1);
	}

	/* print keys and its values */
	json_t *data, *obj, *array;
	const char * key;
	int i;
	json_object_foreach(root, key, obj) {
		printf("%s:", key);
		data = json_object_get(root, key);
		if (!json_is_array(data))
			printf("%s\n", json_dumps(data, JSON_ENCODE_ANY));

		json_array_foreach(obj, i, array) {
			printf("%s:\n", json_dumps(array, JSON_ENCODE_ANY));
		}
	}

	/* Jansson library is used for parsing JSON data
	More info found at https://jansson.readthedocs.org/en/2.5/ */
}