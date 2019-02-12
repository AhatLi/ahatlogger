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

	for(int i = 0; i < 100000; i++)
	{
		AhatLogger::INFO(CODE(), "ttt");
		AhatLogger::INFO(CODE(), "로그입니다 로그");
	}
	
	return 0;
}