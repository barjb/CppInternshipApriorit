#include <memory>
#include <utility>

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
int main()
{
    // std::shared_ptr<std::vector<std::string>> m = std::make_shared<std::vector<std::string>>(std::vector<std::string>({"john", "paul", "jacob", "major"}));
    std::shared_ptr<std::vector<int>> m = std::make_shared<std::vector<int>>(std::vector<int>({1, 2, 3, 4, 10, 15, 20}));

    std::cout << m->at(0) << std::endl;
    // std::cout << "UC: " << m.use_count() << std::endl;
    // std::vector<int> *x = m.get();
    // std::cout << "UC: " << m.use_count() << std::endl;
    // for (int i = 0; i < x->size(); i++)
    // {
    //     std::cout << x->at(i) << ", ";
    // }
    // std::cout << std::endl;

    // x->push_back(99);

    // for (int i = 0; i < m->size(); i++)
    // {
    //     std::cout << m->at(i) << ", ";
    // }
    // std::cout << std::endl;

    // std::shared_ptr<std::vector<int>> p = std::make_shared<std::vector<int>>(m.get());
    // for (int i = 0; i < p->size(); i++)
    // {
    //     std::cout << p->at(i) << ", ";
    // }
    // std::cout << std::endl;
}