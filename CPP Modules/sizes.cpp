#include <iostream>
#include <array>
#include <string>
#include <vector>

struct Empty {};

int main() {
    Empty e;
    std::array<int, 5> x;

    unsigned char *p = reinterpret_cast<unsigned char*>(&e);
    std::cout << "Byte value: " << static_cast<int>(*p) << std::endl;
    std::cout << &e << std::endl;
    std::cout <<"sizeof array " << sizeof(std::array<int, 0>) << std::endl;



	std::string s1 = "short";
	std::string s2 = "this is a very long string that will not fit in SSO";
	
	std::cout << "sizeof(std::vector<int>): " << sizeof(std::vector<int>) << std::endl;
	std::cout << "sizeof(std::string): " << sizeof(std::string) << std::endl;
	std::cout << "s1 data address: " << static_cast<const void*>(s1.data()) << std::endl;
	std::cout << "s2 data address: " << static_cast<const void*>(s2.data()) << std::endl;
	std::cout << "s1 object address: " << static_cast<const void*>(&s1) << std::endl;
	std::cout << "s2 object address: " << static_cast<const void*>(&s2) << std::endl;
    return 0;
}


