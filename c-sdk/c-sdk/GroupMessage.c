#include "coolsms.h"

typedef struct { char *charset, *srk, *mode, *delay, *force_sms, *os_platform, *dev_lang, *sdk_version, *app_version; } new_group_opt;
typedef struct { char *group_id; } group_info_opt;
typedef struct { char *group_ids; } delete_groups_opt;
typedef struct { char *to, *from, *text, *type, *image_id, *refname, *country, *datetime, *subject, *delay; } add_messages_opt;
typedef struct { char *messages; } add_messages_json_opt;
typedef struct { char *offset, *limit; } message_list_opt;
typedef struct { char *message_ids; } delete_messages_opt;
typedef struct { char *group_id; } send_group_opt;

new_group_opt new_group_opt_init() {
	new_group_opt group_info = { "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0" };

	return group_info;
}

group_info_opt group_info_opt_init() {
	group_info_opt group_info = { "\0" };

	return group_info;
}

delete_groups_opt delete_groups_opt_init() {
	delete_groups_opt group_info = { "\0" };

	return group_info;
}

add_messages_opt add_messages_opt_init() {
	add_messages_opt message_info = { "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0", "\0" };

	return message_info;
}

add_messages_json_opt add_messages_json_opt_init() {
	add_messages_json_opt message_info = { "\0" };

	return message_info;
}

message_list_opt message_list_opt_init() {
	message_list_opt message_info = { "\0", "\0" };

	return message_info;
}

delete_messages_opt delete_messages_opt_init() {
	delete_messages_opt message_info = { "\0" };

	return message_info;
}

send_group_opt send_group_opt_init() {
	send_group_opt group_info = { "\0" };

	return group_info;
}

response_struct newGroup(const user_opt *u, const new_group_opt *g)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&charset=%s&srk=%s&mode=%s&delay=%s&force_sms=%s&os_platform=%s&dev_lang=%s&sdk_version=%s&app_version=%s",
		u->api_key, u->salt, u->signature, u->timestamp, g->charset, g->srk, g->mode, g->delay, g->force_sms, g->os_platform, g->dev_lang, g->sdk_version, g->app_version);

	if (curlProcess(false, options, "new_group", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct groupList(const user_opt *u)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s",
		u->api_key, u->salt, u->signature, u->timestamp);

	if (curlProcess(false, options, "group_list", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct groupInfo(const user_opt *u, const group_info_opt *g)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&group_id=%s",
		u->api_key, u->salt, u->signature, u->timestamp, g->group_id);

	if (curlProcess(false, options, "group_info", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct deleteGroups(const user_opt *u, const delete_groups_opt *g)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&group_ids=%s",
		u->api_key, u->salt, u->signature, u->timestamp, g->group_ids);

	if (curlProcess(true, options, "delete_groups", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct addMessages(const user_opt *u, const add_messages_opt *m)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&to=%s&from=%s&text=%s&type=%s&image_id=%s&refname=%s&country=%s&datetime=%s&subject=%s&delay=%s",
		u->api_key, u->salt, u->signature, u->timestamp, m->to, m->from, m->text, m->type, m->image_id, m->refname, m->country, m->datetime, m->subject, m->delay);

	if (curlProcess(true, options, "add_messages", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct addMessagesJson(const user_opt *u, const add_messages_json_opt *m)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&messages=%s",
		u->api_key, u->salt, u->signature, u->timestamp, m->messages);

	if (curlProcess(true, options, "add_messages_json", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct messageList(const user_opt *u, const message_list_opt *m)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&offset=%s&limit=%s",
		u->api_key, u->salt, u->signature, u->timestamp, m->offset, m->limit);

	if (curlProcess(false, options, "message_list", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct deleteMessages(const user_opt *u, const delete_messages_opt *m)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&message_ids=%s",
		u->api_key, u->salt, u->signature, u->timestamp, m->message_ids);

	if (curlProcess(true, options, "delete_messages", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct sendGroup(const user_opt *u, const send_group_opt *g)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&group_id=%s",
		u->api_key, u->salt, u->signature, u->timestamp, g->group_id);

	if (curlProcess(true, options, "send", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

