#include <fstream>
#include <iostream>
#include <array>
#include <vector>

int main()
{
    std::string cfname = "Z_fromclient.txt";
    std::fstream cf(cfname, std::ios::binary | std::ios::in);
    std::string sfname = "Z_toserver.txt";
    std::fstream sf(sfname, std::ios::binary | std::ios::out);

    if (!cf.is_open())
    {
        std::cout << "failed to open client file\n";
    }
    if (!sf.is_open())
    {
        std::cout << "failed to open server file\n";
    }
    // cf >> sf;

    // 0 bytes from end
    cf.seekg(0, cf.end);
    // current reading position (0 bytes from end)
    size_t inputsize = cf.tellg();
    // std::cout << "cf: " << filesize << std::endl;
    // trzeba cofnac na poczatek pliku
    cf.seekg(0);

    const std::size_t filesize = 1024;
    std::array<char, filesize> buffer;

    // char buffer[1024];
    cf.read(buffer.data(), buffer.size());
    std::cout << buffer.data();

    // auto buf = boost::asio::buffer(buffer.data(), static_cast<size_t>(inputsize));

    sf << "a " << 13 << " " << 22;

    // cf.close();
    // sf.close();
}