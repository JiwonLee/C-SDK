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
	send_group_opt send_group_info = send_group_opt_init();

	send_group_info.group_id = "GID573D2CD5BDFED";

	result = send_group(&user_info, &send_group_info);
	print_result(result);

	return 0;
}
#endif 