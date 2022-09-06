#include <sys/socket.h>
#include <netinet/in.h>
#include <memory>
#include <unistd.h>
#include <functional>

class Deleter2
{
public:
    void operator()(int *sock)
    {
        close(*sock);
    }
};

int main()
{
    sockaddr_in address;
    size_t addr_len;
    int port_num = 3333;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port_num);
    addr_len = sizeof(address);

    auto deleter1 = [](int *sock)
    {
        close(*sock);
    };

    int sock1 = socket(AF_INET, SOCK_STREAM, 0);
    std::unique_ptr<int, decltype(deleter1)> uni_ptr1(&sock1, deleter1);

    int sock2 = socket(AF_INET, SOCK_STREAM, 0);
    std::unique_ptr<int, Deleter2> uni_ptr2(&sock2);

    std::function<void(int *)> del3 = [](int *sock)
    {
        close(*sock);
    };
    int sock3 = socket(AF_INET, SOCK_STREAM, 0);
    std::unique_ptr<int, decltype(del3)> p(&sock3, del3);
}
