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
	cancel_opt cancel_info = cancel_opt_init();

	/* set send infomations
	More info found at http://doc.coolsms.co.kr?page_id=1811 */
	// cancel_info.gid = "GROUP_ID";
	cancel_info.mid = "R1M57338255D8";

	result = cancel(&user_info, &cancel_info);
	print_result(result);

	return 0;
}
#endif