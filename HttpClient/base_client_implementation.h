
#ifndef HTTP_BASE_CLIENT_IMPLEMENTATION_H_
#define HTTP_BASE_CLIENT_IMPLEMENTATION_H_
//
//TODO: default headers
#ifndef HTTP_USER_AGENT
#define HTTP_USER_AGENT "C++ HTTP Client"
#endif

namespace http {
	//Default headers for HTTP versions
	const Headers::map_type http_1_0_headers {
		{ "Accept", "*/*" }, 
		{ "Connection", "close" }, 
		{ "Cache-Control", "no-cache" }
	};

	const Headers::map_type http_1_1_headers{
		{ "Accept", "*/*" }, 
		{ "Connection", "keep-alive" }, 
		{ "Cache-Control", "no-cache" }
	};

	template <typename S>
	base_client<S>::base_client(const std::string &hostname, const std::string &port, Version version = HTTP_1_0) :
		defaultHeaders_(version == HTTP_1_0 ? http_1_0_headers : http_1_1_headers), 
		hostname_(hostname), port_(port), version_(version)
	{
	}

	template <typename S>
	Response base_client<S>::exec(const Request &request)
	{
		send_request(request);
		return recv_response();
	}

	template <typename S>
	void base_client<S>::send_request(const Request &request)
	{
		std::string requestLine = request.getMethodString() + " ";
		requestLine += request.getPath() + " ";
		requestLine += version_ == HTTP_1_0 ? "HTTP/1.0" : "HTTP/1.1";
		requestLine += "\r\n";

		auto headerFields = request.getHeaders();
		headerFields.addValue("Content-Length", request.getBuf()->size());

		std::string requestHeader = requestLine + headerFields.toString() + "\r\n";
		boost::asio::write(sock(), boost::asio::buffer(requestHeader));

		boost::asio::write(sock(), *request.getBuf());
	}
}

#endif /*HTTP_BASE_CLIENT_IMPLEMENTATION_H_*/