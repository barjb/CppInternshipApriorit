#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <thread>

class AcceptorSocket
{
public:
    AcceptorSocket(int port_num, int backlog_size) : port_num(port_num), backlog_size(backlog_size)
    {
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port_num);
        addr_len = sizeof(address);
        runs = true;

        FD_ZERO(&master);
        FD_ZERO(&read_fds);

        if ((server_num = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            std::cout << "Failed to create socket.\n";
            exit(EXIT_FAILURE);
        }
        if (bind(server_num, (sockaddr *)&address, addr_len) < 0)
        {
            std::cout << "Failed to bind.\n";
            exit(EXIT_FAILURE);
        }
    }
    void Listen()
    {
        if (listen(server_num, backlog_size) < 0)
        {
            std::cout << "Failed to listen.\n";
            exit(EXIT_FAILURE);
        }
        FD_SET(server_num, &master);
        fdmax = server_num;
    }
    void Accept()
    {
        while (runs)
        {
            read_fds = master;
            if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
            {
                std::cout << "select error\n";
            }
            for (int client = 0; client <= fdmax; client++)
            {
                if (FD_ISSET(client, &read_fds))
                {
                    if (client == server_num)
                    {
                        if ((new_connection = accept(server_num, (sockaddr *)&address, (socklen_t *)&addr_len)) < 0)
                        {
                            std::cout << "failed to accept\n";
                            exit(EXIT_FAILURE);
                        }
                        else
                        {
                            std::cout << "Got new client: " << new_connection << std::endl;
                            FD_SET(new_connection, &master);
                            if (new_connection > fdmax)
                            {
                                fdmax = new_connection;
                            }
                        }
                    }
                    else
                    {
                        char buffer[1024];
                        size_t bytes_read = recv(client, buffer, sizeof(buffer), 0);
                        buffer[bytes_read] = '\0';
                        std::cout << "Received <" << bytes_read << "> from client[" << client << "] message: " << buffer << std::endl;
                        if (strcmp(buffer, "disconnect") == 0 || bytes_read == 0)
                        {
                            if (shutdown(client, SHUT_RDWR) < 0)
                            {
                                std::cout << "Error closing socket!\n";
                                exit(1);
                            }
                            FD_CLR(client, &master);
                        }
                        else if (strcmp(buffer, "hello") == 0)
                        {
                            auto msg = "world";
                            send(client, msg, strlen(msg), 0);
                        }
                        else
                        {
                            send(client, buffer, strlen(buffer), 0);
                            std::cout << "ECHO sent to the client: " << buffer << "\n";
                        }
                    }
                }
            }
        }
    }

private:
    int server_num;
    sockaddr_in address;
    int addr_len;
    int backlog_size;
    int port_num;
    int client;
    int new_connection;
    bool runs;
    fd_set master;
    fd_set read_fds;
    int fdmax;
};

class Server
{
public:
    Server(int port_num, int backlog_size) : port_num(port_num), backlog_size(backlog_size) {}
    void Start()
    {
        acceptor_thread.reset(new std::thread([this]()
                                              { Run(backlog_size); }));
    }
    void Stop()
    {
        acceptor_thread->join();
    }
    ~Server()
    {
        if (acceptor_thread->joinable())
        {
            acceptor_thread->join();
        }
    }

private:
    void Run(int backlog_size)
    {
        acceptor = std::make_unique<AcceptorSocket>(port_num, backlog_size);
        acceptor->Listen();
        while (true)
        {
            acceptor->Accept();
        }
    }
    int port_num;
    int backlog_size;
    std::unique_ptr<std::thread> acceptor_thread;
    std::unique_ptr<AcceptorSocket> acceptor;
};

int main()
{
    const int PORT = 7777;
    const int BACKLOG_SIZE = 10;
    Server s(PORT, BACKLOG_SIZE);

    std::unique_ptr<std::thread> server;
    server.reset(new std::thread([&]
                                 { s.Start(); }));

    if (server.get()->joinable())
        server.get()->join();
}