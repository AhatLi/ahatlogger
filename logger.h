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

#define __FILENAME__    strrchr(__FILE__, '\\') +1

#define CODE() code(__FILENAME__, __FUNCTION__, __LINE__)

std::string code(const char* file, char* func, int line);

std::string getCurTime();

class AhatLogger
{
private:
	static std::string path;

	static std::string name;
	static std::string version;
	static std::string host;
	
	static std::queue< std::string > *q;
	static bool isStarted;
	static int level;

	static void run();
public:
	static std::mutex mutex;
	
	static void setting(std::string path, int level);
	static void start();
	
	static void INFO(std::string src_file, std::string body);
	static void ERROR(std::string src_file, std::string body);
	static void DEBUG(std::string src_file, std::string body);

	static void REQUEST(std::string src_file, std::string req_ip, std::string req_uri);
	static void RESPONSE(std::string src_file, std::string res_body, std::string res_code);

	static void DB(std::string src_file, InDBtem db_req_item, std::string db_res_time, std::string db_res_body);
	static void DB_ERROR(std::string src_file, InDBtem db_req_item, std::string db_res_body);
	
	static void IN_REQ(std::string src_file, InReqItem in_req_item, std::string in_res_body);
	static void IN_REQ_ERR(std::string src_file, InReqItem in_req_item, std::string in_res_body);
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
		std::stringstream buf;
		buf << "INFO," << log_time << "," << src_file << "," << std::this_thread::get_id() << "," << body;
	
		return buf.str();
	};
};
class AhatLogItemError : public AhatLogItem
{
public:
	std::string body;

	std::string message()
	{
		std::stringstream buf;
		buf << "ERROR," << log_time << "," << src_file << "," << std::this_thread::get_id() << "," << body;
	
		return buf.str();
	};
};

class AhatLogItemRequest : public AhatLogItem
{
public:
	std::string req_ip;
	std::string req_uri;
	
	std::string req_body;

	std::string message()
	{
		std::stringstream buf;
		buf << "REQEUSET," << log_time << "," << src_file << "," << std::this_thread::get_id() << "," << req_ip << "," << req_uri << "," << req_body;
	
		return buf.str();
	};
};

class AhatLogItemResponse : public AhatLogItem
{
public:
	std::string res_body;
	std::string res_code;

	std::string message()
	{
		std::stringstream buf;
		buf << "RESPONSE," << log_time << "," << src_file << "," << std::this_thread::get_id() << "," << res_code << "," << res_body;
	
		return buf.str();
	};
};

class InDBtem
{
public:
	std::string db_req_time;
	std::string db_req_func;
	std::string db_req_body;
	
	InDBtem(std::string db_req_func, std::string db_req_body);
	InDBtem(std::string db_req_func);
};

class AhatLogItemDB : public AhatLogItem
{
public:
	InDBtem db_req_item;
	std::string db_res_time;
	std::string db_res_body;

	std::string message()
	{
		std::stringstream buf;
		buf << "DB," << log_time << "," << src_file << "," << std::this_thread::get_id() << "," << db_req_item.db_req_time << "," << db_res_time 
			<< "," << db_req_item.db_req_func << "," << db_req_item.db_req_body << "," << db_res_body;
	
		return buf.str();
	};
};

class AhatLogItemDBError : public AhatLogItem
{
public:
	InDBtem db_req_item;
	std::string db_res_time;
	std::string db_res_body;

	std::string message()
	{
		std::stringstream buf;
		buf << "DB_ERROR," << log_time << "," << src_file << "," << std::this_thread::get_id() << "," << db_req_item.db_req_time << "," << db_res_time 
			<< "," << db_req_item.db_req_func << "," << db_req_item.db_req_body << "," << db_res_body;
	
		return buf.str();
	};
};

class InReqItem
{
public:
	std::string in_req_ip;
	std::string in_req_port;
	std::string in_req_url;
	std::string in_req_time;
	std::string in_req_body;
	
	InReqItem(std::string in_req_ip, std::string in_req_port, std::string in_req_url, std::string in_req_body);
	InReqItem(std::string in_req_ip, std::string in_req_port, std::string in_req_url);
};

class AhatLogItemInReq : public AhatLogItem
{
public:
	InReqItem in_req_item;
	std::string in_res_time;
	std::string in_res_body;

	std::string message()
	{
		std::stringstream buf;
		buf << "IN_REQ," << log_time << "," << src_file << "," << std::this_thread::get_id() << "," << in_req_item.in_req_ip << "," << in_req_item.in_req_port 
			<< "," << in_req_item.in_req_url << "," << in_req_item.in_req_time << "," << in_res_time << "," << in_req_item.in_req_body << "," << in_res_body;
	
		return buf.str();
	};
};

class AhatLogItemInReqError : public AhatLogItem
{
public:
	InReqItem in_req_item;
	std::string in_res_time;
	std::string in_res_body;

	std::string message()
	{
		std::stringstream buf;
		buf << "IN_REQ_ERR," << log_time << "," << src_file << "," << std::this_thread::get_id() << "," << in_req_item.in_req_ip << "," << in_req_item.in_req_port 
			<< "," << in_req_item.in_req_url << "," << in_req_item.in_req_time << "," << in_res_time << "," << in_req_item.in_req_body << "," << in_res_body;
	
		return buf.str();
	};
};

class AhatLogItemDebug : public AhatLogItem
{
public:
	std::string body;

	std::string message()
	{
		std::stringstream buf;
		buf << "DEBUG," << log_time << "," << src_file << "," << std::this_thread::get_id() << "," << body;
	
		return buf.str();
	};
};

#endif