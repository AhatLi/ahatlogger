#include <ahatlogger.h>

#include <iostream>
 
int main()
{
	//setting( logfile path, loglevel )   loglevel 0 print debug log
	AhatLogger::setting("ahat.log", 1); 
	AhatLogger::start();

	for(int i = 0; i < 10; i++)
	{
		AhatLogger::INFO(CODE, "infolog 1 %d, 2 %f, 3 %c, 4 %s, 5 %.2f", i, 3.14, 'a', "ahatlogger", 1.23456789);
		AhatLogger::ERROR(CODE, "errorlog 1 %d, 2 %f, 3 %c, 4 %s, 5 %.2f", i, 3.14, 'a', "ahatlogger", 1.23456789);
		AhatLogger::DEBUG(CODE, "debuglog 1 %d, 2 %f, 3 %c, 4 %s, 5 %.2f", i, 3.14, 'a', "ahatlogger", 1.23456789);

		AhatLogger::CUSTOM(CODE, "AHAT", "debuglog 1 %d, 2 %f, 3 %c, 4 %s, 5 %.2f", i, 3.14, 'a', "ahatlogger", 1.23456789);
		
		InDBtem dbitem("db_req_func", "db_req_body");
		//DB Request process
		AhatLogger::DB(CODE, dbitem, "db_res_body");
		AhatLogger::DB_ERROR(CODE, dbitem, "db_res_body");

		InReqItem reqitem("in_req_ip", "in_req_port", "in_req_url", "in_req_body");
		//Network Request process
		AhatLogger::IN_REQ(CODE, reqitem, "in_res_body");
		AhatLogger::IN_REQ_ERR(CODE, reqitem, "in_res_body");
	}
	AhatLogger::stop();
	return 0;
}
