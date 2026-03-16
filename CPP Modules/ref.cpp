#include <iostream>

unsigned int foo()
{
	unsigned int lo, hi;
	asm volatile("rdtsc": "=a"(lo), "=b"(hi));
	return ((uint64_t)hi <<32 )| lo;
}

int main()
{
	int x = 32;
	int y = 42;
	int &x_ref = x;

	const int &cx_ref = x;

	unsigned int start, end;
	start = foo();

	std::cout << "x     = " << x << std::endl;
	std::cout << "&x    = " <<&x << std::endl;
	std::cout << "y     = " <<y << std::endl;
	std::cout << "&y    = " <<&y << std::endl;
	std::cout << "x_ref = " <<&x_ref << std::endl;

	x_ref = y;
	std::cout << "Setting x_ref = y" << std::endl;
	std::cout << "x_ref = " <<&x_ref << std::endl;
	std::cout << "x     = " << x << " (copies y into x)" << std::endl;
	
	// cx_ref = y;
	std::cout << "Setting x_ref = y" << std::endl;
	std::cout << "x_ref = " <<&x_ref << std::endl;
	std::cout << "x     = " << x << " (copies y into x)" << std::endl;

	end = foo();
	std::cout << "Cycles" << end -start << std::endl;
}
