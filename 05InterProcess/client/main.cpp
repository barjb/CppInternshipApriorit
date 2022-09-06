#include "client.hpp"

#include <iostream>
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "usage ./client 'filename'\n";
        return 1;
    }
    const std::string raw_ip_address = "127.0.0.1";
    const unsigned int port_num = 3333;
    try
    {
        Client client(raw_ip_address, port_num);
        client.connect();

        std::cout << "Sending file: " << argv[1] << std::endl;
        client.sendFile(argv[1]);
        std::cout << "Response from the server: " << client.getResponse() << std::endl;
        client.close();
    }
    catch (boost::system::system_error &e)
    {
        std::cout << "error occured " << e.code() << " message: " << e.what() << std::endl;
    }
    return 0;
}