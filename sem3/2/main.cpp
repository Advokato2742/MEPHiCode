#include "domino.h"
#include <iostream>

int main() {
	srand(time(0));
	Domino re = Domino();
	std::cout << re << std::endl;
	std::cin >> re;
	std::cout << "re " << re << std::endl;
	Dominoes t1 = Dominoes(3);
	std::cin >> t1;
	Dominoes t2 = Dominoes(3);
	std::cout << t1 << std::endl << t2;

	Dominoes a = Dominoes();
	std::cout << a << std::endl;
	Domino r = Domino(3, 5);
	a += r;
	std::cout << a << std::endl;
	Dominoes b = Dominoes(3);
	a += b;
	std::cout << a << std::endl;
	b[3] = r;
	a.Sort();
	std::cout << a << std::endl;
	return 0;
}