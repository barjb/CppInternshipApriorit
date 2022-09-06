#ifndef _CIPHERED_LOGGER_HPP_
#define _CIPHERED_LOGGER_HPP_

#include <memory>
#include <string>

#include "cryptography.hpp"
#include "logger.hpp"

class CipheredLogger : public Logger
{
private:
    std::unique_ptr<XORCipher> adaptee;

public:
    CipheredLogger(std::string fileName, std::string key);
    void Write(std::string input);
};

#endif