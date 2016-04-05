#include "coolsms.h"
#include "Coolsms.c"

typedef struct { char *image, *encoding; } upload_image_opt;
typedef struct { char *offset, *limit; } image_list_opt;
typedef struct { char *image_ids; } delete_images_opt;

response_struct uploadImage(const user_opt *u, const upload_image_opt *i)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&image=%s&encoding=%s",
		u->api_key, u->salt, u->signature, u->timestamp, i->image, i->encoding);

	if (curlProcess(true, options, "upload_image", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct imageInfo(const user_opt *u)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s",
		u->api_key, u->salt, u->signature, u->timestamp);

	if (curlProcess(false, options, "image_info", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct imageList(const user_opt *u, const image_list_opt *i)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&offset=%s&limit=%s",
		u->api_key, u->salt, u->signature, u->timestamp, i->offset, i->limit);

	if (curlProcess(false, options, "image_list", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}

response_struct deleteImages(const user_opt *u, const delete_images_opt *i)
{
	char options[1024];
	response_struct output;

	sprintf(options, "api_key=%s&salt=%s&signature=%s&timestamp=%s&image_ids=%s",
		u->api_key, u->salt, u->signature, u->timestamp, i->image_ids);

	if (curlProcess(true, options, "delete_images", &output) == CURLE_OK)
		printf("\nSuccess!\n");
	else
		printf("\nError!\n");

	return output;
}