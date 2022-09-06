#include "cipheredLogger.hpp"

CipheredLogger::CipheredLogger(std::string fileName, std::string key) : Logger(fileName), adaptee(std::make_unique<XORCipher>(key)) {}

void CipheredLogger::Write(std::string input)
{
    std::string cipheredOutput = adaptee->cipher(input);
    Logger::Write(cipheredOutput);
}