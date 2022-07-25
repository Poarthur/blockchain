#include <iostream>
#include <Sha256.h>

int main()
{
    Block::Sha256 sha("Memphis");
    std::string s = sha.sha256_to_ascii();
    std::cout << s << std::endl;
    for (int i = 0; i < 32; i++) {
        std::cout << std::hex << (int)(unsigned char)s[i] << ' ';
    }
    std::cout << std::endl;
    std::string a = sha.sha256_from_ascii(s);
    for (int i = 0; i < 32; i++) {
        std::cout << std::hex << (int)(unsigned char)a[i] << ' ';
    }
    std::cout << std::endl;
    std::cout << sha << std::endl;
}