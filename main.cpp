#include <iostream>
#include "big_int.h"

int main() {

	BigInt a;
	std::cout << a << std::endl;
	a = 1324;
	std::cout << a << std::endl;
	a = a - 9999;
	std::cout << a << std::endl;
	a = a * -731;
	std::cout << a << std::endl;
	return 0;
}
