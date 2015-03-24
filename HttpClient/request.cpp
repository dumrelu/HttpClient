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
	std::ostream(nullptr), headers_(headers), methodString_(methodStrings_[method]), path_(path), buf_(new boost::asio::streambuf)
{
		rdbuf(buf_.get());
}

Request::Request(const std::string &methodString, const std::string &path, const Headers &headers) :
	std::ostream(nullptr), headers_(headers), methodString_(methodString), path_(path), buf_(new boost::asio::streambuf())
{
		rdbuf(buf_.get());
}

Request::Request(Request &&o) :
	std::ostream(std::move(o)), headers_(std::move(o.headers_)), methodString_(std::move(o.methodString_)),
	path_(std::move(o.path_)), buf_(std::move(o.buf_))
{
		rdbuf(buf_.get());
}

Request &Request::operator=(Request &&o)
{
	if (this != &o) {
		std::ostream::operator=(std::move(o));
		headers_ = std::move(o.headers_);
		methodString_ = std::move(o.methodString_);
		path_ = std::move(o.path_);
		buf_ = std::move(o.buf_);

		rdbuf(buf_.get());
	}

	return *this;
}