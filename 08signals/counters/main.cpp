#include "counter.h"

#include <iostream>

int main(int argc, char *argv[])
{
    Counter c1(45);
    Counter c2(23);

    bool result = QObject::connect(&c1,&Counter::valueChanged,&c2,&Counter::setValue);
    if(!result)
    {
        return -1;
    }
    bool result2 = QObject::connect(&c2,&Counter::valueChanged,&c1,&Counter::setValue);
    if(!result2)
    {
        return -2;
    }

    std::cout<<"c1: " << c1.getCount() << ", c2: " << c2.getCount() << std::endl;
    std::cout << "c1/c2 increment\n";
    c1.Increment();
    std::cout<<"c1: " << c1.getCount() << ", c2: " << c2.getCount() << std::endl;
    c2.Increment();
    std::cout<<"c1: " << c1.getCount() << ", c2: " << c2.getCount() << std::endl;

    std::cout << "c1/c2 decrement\n";
    c1.Decrement();
    std::cout<<"c1: " << c1.getCount() << ", c2: " << c2.getCount() << std::endl;
    c2.Decrement();
    std::cout<<"c1: " << c1.getCount() << ", c2: " << c2.getCount() << std::endl;

}
