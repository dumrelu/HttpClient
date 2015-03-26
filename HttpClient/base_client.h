
#ifndef HTTP_BASE_CLIENT_H_
#define HTTP_BASE_CLIENT_H_

#include "headers.h"
#include "request.h"
#include "response.h"
#include <boost\asio.hpp>
#include <string>

namespace http {

	enum Version : char {
		HTTP_1_0, 
		HTTP_1_1
	};

	template <typename Socket>
	class base_client {
	public:
		base_client(const std::string &hostname, const std::string &port, Version version = HTTP_1_0);
		base_client(const base_client &) = delete;
		base_client(base_client &&) = delete;

		base_client &operator=(const base_client &) = delete;
		base_client &operator=(base_client &&) = delete;

		Response exec(const Request &request);

		Headers getDefaultHeaders() const { return defaultHeaders_; }
		const std::string &getHostname() const { return hostname_; }
		const std::string &getPort() const { return port_; }
		Version getVersion() const { return version; }

		void setDefaultHeaders(const Headers &defaultHeaders) { defaultHeaders_ = defaultHeaders; }
		void setVersion(Version version) { version_ = version; }

	protected:
		virtual void connect() = 0;
		virtual bool isConnected() = 0;
		virtual void disconnect() = 0;
		virtual Socket& sock() = 0;

	private:
		void send_request(const Request &request);
		Response recv_response();

	private:
		Headers defaultHeaders_;
		std::string hostname_, port_;
		Version version_;
	};
}

//Include the implementation file
#include "base_client_implementation.h"

#endif /*HTTP_BASE_CLIENT_H_*/