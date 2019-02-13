#include "logger.h"

#include <iostream>
#include <thread>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <time.h>

#include <sstream>
 
int main()
{
	AhatLogger::setting("C:\\Users\\castis\\Desktop\\share\\ahat.log", 1);
	AhatLogger::start();

	for(int i = 0; i < 10; i++)
	{
		std::stringstream s;
		s<<"로그입니다 "<<i;
		AhatLogger::INFO(CODE(), s.str());
		AhatLogger::ERROR(CODE(), s.str());
		AhatLogger::DEBUG(CODE(), s.str());
		
		AhatLogger::DB(CODE(),InDBtem("1", "2"), s.str());
		AhatLogger::DB_ERROR(CODE(),InDBtem("1", "2"), s.str());

		AhatLogger::IN_REQ(CODE(),InReqItem("1", "2", "3"), s.str());
		AhatLogger::IN_REQ_ERR(CODE(),InReqItem("1", "2", "3"), s.str());

		AhatLogger::CUSTOM(CODE(), "AHAT", s.str());
	AhatLogger::stop();
	}
	
	return 0;
}