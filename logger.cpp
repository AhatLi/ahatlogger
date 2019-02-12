#include "logger.h"

std::queue< std::string > *AhatLogger::q = NULL;
bool AhatLogger::isStarted = false;
std::string AhatLogger::path;
std::mutex AhatLogger::mutex;

std::string code(const char* file, char* func, int line)
{
	std::stringstream buf;
	buf<<file<<","<<func<<":"<<line;
	return buf.str();
}

void AhatLogger::setting(std::string path)
{
	AhatLogger::path = path;
}

void AhatLogger::info(std::string src_file, std::string body)
{
	AhatLogItemInfo log;
	log.log_time = getCurTime();
	log.body = body;
	log.src_file = src_file;
	
	mutex.lock();
	AhatLogger::q->push(log.message());
	mutex.unlock();
}

void AhatLogger::start()
{
	if(isStarted == false)
	{
		isStarted = true;
		q = new std::queue< std::string >();
		std::thread t(&AhatLogger::run);
		t.detach();
	}
}

void AhatLogger::run()
{
	while(1)
	{
		if(q->size() <= 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			continue;
		}
		
		std::ofstream f;
		f.open(path, std::ios::out | std::ios::app);
		
		mutex.lock();

		std::queue< std::string > *qqq = q;
		q = new std::queue< std::string >();

		mutex.unlock();

		std::cout<<qqq->size()<<"\n";
		int size = qqq->size();
		for(int i = 0; i < size; i++)
		{
			std::string item = qqq->front();
			qqq->pop();
			f << item << "\n";
		}
		
		delete qqq;
			
		f.close();
	}
}

std::string AhatLogger::getCurTime()
{
	std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
	
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()) - std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch());
	
	time -= std::chrono::milliseconds(500);
	time_t tt = std::chrono::system_clock::to_time_t(time);
	struct tm tm;
	localtime_s(&tm, &tt);
 
	char buf[64];
	sprintf_s(buf, "%d-%02d-%02d %02d:%02d:%02d.%03d",tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, ms);

	return std::string(buf);
}

AhatLogItem::AhatLogItem()
{
}

AhatLogItem::~AhatLogItem()
{
}