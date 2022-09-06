#ifndef _CRIPTOGRAPHY_HPP_
#define _CRYPTOGRAPHY_HPP_

#include <string>
#include <algorithm>

class XORCipher
{
public:
    XORCipher(std::string key);
    std::string cipher(std::string input);

private:
    std::string key;
};

#endif