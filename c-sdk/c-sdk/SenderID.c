#include "coolsms.h"
#include "Coolsms.c"

typedef struct { char * phone, *site_user; } register_opt;
typedef struct { char * handle_key; } verify_opt;
typedef struct { char * handle_key; } delete_opt;
typedef struct { char * site_user; } list_opt;
typedef struct { char * site_user; } get_default_opt;
typedef struct { char * handle_key, *site_user; } set_default_opt;

response_struct registerSender(const user_opt *u, const register_opt *s)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&phone=%s&site_user=%s",
		u->api_key, u->salt, u->signature, u->timestamp, s->phone, s->site_user);

	if (curlProcess(true, options, "register", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct verify(const user_opt *u, const verify_opt *s)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&handle_key=%s",
		u->api_key, u->salt, u->signature, u->timestamp, s->handle_key);

	if (curlProcess(true, options, "verify", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct deleteSender(const user_opt *u, const delete_opt *s)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&handle_key=%s",
		u->api_key, u->salt, u->signature, u->timestamp, s->handle_key);

	if (curlProcess(true, options, "delete", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct list(const user_opt *u, const list_opt *s)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&site_user=%s",
		u->api_key, u->salt, u->signature, u->timestamp, s->site_user);

	if (curlProcess(false, options, "list", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct setDefault(const user_opt *u, const set_default_opt *s)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&handle_key=%s&site_user=%s",
		u->api_key, u->salt, u->signature, u->timestamp, s->handle_key, s->site_user);

	if (curlProcess(true, options, "set_default", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct getDefault(const user_opt *u, const get_default_opt *s)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&site_user=%s",
		u->api_key, u->salt, u->signature, u->timestamp, s->site_user);

	if (curlProcess(false, options, "get_default", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}