#include "request.h"
#include <exception>
using namespace http;

std::unordered_map<Request::Method, std::string> Request::methodStrings_{
	{ Request::GET, "GET" }, 
	{ Request::HEAD, "HEAD" }, 
	{ Request::POST, "POST" }, 
	{ Request::PUT, "PUT" }, 
	{ Request::DELETE, "DELETE" }, 
	{ Request::CONNECT, "CONNECT" }, 
	{ Request::OPTIONS, "OPTIONS" }, 
	{ Request::TRACE, "TRACE" }
};

Request::Request(Method method, const std::string &path, const Headers &headers) : 
	headers_(headers), methodString_(methodStrings_[method]), path_(path)
{
}

Request::Request(const std::string &methodString, const std::string &path, const Headers &headers) :
	headers_(headers), methodString_(methodString), path_(path)
{
}