
#ifndef HTTP_CLIENT_H_
#define HTTP_CLIENT_H_

#include "base_client.h"
#include <boost\asio.hpp>

namespace http {
	namespace ip = boost::asio::ip;

	class HttpClient : public base_client<ip::tcp::socket> {
	public:
		HttpClient(boost::asio::io_service &io, const std::string &hostname, const std::string &port, Version version = HTTP_1_0);

	protected:
		void connect() override;
		bool isConnected() override;
		void disconnect() override;
		ip::tcp::socket &sock() override;

	private:
		ip::tcp::socket socket_;
		ip::tcp::resolver::iterator endpoints_;
	};
}

#endif /*HTTP_CLIENT_H_*/