
#ifndef HTTP_BASE_CLIENT_IMPLEMENTATION_H_
#define HTTP_BASE_CLIENT_IMPLEMENTATION_H_
//
//TODO: default headers, user agent
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

	template <typename S>
	Response base_client<S>::recv_response()
	{
		Response response;
		boost::asio::streambuf &streambuf = *response.getBuf();
		Headers headers;
		std::string httpVersion, reasonPhrase;
		int statusCode;

		auto header_size = boost::asio::read_until(sock(), streambuf, "\r\n\r\n");
		response >> httpVersion >> statusCode >> std::skipws;
		std::getline(response, reasonPhrase);
		headers.parse(response);

		if (!headers.hasValue("Content-Length"))
			throw std::runtime_error("No \"Content-Length\" field in the response.");

		int already_read = streambuf.size();
		int body_size = headers.getInt("Content-Length") - already_read;
		auto bytes_transferred = boost::asio::read(sock(), streambuf.prepare(body_size));
		streambuf.commit(bytes_transferred);

		response.setHeaders(headers);
		response.setStatusCode(statusCode);
		response.setReasonPhrase(reasonPhrase);

		return response;
	}

	template <typename S>
	Response base_client<S>::exec(const Request &request)
	{
		if (!isConnected())
			connect();

		send_request(request);
		return recv_response();
	}
}

#endif /*HTTP_BASE_CLIENT_IMPLEMENTATION_H_*/