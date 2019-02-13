#include "ahatloggeritem.h"

AhatLogItemInfo::AhatLogItemInfo(std::string src_file, std::string body)
{
	this->src_file = src_file;
	this->body = body;
}

AhatLogItemError::AhatLogItemError(std::string src_file, std::string body)
{
	this->src_file = src_file;
	this->body = body;
}

AhatLogItemRequest::AhatLogItemRequest(std::string src_file, std::string req_ip, std::string req_uri, std::string req_body)
{
	this->src_file = src_file;
	this->req_ip = req_ip;
	this->req_uri = req_uri;
	this->req_body = req_body;
}

AhatLogItemResponse::AhatLogItemResponse(std::string src_file, std::string res_body, std::string res_code)
{
	this->src_file = src_file;
	this->res_body = res_body;
	this->res_code = res_code;
}

AhatLogItemDB::AhatLogItemDB(std::string src_file, InDBtem db_req_item, std::string db_res_body)
{
	this->src_file = src_file;
	this->db_res_time = getCurTime();
	this->db_req_item = db_req_item;
	this->db_res_body = db_res_body;
}

AhatLogItemDBError::AhatLogItemDBError(std::string src_file, InDBtem db_req_item, std::string db_res_body)
{
	this->src_file = src_file;
	this->db_res_time = getCurTime();
	this->db_req_item = db_req_item;
	this->db_res_body = db_res_body;
}

AhatLogItemInReq::AhatLogItemInReq(std::string src_file, InReqItem in_req_item, std::string in_res_body)
{
	this->src_file = src_file;
	this->in_res_time = getCurTime();
	this->in_req_item = in_req_item;
	this->in_res_body = in_res_body;
}

AhatLogItemInReqError::AhatLogItemInReqError(std::string src_file, InReqItem in_req_item, std::string in_res_body)
{
	this->src_file = src_file;
	this->in_res_time = getCurTime();
	this->in_req_item = in_req_item;
	this->in_res_body = in_res_body;
}

AhatLogItemDebug::AhatLogItemDebug(std::string src_file, std::string body)
{
	this->src_file = src_file;
	this->body = body;
}

AhatLogItemCustom::AhatLogItemCustom(std::string src_file, std::string body)
{
	this->src_file = src_file;
	this->body = body;
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
}

InDBtem::InDBtem()
{
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
}

InReqItem::InReqItem()
{
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