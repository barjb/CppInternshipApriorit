#include <iostream>
#include <future>

#include <atomic>

#include <ctime>

void operation(int a, std::string op, int b)
{
    std::srand(std::time(nullptr));
    int random_wait = std::rand() % 10 + 10;
    int result;
    if (op == "+")
    {
        result = a + b;
    }
    else if (op == "*")
    {
        result = a * b;
    }
    std::this_thread::sleep_for(std::chrono::seconds(random_wait));
    std::cout << "OPERATION[" << op << "] (" << a << ", " << b << ") = " << result << std::endl;
}

int main()
{
    bool loop = true;
    std::string input;
    while (loop)
    {
        std::cout << "podaj dzialanie, q aby zakończyć...\n";
        std::cin >> input;
        if (input == "Q" || input == "q")
        {
            break;
        }
        else
        {
            int a, b;
            std::string op;
            a = std::stoi(input);
            std::cin >> input;
            op = input;
            std::cin >> input;
            b = std::stoi(input);
            std::cout << a << " " << op << " " << b << " = ?\n";
            (std::thread(operation, a, op, b).detach());
        }
    }
}