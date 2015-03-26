
#ifndef HTTP_RESPONSE_H_
#define HTTP_RESPONSE_H_

#include <istream>
#include <string>
#include <memory>
#include <boost\asio\streambuf.hpp>
#include "headers.h"

namespace http {

	class Response : public std::istream {
	public:
		typedef std::shared_ptr<boost::asio::streambuf> buf_ptr;

		Response(int statusCode = -1, const std::string &reasonPhrase = "", const Headers &headers = Headers());
		Response(const Response&) = delete;
		Response(Response &&);

		Response &operator=(const Response &) = delete;
		Response &operator=(Response &&);

		const Headers &getHeaders() const { return headers_; }
		int getStatusCode() const { return statusCode_; }
		const std::string &getReasonPhrase() const { return reasonPhrase_; }
		buf_ptr getBuf() const { return buf_; }

		void setHeaders(const Headers &headers) { headers_ = headers; }
		void setStatusCode(int statusCode) { statusCode_ = statusCode; }
		void setReasonPhrase(const std::string &reasonPhrase) { reasonPhrase_ = reasonPhrase; }
		void setBuf(boost::asio::streambuf *buf) { buf_.reset(buf); rdbuf(buf); }

	private:
		Headers headers_;
		int statusCode_;
		std::string reasonPhrase_;
		buf_ptr buf_;
	};

}

#endif /*HTTP_RESPONSE_H_*/