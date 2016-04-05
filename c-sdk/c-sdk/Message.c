#include "coolsms.h"
#include "Coolsms.c"

typedef struct { char *to, *from, *text, *type, *image, *image_encoding, *refname, *country, *datetime, *subject, *charset, *srk, *mode, *delay, *force_sms, *os_platform, *dev_lang, *sdk_version, *app_version; } send_opt;
typedef struct { char *offset, *limit, *rcpt, *start, *end, *status, *resultcode, *notin_resultcode, *mid, *gid; } sent_opt;
typedef struct { char *mid, *gid; } cancel_opt;
typedef struct { char *count, *unit, *date, *channel; } status_opt;


response_struct sendMessage(const user_opt *u, const send_opt *s)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&to=%s&from=%s&text=%s&type=%s&image=%s&refname=%s&country=%s&datetime=%s&subject=%s&charset=%s&srk=%s&mode=%s&delay=%s&force_sms=%s&os_platform=%s&dev_lang=%s&sdk_version=%s&app_version=%s",
		u->api_key, u->salt, u->signature, u->timestamp, s->to, s->from, s->text, s->type, s->image, s->refname, s->country, s->datetime, s->subject, s->charset, s->srk, s->mode, s->delay, s->force_sms, s->os_platform, s->dev_lang, s->sdk_version, s->app_version);

	if (curlProcess(true, options, "send", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct sent(const user_opt *u, const sent_opt *s)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&offset=%s&limit=%s&rcpt=%s&start=%s&end=%s&status=%s&resultcode=%s&notin_resultcode=%s&mid=%s&gid=%s",
		u->api_key, u->salt, u->signature, u->timestamp, s->offset, s->limit, s->rcpt, s->start, s->end, s->status, s->resultcode, s->notin_resultcode, s->mid, s->gid);

	if (curlProcess(false, options, "sent", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct cancel(const user_opt *u, const cancel_opt *c)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&mid=%s&gid=%s",
		u->api_key, u->salt, u->signature, u->timestamp, c->mid, c->gid);

	if (curlProcess(true, options, "cancel", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct balance(const user_opt *u)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s",
		u->api_key, u->salt, u->signature, u->timestamp);

	if (curlProcess(true, options, "balance", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct status(const user_opt *u, const status_opt *s)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&count=%s&unit=%s&date=%s&channel=%s",
		u->api_key, u->salt, u->signature, u->timestamp, s->count, s->unit, s->date, s->channel);

	if (curlProcess(true, options, "status", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}