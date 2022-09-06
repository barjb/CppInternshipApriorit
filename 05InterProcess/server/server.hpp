#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <boost/asio.hpp>
#include <memory>
#include <atomic>
#include <thread>
#include <fstream>

class Service
{
public:
    Service();
    void startHandlingClient(std::shared_ptr<boost::asio::ip::tcp::socket> sock);

private:
    void handleClient(std::shared_ptr<boost::asio::ip::tcp::socket> sock);
    void openFile();
    void writeFile(std::istream &m_input_buf);
    boost::asio::streambuf m_request;
    std::string m_file_name;
    std::ofstream m_out_file;
};
class Acceptor
{
public:
    Acceptor(boost::asio::io_service &ios, unsigned short port_num);
    void accept();

private:
    boost::asio::io_service &m_ios;
    boost::asio::ip::tcp::acceptor m_acceptor;
    std::shared_ptr<boost::asio::ip::tcp::socket> m_sock;
};
class Server
{
public:
    Server(unsigned short port_num);
    void start();
    void stop();

private:
    void run();
    boost::asio::io_service m_ios;
    std::atomic<bool> m_stop;
    std::unique_ptr<std::thread> m_thread;
    std::unique_ptr<Acceptor> m_acceptor;
    int m_port_num;
};
#endif