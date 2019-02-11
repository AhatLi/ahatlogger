#include "logger.h"

std::queue< std::shared_ptr<AhatLogItem> > *AhatLogger::q = NULL;
bool AhatLogger::isStarted = false;
std::string AhatLogger::path;

std::string awhere(const char* file, char* func, int line)
{
	std::stringstream aa;
	aa<<file<<","<<func<<":"<<line;
	return aa.str();
}

void AhatLogger::setting(std::string path)
{
	AhatLogger::path = path;
}

void AhatLogger::info(std::string src_file, std::string body)
{
	src_file = WHERE();
	std::shared_ptr<AhatLogItemInfo> item(new AhatLogItemInfo());

//	std::static_pointer_cast<AhatLogItemInfo>(item)->body = body;

	item->body = body;

	item->thread_id = std::this_thread::get_id();
	item->getCurTime();
	item->src_name = src_file;
//	item->src_line = line;
//	item->src_func = func;
	item->log_type = "INFO";

	AhatLogger::q->push(item);
}

void AhatLogger::start()
{
	if(isStarted == false)
	{
		isStarted = true;
		q = new std::queue< std::shared_ptr<AhatLogItem> >();
		std::thread t(&AhatLogger::run);
		t.detach();
	}
}

void AhatLogger::run()
{
	while(1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout<<AhatLogger::q->size()<<"\n";

		if(q->size() <= 0)
			continue;

		std::shared_ptr<AhatLogItem> item = q->back();
		
		std::ofstream f;
		f.open(path, std::ios::out | std::ios::app);
		
		{


			auto item2 = std::static_pointer_cast<AhatLogItemInfo>(item);
			f << item->log_type << "," << item->log_time << "," << item->src_name << "," << item->thread_id << "," << item2->body << "\n";
		}
		f.close();
	}
}

void AhatLogger::infoWrite(std::shared_ptr<AhatLogItemInfo> item, std::ofstream f)
{
}


void AhatLogItem::getCurTime()
{
	std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
	
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()) - std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch());
	
	time -= std::chrono::milliseconds(500);
	time_t tt = std::chrono::system_clock::to_time_t(time);
	struct tm tm;
	localtime_s(&tm, &tt);
 
	char buf[64];
	sprintf_s(buf, "%d-%02d-%02d %02d:%02d:%02d.%03d",tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, ms);

	this->log_time = (char*)malloc(strlen(buf)+1);
	sprintf_s(this->log_time, strlen(buf) + 1, "%d-%02d-%02d %02d:%02d:%02d.%03d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, ms);
}

AhatLogItem::AhatLogItem()
{
	log_time = NULL;
}

AhatLogItem::~AhatLogItem()
{
//	std::string thread_name;

	if(log_time != NULL)
	{
		free(log_time);
		log_time = NULL;
	}

//	std::string src_name;
//	std::string src_line;
//	std::string src_func;
//	std::string log_type;
}