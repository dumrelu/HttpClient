#include "http_client.h"
using namespace http;

HttpClient::HttpClient(boost::asio::io_service &io, const std::string &hostname, const std::string &port, Version version) :
	base_client(hostname, port, version), socket_(io)
{
	ip::tcp::resolver resolver(io);
	ip::tcp::resolver::query query(hostname, port);
	endpoints_ = resolver.resolve(query);
}

void HttpClient::connect()
{
	boost::asio::connect(socket_, endpoints_);
}

bool HttpClient::isConnected()
{
	return socket_.is_open();
}

void HttpClient::disconnect()
{
	socket_.shutdown(ip::tcp::socket::shutdown_both);
	socket_.close();
}

ip::tcp::socket &HttpClient::sock()
{
	return socket_;
}