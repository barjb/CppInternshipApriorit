#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <boost/asio.hpp>

class Client
{
public:
    Client(const std::string &raw_ip_address, unsigned short port_num);
    void connect();
    void close();
    void sendFile(char *file_name);
    std::string getResponse();

private:
    void sendRequest(const std::string &request);

private:
    boost::asio::io_service m_ios;
    boost::asio::ip::tcp::endpoint m_ep;
    boost::asio::ip::tcp::socket m_sock;
    boost::asio::streambuf m_response_buffer;
    boost::asio::streambuf m_request_buffer;
};

#endif