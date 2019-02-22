#include "ahatlogger.h"

std::queue< std::pair<std::string, std::string> > *	AhatLogger::q = NULL;
bool			AhatLogger::isStarted = false;
bool			AhatLogger::isFinished = false;
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
	
	while(1)
	{
		if(isFinished)
			break;
		else
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	
	isFinished = false;
}

void AhatLogger::run()
{
	while(isStarted)
	{
		if(!q->size())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			continue;
		}
		
		logWrite();
	}
	if(q->size())
	{
		logWrite();
	}
	
	isFinished = true;
}

void AhatLogger::logWrite()
{
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

void AhatLogger::setting(std::string path, int level)
{
	AhatLogger::path = path;
	AhatLogger::level = level;
}

void AhatLogger::INFO(std::string src_file, const char* body, ...)
{
    int count = 0;
 
	va_list arglist;
	va_start(arglist, body);

	int len = _vscprintf(body, arglist) + 1;
	char* tmp = new char[len];
	memset(tmp, 0, len);

	vsprintf_s(tmp, len, body, arglist);
	
	AhatLogItemInfo log(src_file, tmp);
	delete tmp;
	va_end(arglist);
	
	mutex.lock();
	AhatLogger::q->push( std::pair<std::string, std::string>("INFO", log.message()));
	mutex.unlock();
}

void AhatLogger::ERROR(std::string src_file, const char* body, ...)
{
    int count = 0;
 
	va_list arglist;
	va_start(arglist, body);

	int len = _vscprintf(body, arglist) + 1;
	char* tmp = new char[len];
	memset(tmp, 0, len);

	vsprintf_s(tmp, len, body, arglist);
	
	AhatLogItemError log(src_file, tmp);
	delete tmp;
	va_end(arglist);
	
	mutex.lock();
	AhatLogger::q->push( std::pair<std::string, std::string>("ERROR", log.message()));
	mutex.unlock();
}

void AhatLogger::CUSTOM(std::string src_file, std::string custom, const char* body, ...)
{
    int count = 0;
 
	va_list arglist;
	va_start(arglist, body);

	int len = _vscprintf(body, arglist) + 1;
	char* tmp = new char[len];
	memset(tmp, 0, len);

	vsprintf_s(tmp, len, body, arglist);
	
	AhatLogItemCustom log(src_file, tmp);
	delete tmp;
	va_end(arglist);
	
	mutex.lock();
	AhatLogger::q->push( std::pair<std::string, std::string>(custom, log.message()));
	mutex.unlock();
}

//로그레벨 0이면 로그를 작성 그 이상은 작성하지 않음
void AhatLogger::DEBUG(std::string src_file, const char* body, ...)
{
	if(level <= 1)
		return;
	
    int count = 0;
 
	va_list arglist;
	va_start(arglist, body);

	int len = _vscprintf(body, arglist) + 1;
	char* tmp = new char[len];
	memset(tmp, 0, len);

	vsprintf_s(tmp, len, body, arglist);
	
	AhatLogItemDebug log(src_file, tmp);
	delete tmp;
	va_end(arglist);
	
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

#ifdef __linux__
int _vscprintf (const char * format, va_list pargs) 
{ 
    int retval; 
    va_list argcopy; 
    va_copy(argcopy, pargs); 
	
    retval = vsnprintf(NULL, 0, format, argcopy); 
    va_end(argcopy); 
    return retval; 
}
#endif