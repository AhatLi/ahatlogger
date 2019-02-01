#include "logger.h"

#include <iostream>
#include <thread>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <time.h>
 
int main()
{
	while(1)
	{

		std::this_thread::sleep_for(std::chrono::milliseconds(400));
		AhatLogger::info();
	}
	
	return 0;
}