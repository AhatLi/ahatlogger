#ifndef AHATLOGGER_H_
#define AHATLOGGER_H_

#include <iostream>
#include <thread>
#include <string>
#include <queue>
#include <memory>
#include <chrono>
#include <thread>
#include <mutex>

#include <iostream>
#include <fstream>
#include <sstream>

#include <fcntl.h>
#include <io.h>

#define AHAT_LOG_INFO 1
#define AHAT_LOG_ERROR 2
#define AHAT_LOG_REQUEST 3
#define AHAT_LOG_RESPONSE 4
#define AHAT_LOG_DB 5
#define AHAT_LOG_DB_ERROR 6
#define AHAT_LOG_IN_REQ 7
#define AHAT_LOG_IN_REQ_ERROR 8
#define AHAT_LOG_DEBUG 9

#define __FILENAME__    strrchr(__FILE__, '\\') +1

#define WHERE() code(__FILENAME__, __FUNCTION__, __LINE__)

std::string code(const char* file, char* func, int line);


class AhatLogger
{
private:
	static std::string path;

	static std::string name;
	static std::string version;
	static std::string host;
	
	static std::queue< std::string > *q;

	static bool isStarted;
	
	static std::string getCurTime();

public:
	static std::mutex mutex;
	
	static void setting(std::string _path);
	static void run();
	static void info(std::string src_file, std::string body);
	static void start();

};



class AhatLogItem
{
public:
	std::string log_time;
	std::string src_file;
	int log_type;

	AhatLogItem();
	~AhatLogItem();

	std::string message() {};
};	

class AhatLogItemInfo : public AhatLogItem
{
public:
	std::string body;

	std::string message()
	{
		std::stringstream aa;
		aa << "INFO," << log_time << "," << src_file << "," << std::this_thread::get_id() << "," << body;
	
		return aa.str();
	};
};
/*
class AhatLogItemError : public AhatLogItem
{
	std::string body;
};

class AhatLogItemRequest : public AhatLogItem
{
	std::string req_ip;
	std::string req_uri;
	std::string req_time;
	
	std::string req_body;
};

class AhatLogItemResponse : public AhatLogItem
{
	std::string req_ip;
	std::string req_uri;
	std::string req_time;

	std::string res_body;
	std::string res_code;
};

class AhatLogItemDB : public AhatLogItem
{
	std::string db_req_time;
	std::string db_res_time;
	std::string db_req_func;
	std::string db_req_body;
	std::string db_res_body;
};

class AhatLogItemDBError : public AhatLogItem
{
	std::string db_req_time;
	std::string db_res_time;
	std::string db_req_func;
	std::string db_req_body;
	std::string db_res_body;
};

class AhatLogItemInReq : public AhatLogItem
{
	std::string in_req_ip;
	std::string in_req_port;
	std::string in_req_url;
	std::string in_req_time;
	std::string in_res_time;
	std::string in_req_body;
	std::string in_res_body;
};

class AhatLogItemInReqError : public AhatLogItem
{
	std::string in_req_ip;
	std::string in_req_port;
	std::string in_req_url;
	std::string in_req_time;
	std::string in_res_time;
	std::string in_req_body;
	std::string in_res_body;
};

class AhatLogItemDebug : public AhatLogItem
{
	std::string body;
};
*/
#endif