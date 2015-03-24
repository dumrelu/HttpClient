#include "response.h"
using namespace http;


Response::Response(int statusCode, const std::string &reasonPhrase, const Headers &headers) :
	std::istream(nullptr), headers_(headers), statusCode_(statusCode), reasonPhrase_(reasonPhrase), buf_(new boost::asio::streambuf)
{
	rdbuf(buf_.get());
}

Response::Response(Response &&o) :
	std::istream(std::move(o)), headers_(std::move(o.headers_)), statusCode_(o.statusCode_), reasonPhrase_(std::move(o.reasonPhrase_)), 
	buf_(std::move(o.buf_))
{
	rdbuf(buf_.get());
}

Response &Response::operator=(Response &&o)
{
	if (this != &o) {
		std::istream::operator=(std::move(o));
		headers_ = std::move(o.headers_);
		statusCode_ = o.statusCode_;
		reasonPhrase_ = std::move(o.reasonPhrase_);
		buf_ = std::move(o.buf_);

		rdbuf(buf_.get());
	}

	return *this;
}