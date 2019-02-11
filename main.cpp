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
	std::stringstream aa;
	aa<<"1111"<<333<<5454<<"3333";
	aa.str();


	while(1)
	{
		AhatLogger::setting("C:\\Users\\castis\\Desktop\\share\\ahat.log");
		AhatLogger::start();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		AhatLogger::info(WHERE(), "ttt");
	}
	
	return 0;
}