#ifndef AHATLOGGER_H_
#define AHATLOGGER_H_

#include <iostream>
#include <thread>
#include <string>
#include <queue>
#include <memory>
#include <chrono>
#include <thread>

#define INFO 1
#define ERROR 2
#define REQUEST 3
#define RESPONSE 4
#define DB 5
#define DB_ERROR 6
#define IN_REQ 7
#define IN_REQ_ERROR 8
#define DEBUG 9

class AhatLogItem
{
private:
	std::string thread_name;
	std::string log_time;
	std::string src_name;
	std::string src_line;
	std::string src_func;
	std::string log_type;
	/*
	AhatLogItem() {};

	AhatLogItem
	(
		std::string thread_name,
		std::string log_time,
		std::string src_name,
		std::string src_line,
		std::string src_func,
		std::string log_type
	)
	{
		this->thread_name = thread_name;
		this->log_time = log_time;
		this->src_name = src_name;
		this->src_line = src_line;
		this->src_func = src_func;
		this->log_type = log_type;
	}
	*/
};	

class AhatLogItemInfo : public AhatLogItem
{
	std::string body;

//	AhatLogItemInfo() { AhatLogItem(); };
};

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


class AhatLogger
{
private:
	static std::string name;
	static std::string version;
	static std::string host;

	static std::queue< std::shared_ptr<AhatLogItem> > *q;

public:
	
	static void run();
	static void info();
	static void start();
};

std::string getCurTime();

#endif