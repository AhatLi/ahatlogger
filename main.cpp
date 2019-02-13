#include "ahatlogger.h"

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
	AhatLogger::setting("ahat.log", 1);
	AhatLogger::start();

	for(int i = 0; i < 1; i++)
	{
		std::stringstream s;
		s<<"wwwww"<<i;
		AhatLogger::INFO(CODE, s.str());
		AhatLogger::ERROR(CODE, s.str());
		AhatLogger::DEBUG(CODE, s.str());
		
		AhatLogger::DB(CODE,InDBtem("1", "2"), s.str());
		AhatLogger::DB_ERROR(CODE,InDBtem("1", "2"), s.str());

		AhatLogger::IN_REQ(CODE,InReqItem("1", "2", "3"), s.str());
		AhatLogger::IN_REQ_ERR(CODE,InReqItem("1", "2", "3"), s.str());

		AhatLogger::CUSTOM(CODE, "AHAT", s.str());
	}
	std::cout<<"³¡\n";
	getchar();
	return 0;
}