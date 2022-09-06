#include "cryptography.hpp"

XORCipher::XORCipher(std::string key) : key(key) {}

std::string XORCipher::cipher(std::string input)
{
    int i = 0;
    std::for_each(input.begin(), input.end(), [&](char &character)
                  {
        character ^= key[i % key.length()];
        i++; });
    return input;
}