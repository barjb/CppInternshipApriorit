#include "server.hpp"
#include <memory>
#include <iostream>
int main()
{
    unsigned short port_num = 3333;
    try
    {
        Server srv(port_num);
        srv.start();
        std::this_thread::sleep_for(std::chrono::seconds(60));
        srv.stop();
    }
    catch (boost::system::system_error &e)
    {
        std::cout << "Error occured " << e.code() << " message: " << e.what() << std::endl;
    }
}