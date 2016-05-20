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
	send_opt send_info = send_opt_init();
	
	send_info.to = "01048206231";
	send_info.from = "01028866231";
	send_info.text = "테스트 중이여~";
	// send_info.subject = "";
	// send_info.type = "SMS";
	// send_info.image = "image.jpg";
	// send_info.country_code = "82";
	send_info.charset = "euckr";

	result = send_message(&user_info, &send_info);
	print_result(result);

	return 0;
}
#endif