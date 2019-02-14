#include <ahatlogger.h>

#include <iostream>
#include <sstream>
 
int main()
{
	AhatLogger::setting("ahat.log", 1);
	AhatLogger::start();

	for(int i = 0; i < 100; i++)
	{
		std::stringstream s;
		s<<"sample  "<<i;
		AhatLogger::INFO(CODE, s.str());
		AhatLogger::ERROR(CODE, s.str());
		AhatLogger::DEBUG(CODE, s.str());
		
		AhatLogger::DB(CODE,InDBtem("db_req_func", "db_req_body"), s.str());
		AhatLogger::DB_ERROR(CODE,InDBtem("db_req_func", "db_req_body"), s.str());

		AhatLogger::IN_REQ(CODE,InReqItem("in_req_ip", "in_req_port", "in_req_url", "in_req_body"), s.str());
		AhatLogger::IN_REQ_ERR(CODE,InReqItem("in_req_ip", "in_req_port", "in_req_url", "in_req_body"), s.str());

		AhatLogger::CUSTOM(CODE, "AHAT", s.str());
	}
	AhatLogger::stop();
	return 0;
}
