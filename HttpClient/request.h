
#ifndef HTTP_REQUEST_H_
#define HTTP_REQUEST_H_

#include <ostream>
#include <string>
#include <unordered_map>
#include <boost\asio\streambuf.hpp>
#include <memory>
#include "headers.h"

namespace http {

	class Request : public std::ostream {
	public:
		//Common http methods
		enum Method : char {
			GET, 
			HEAD,
			POST, 
			PUT, 
			DELETE, 
			CONNECT, 
			OPTIONS, 
			TRACE
		};

		//Stream buffer pointer
		typedef std::shared_ptr<boost::asio::streambuf> buf_ptr;

		Request(Method method = GET, const std::string &path = "/", const Headers &headers = Headers());
		Request(const std::string &methodString, const std::string &path = "/", const Headers &headers = Headers());
		Request(const Request &) = delete;
		Request(Request &&);

		Request &operator=(const Request &) = delete;
		Request &operator=(Request &&);

		const Headers &getHeaders() const { return headers_; }
		const std::string &getMethodString() const { return methodString_; }
		const std::string &getPath() const { return path_; }
		buf_ptr getBuf() const { return buf_; }

		void setHeaders(const Headers &headers) { headers_ = headers; }
		void setMethodString(const std::string &methodString) { methodString_ = methodString; }
		void setPath(const std::string &path) { path_ = path; }
		void setBuf(boost::asio::streambuf *buf) { buf_.reset(buf); }

	private:
		Headers headers_;
		std::string methodString_;
		std::string path_;
		buf_ptr buf_;
		static std::unordered_map<Method, std::string> methodStrings_;
	};

}

#endif /*HTTP_REQUEST_H_*/