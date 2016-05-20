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
	new_group_opt new_group_info = new_group_opt_init();

	// new_group_info.charset = "utf8 ";
	// new_group_info.srk = "";
	// new_group_info.mode = "test";
	// new_group_info.delay = 10;
	// new_group_info.force_sms = true;
	// new_group_info.app_version = "";

	result = create_group(&user_info, &new_group_info);
	print_result(result);

	return 0;
}
#endif