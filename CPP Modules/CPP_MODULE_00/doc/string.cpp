#include <string>
#include <iostream>
#include <iomanip>

class Foo
{
private:
	int x;
	int b;
	/* data */
public:

	Foo() = default;
	Foo(int x, int b) {
		this->x = x;
		this->b = b;
	}
	
	void say_hello(){std::cout << "hello" << std::endl;}
	void say_hello2();
	~Foo();
};


void Foo::say_hello2(){
	std::cout << "hello 2" << std::endl;
}





int main()
{
	std::string input("123456789");
	int width = 12;
	int trunc = input.length() > width ? input.length() - width : 0;
	std::cout	<< std::setw(width)
				<< std::right;
				if (trunc) 
	std::cout 	<< input.replace(width - 1, trunc + 1, std::string(1, '.'));
				else
	std::cout 	<< input;
	std::cout	<< std::endl;

	Foo foo;
	foo.say_hello();
	foo.say_hello2();
}
