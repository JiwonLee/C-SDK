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
	image_list_opt image_list_info = image_list_opt_init();

	image_list_info.offset = "0";
	image_list_info.limit = "20";

	result = image_list(&user_info, &image_list_info);
	print_result(result);

	return 0;
}
#endif