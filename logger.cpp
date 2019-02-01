#include "logger.h"

std::queue< std::shared_ptr<AhatLogItem> > *AhatLogger::q = NULL;

void AhatLogger::info()
{
	std::shared_ptr<AhatLogItem> item(new AhatLogItemInfo());
	AhatLogger::q->push(item);
	
	std::cout<<"thread id = "<<std::this_thread::get_id()<<"\n";
//	std::cout<<"log_time = "<<getCurTime()<<"\n";
}

void AhatLogger::start()
{
	q = new std::queue< std::shared_ptr<AhatLogItem> >();
	std::thread t(&AhatLogger::run);
	t.detach();
}

void AhatLogger::run()
{
	while(1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::cout<<AhatLogger::q->size()<<"\n";
	}
}


std::string getCurTime()
{
	std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
	
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()) -
				std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch());
	
	time -= std::chrono::milliseconds(500);
	time_t tt = std::chrono::system_clock::to_time_t(time );
	struct tm tm;
	localtime_s(&tm, &tt);
 
	char buf[64];
	sprintf_s(buf, "%d-%02d-%02d %02d:%02d:%02d.%03d\n",
		tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
		tm.tm_hour, tm.tm_min, tm.tm_sec, ms);

	return std::string(buf);
}