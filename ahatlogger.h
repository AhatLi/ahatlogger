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

#include "ahatloggeritem.h"

#define __FILENAME__    strrchr(__FILE__, '\\') +1

#define CODE() code(__FILENAME__, __FUNCTION__, __LINE__)

std::string code(const char* file, char* func, int line);

class AhatLogger
{
private:
	static std::string path;

	static std::string name;
	static std::string version;
	static std::string host;
	
	static std::queue< std::pair<std::string, std::string> > *q;
	static bool isStarted;
	static int level;

	static void run();
public:
	static std::mutex mutex;
	
	static void setting(std::string path, int level);
	static void start();
	static void stop();
	
	static void INFO(std::string src_file, std::string body);
	static void ERROR(std::string src_file, std::string body);
	static void DEBUG(std::string src_file, std::string body);

	static void CUSTOM(std::string src_file, std::string custom, std::string body);

	static void REQUEST(std::string src_file, std::string req_ip, std::string req_uri);
	static void RESPONSE(std::string src_file, std::string res_body, std::string res_code);

	static void DB(std::string src_file, InDBtem db_req_item, std::string db_res_body);
	static void DB_ERROR(std::string src_file, InDBtem db_req_item, std::string db_res_body);
	
	static void IN_REQ(std::string src_file, InReqItem in_req_item, std::string in_res_body);
	static void IN_REQ_ERR(std::string src_file, InReqItem in_req_item, std::string in_res_body);
};




#endif