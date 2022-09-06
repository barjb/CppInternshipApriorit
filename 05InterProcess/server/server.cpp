#include "server.hpp"
#include <iostream>

Service::Service()
{
}

void Service::startHandlingClient(std::shared_ptr<boost::asio::ip::tcp::socket> sock)
{
    std::thread thread(([this, sock]()
                        { handleClient(sock); }));
    thread.detach();
}
void Service::openFile()
{
    m_out_file = std::ofstream(m_file_name, std::ios::binary | std::ios_base::out);
    if (!m_out_file)
    {
        std::cerr << "failed to create file\n";
        return;
    }
}
void Service::writeFile(std::istream &m_input_buf)
{
    m_out_file << m_input_buf.rdbuf();
    m_out_file.close();
}
void Service::handleClient(std::shared_ptr<boost::asio::ip::tcp::socket> sock)
{
    try
    {
        boost::asio::read_until(*sock.get(), m_request, '\n\n');
        std::istream m_input_buf(&m_request);

        std::getline(m_input_buf >> std::ws, m_file_name);
        std::cout << "Received request from a client for a file: " << m_file_name << std::endl;

        openFile();
        writeFile(m_input_buf);

        std::string response = "File read succesfully\n";
        boost::asio::write(*sock.get(), boost::asio::buffer(response));
    }
    catch (boost::system::system_error &e)
    {
        std::cout << "error occured " << e.code() << " message: " << e.what() << std::endl;
    }
    delete this;
}

Acceptor::Acceptor(boost::asio::io_service &ios, unsigned short port_num) : m_ios(ios), m_acceptor(m_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::any(), port_num))
{
    m_acceptor.listen();
}
void Acceptor::accept()
{
    m_sock = std::make_shared<boost::asio::ip::tcp::socket>(m_ios);
    m_acceptor.accept(*m_sock);
    (new Service)->startHandlingClient(m_sock);
}

Server::Server(unsigned short port_num) : m_port_num(port_num), m_stop(false)
{
}

void Server::start()
{
    m_thread.reset(new std::thread([this]()
                                   { run(); }));
}

void Server::stop()
{
    m_stop.store(true);
    m_thread->join();
}
void Server::run()
{
    m_acceptor = std::make_unique<Acceptor>(m_ios, this->m_port_num);
    while (!m_stop.load())
    {
        m_acceptor->accept();
    }
}