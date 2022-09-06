#include "client.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

#include <array>
#include <exception>

Client::Client(const std::string &raw_ip_address, unsigned short port_num) : m_ep(boost::asio::ip::address::from_string(raw_ip_address), port_num), m_sock(m_ios)
{
    m_sock.open(m_ep.protocol());
}
void Client::connect()
{
    m_sock.connect(m_ep);
}
void Client::close()
{
    m_sock.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    m_sock.close();
}
void Client::sendFile(char *file_name)
{
    std::ifstream file(file_name, std::ios_base::binary | std::ios_base::in);
    if (!file)
    {
        std::cerr << "Failed opening file: " << file_name << std::endl;
        return;
    }

    const int array_size = 1024;
    std::array<char, array_size> m_file_buffer;

    file.read(m_file_buffer.data(), m_file_buffer.size());

    std::ostream m_request(&m_request_buffer);
    m_request << file_name << "\n";
    m_request << m_file_buffer.data();
    boost::asio::write(m_sock, m_request_buffer);
}
std::string Client::getResponse()
{
    boost::asio::read_until(m_sock, m_response_buffer, '\n');
    std::istream input(&m_response_buffer);
    std::string response;
    std::getline(input, response);
    return response;
}
