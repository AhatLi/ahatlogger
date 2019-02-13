#include "ahatlogger.h"

std::queue< std::pair<std::string, std::string> > *	AhatLogger::q = NULL;
bool			AhatLogger::isStarted = false;
std::string		AhatLogger::path;
std::mutex		AhatLogger::mutex;
int				AhatLogger::level;

std::string code(std::string file, std::string func, int line)
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
		q = new std::queue< std::pair<std::string, std::string> >();
		std::thread t(&AhatLogger::run);
		t.detach();
	}
}

void AhatLogger::stop()
{
	isStarted = false;
}

void AhatLogger::run()
{
	while(isStarted)
	{
		if(q->size() <= 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			continue;
		}
		
		std::ofstream f;
		f.open(path, std::ios::out | std::ios::app);
		
		mutex.lock();

		std::queue< std::pair<std::string, std::string> > *qq = q;
		q = new std::queue< std::pair<std::string, std::string> >();

		mutex.unlock();

		int size = qq->size();
		for(int i = 0; i < size; i++)
		{
			std::pair<std::string, std::string>  item = qq->front();
			qq->pop();

			f << item.first<< "," << getCurTime() << item.second << "\n";
		}
		
		delete qq;
			
		f.close();
	}
}

void AhatLogger::setting(std::string path, int level)
{
	AhatLogger::path = path;
	AhatLogger::level = level;
}

void AhatLogger::INFO(std::string src_file, std::string body)
{
	AhatLogItemInfo log(src_file, body);
	
	mutex.lock();
	AhatLogger::q->push( std::pair<std::string, std::string>("INFO", log.message()));
	mutex.unlock();
}

void AhatLogger::ERROR(std::string src_file, std::string body)
{
	AhatLogItemError log(src_file, body);
	
	mutex.lock();
	AhatLogger::q->push( std::pair<std::string, std::string>("ERROR", log.message()));
	mutex.unlock();
}

void AhatLogger::CUSTOM(std::string src_file, std::string custom, std::string body)
{
	AhatLogItemCustom log(src_file, body);
	
	mutex.lock();
	AhatLogger::q->push( std::pair<std::string, std::string>(custom, log.message()));
	mutex.unlock();
}

void AhatLogger::DEBUG(std::string src_file, std::string body)
{
	if(level < 1)
		return;

	AhatLogItemDebug log(src_file, body);
	
	mutex.lock();
	AhatLogger::q->push( std::pair<std::string, std::string>("DEBUG", log.message()));
	mutex.unlock();
}

void AhatLogger::REQUEST(std::string src_file, std::string req_ip, std::string req_uri)
{
	AhatLogItemRequest log(src_file, req_ip, req_uri, src_file);
	
	mutex.lock();
	AhatLogger::q->push( std::pair<std::string, std::string>("REQUEST", log.message()));
	mutex.unlock();
}
void AhatLogger::RESPONSE(std::string src_file, std::string res_body, std::string res_code)
{
	AhatLogItemResponse log(src_file, res_body, res_code);
	
	mutex.lock();
	AhatLogger::q->push( std::pair<std::string, std::string>("RESPONSE", log.message()));
	mutex.unlock();
}

void AhatLogger::DB(std::string src_file, InDBtem db_req_item, std::string db_res_body)
{
	AhatLogItemDB log(src_file, db_req_item, db_res_body);
	
	mutex.lock();
	AhatLogger::q->push( std::pair<std::string, std::string>("DB", log.message()));
	mutex.unlock();
}
void AhatLogger::DB_ERROR(std::string src_file, InDBtem db_req_item, std::string db_res_body)
{
	AhatLogItemDBError log(src_file, db_req_item, db_res_body);
	
	mutex.lock();
	AhatLogger::q->push( std::pair<std::string, std::string>("DB_ERROR", log.message()));
	mutex.unlock();
}

void AhatLogger::IN_REQ(std::string src_file, InReqItem in_req_item, std::string in_res_body)
{
	AhatLogItemInReq log(src_file, in_req_item, in_res_body);
	
	mutex.lock();
	AhatLogger::q->push( std::pair<std::string, std::string>("IN_REQ", log.message()));
	mutex.unlock();
}

void AhatLogger::IN_REQ_ERR(std::string src_file, InReqItem in_req_item, std::string in_res_body)
{
	AhatLogItemInReqError log(src_file, in_req_item, in_res_body);
	
	mutex.lock();
	AhatLogger::q->push( std::pair<std::string, std::string>("IN_REQ_ERR", log.message()));
	mutex.unlock();
}

