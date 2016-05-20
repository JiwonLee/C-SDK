#include "coolsms.h"

/* Set 1 to test example */
#if 0
int main()
{
	/* api_key and api_secret can be obtained from http://www.coolsms.co.kr */
	response_struct result;
	char *api_key = "NCS55F7C0B9269DB";
	char *api_secret = "D2ED4C0E5C55D59F33E74484E89F232B";
	user_opt user_info = user_opt_init(api_key, api_secret);
	upload_image_opt upload_image_info = upload_image_opt_init();
	FILE *image_file = fopen("test.jpg", "rb");

	fseek(image_file, 0, SEEK_END);
	int len = ftell(image_file);
	fseek(image_file, 0, SEEK_SET);
	char *buf = (char*)malloc(len);
	fread(buf, len, 1, image_file);
	fclose(image_file);
	
	upload_image_info.image = buf;
	// upload_image_info.encoding = "binary";

	result = upload_image(&user_info, &upload_image_info);
	print_result(result);

	return 0;
}
#endif