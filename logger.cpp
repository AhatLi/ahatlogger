#include "logger.h"

std::queue< std::string > *	AhatLogger::q = NULL;
bool						AhatLogger::isStarted = false;
std::string					AhatLogger::path;
std::mutex					AhatLogger::mutex;
int							AhatLogger::level;

std::string code(const char* file, char* func, int line)
{
	std::stringstream buf;
	buf<<file<<","<<func<<":"<<line;
	return buf.str();
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

std::string getCurTime()
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

InDBtem::InDBtem(std::string db_req_func, std::string db_req_body)
{
	this->db_req_time = getCurTime();
	this->db_req_func = db_req_func;
	this->db_req_body = db_req_body;
}

InDBtem::InDBtem(std::string db_req_func)
{
	this->db_req_time = getCurTime();
	this->db_req_func = db_req_func;
	this->db_req_body = "";
}

InReqItem::InReqItem(std::string in_req_ip, std::string in_req_port, std::string in_req_url, std::string in_req_body)
{
	this->in_req_time = getCurTime();
	this->in_req_ip = in_req_ip;
	this->in_req_port = in_req_port;
	this->in_req_url = in_req_url;
	this->in_req_body = in_req_body;
}

InReqItem::InReqItem(std::string in_req_ip, std::string in_req_port, std::string in_req_url)
{
	this->in_req_time = getCurTime();
	this->in_req_ip = in_req_ip;
	this->in_req_port = in_req_port;
	this->in_req_url = in_req_url;
	this->in_req_body = "";
}

void AhatLogger::setting(std::string path, int level)
{
	AhatLogger::path = path;
	AhatLogger::level = level;
}

void AhatLogger::INFO(std::string src_file, std::string body)
{
	AhatLogItemInfo log;
	log.log_time = getCurTime();
	log.body = body;
	log.src_file = src_file;
	
	mutex.lock();
	AhatLogger::q->push(log.message());
	mutex.unlock();
}

void AhatLogger::ERROR(std::string src_file, std::string body)
{
	AhatLogItemInfo log;
	log.log_time = getCurTime();
	log.body = body;
	log.src_file = src_file;
	
	mutex.lock();
	AhatLogger::q->push(log.message());
	mutex.unlock();
}

void AhatLogger::DEBUG(std::string src_file, std::string body)
{
	AhatLogItemDebug log;
	log.log_time = getCurTime();
	log.body = body;
	log.src_file = src_file;
	
	mutex.lock();
	AhatLogger::q->push(log.message());
	mutex.unlock();
}

void AhatLogger::REQUEST(std::string src_file, std::string req_ip, std::string req_uri)
{
	AhatLogItemRequest log;
	log.log_time = getCurTime();
	log.req_ip = req_ip;
	log.req_uri = req_uri;
	log.src_file = src_file;
	
	mutex.lock();
	AhatLogger::q->push(log.message());
	mutex.unlock();
}
void AhatLogger::RESPONSE(std::string src_file, std::string res_body, std::string res_code)
{
	AhatLogItemResponse log;
	log.log_time = getCurTime();
	log.body = body;
	log.src_file = src_file;
	
	mutex.lock();
	AhatLogger::q->push(log.message());
	mutex.unlock();
}

void AhatLogger::DB(std::string src_file, InDBtem db_req_item, std::string db_res_time, std::string db_res_body)
{
	AhatLogItemDB log;
	log.log_time = getCurTime();
	log.body = body;
	log.src_file = src_file;
	
	mutex.lock();
	AhatLogger::q->push(log.message());
	mutex.unlock();
}
void AhatLogger::DB_ERROR(std::string src_file, InDBtem db_req_item, std::string db_res_body)
{
	AhatLogItemDBError log;
	log.log_time = getCurTime();
	log.body = body;
	log.src_file = src_file;
	
	mutex.lock();
	AhatLogger::q->push(log.message());
	mutex.unlock();
}

void AhatLogger::IN_REQ(std::string src_file, InReqItem in_req_item, std::string in_res_body)
{
	AhatLogItemInReq log;
	log.log_time = getCurTime();
	log.body = body;
	log.src_file = src_file;
	
	mutex.lock();
	AhatLogger::q->push(log.message());
	mutex.unlock();
}

void AhatLogger::IN_REQ_ERR(std::string src_file, InReqItem in_req_item, std::string in_res_body)
{
	AhatLogItemInReqError log;
	log.log_time = getCurTime();
	log.body = body;
	log.src_file = src_file;
	
	mutex.lock();
	AhatLogger::q->push(log.message());
	mutex.unlock();
}