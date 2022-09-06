#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <thread>

class Client
{
public:
    Client(int port) : port_num(port)
    {
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port_num);
        addr_len = sizeof(address);

        if ((client_num = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            std::cout << "Failed to create socket.\n";
            exit(EXIT_FAILURE);
        }
    }
    void Connect()
    {
        if (connect(client_num, (sockaddr *)&address, addr_len) < 0)
        {
            std::cout << "Failed to accept connection.\n";
            exit(EXIT_FAILURE);
        }
    }
    void Close()
    {
        std::cout << "Server closed the connection.\n";
        close(client_num);
    }
    void sendRequest(const char *input)
    {
        send(client_num, input, strlen(input), 0);
    }
    bool receiveResponse()
    {
        char buffer[1024];
        size_t bytes_read = recv(client_num, buffer, sizeof(buffer), 0);

        if (bytes_read == 0)
            return false;

        buffer[bytes_read] = '\0';
        std::cout << "Bytes read: " << bytes_read << " from server_id [" << client_num << "] : " << buffer << std::endl;

        return true;
    }

private:
    int port_num;
    int client_num;
    int addr_len;
    sockaddr_in address;
};

int main()
{
    const int PORT_NUM = 7777;
    bool isConnected = true;
    std::string input;
    std::unique_ptr<std::thread> client;

    Client c(PORT_NUM);
    client.reset(new std::thread([&c]
                                 { c.Connect(); }));

    while (isConnected)
    {
        std::cout << "Type your message... 'disconnect' to exit\n";
        std::getline(std::cin, input);
        c.sendRequest(input.c_str());
        isConnected = c.receiveResponse();
        std::cout << "======\n";
    }
    c.Close();

    if (client.get()->joinable())
        client.get()->join();
}