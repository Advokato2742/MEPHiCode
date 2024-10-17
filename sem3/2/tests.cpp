#include "domino.h"
#include <cassert>
#include <iostream>
#include "output.h"

int testcreate() {
	Bunch t = Bunch();
	std::cout << t;
	Bunch b = Bunch(4);
	std::cout << b.GetSize() << std::endl;
	std::cout << b;
	Bunch&& c = std::move(b);
	std::cout << "b" << b.GetSize() << std::endl;
	std::cout << b;
	std::cout << c;
	return 1;
}

int testadd() {
	Bunch a = Bunch();
	std::cout << "u" << std::endl;
	a.Add();
	std::cout << a.GetSize() << std::endl;
	std::cout << a;
	a.Add();
	std::cout << "u" << std::endl;
	std::cout << a;
	return 1;
}

int testdeleteat() {
	Bunch a = Bunch(3);
		try {
		a.DeleteAt(-3);
	} catch (std::invalid_argument) {
		std::cout << "yep" << std::endl;
	} catch (...) {
		std::cout << "false" << std::endl;
	}
	std::cout << a;
	a.DeleteAt(0);
	std::cout << a;
	a.DeleteAt(1);
	std::cout << a;
	a.DeleteAt(0);
	std::cout << a.GetSize() << std::endl;
	try {
		a.DeleteAt(3);
	} catch (std::invalid_argument) {
		std::cout << "yep" << std::endl;
	} catch (...) {
		std::cout << "false" << std::endl;
	}
	return 1;
}

int testplus() {
	Domino a = Domino().ChangeValues();
	Bunch b = Bunch();
	b += a;
	std::cout << b;
	b += a;
	std::cout << b;
	return 1;
}
int testplusbunch() {
	Bunch a = Bunch();
	Bunch b = Bunch(3);
	std::cout << b;
	a += b;
	std::cout << a;	
	b += b;
	std::cout << "----" << std::endl;
	std::cout << b;
	return 1;
}

int testcopy() {
	Bunch a = Bunch();
	Bunch b = Bunch(3);
	std::cout << "b^" << std::endl;
	std::cout << b;
	b = b;
		std::cout << "b^" << std::endl;
	std::cout << b;
	a = b;
	std::cout << a;
	std::cout << "----" << std::endl;
	Bunch c = Bunch();
	a = c;
	std::cout << a;
	return 1;
}

int testsub() {
	Bunch a = Bunch(4);
	int t;
	std::cout << a;
	std::cin >> t;
	Bunch* b = a.GetSubBunch(t);
	std::cout << a;
	std::cout << "er" << b->GetSize() << std::endl;
	std::cout << *b;
	return 1;
}
int testsort() {
	Bunch a = Bunch(5);
	a.Sort();
	std::cout << a;
	return 1;
}
int testmove() {
	Bunch a = Bunch(3);
	Bunch b = Bunch(std::move(a));
	std::cout << a;
	std::cout << b;
	Bunch c = std::move(b);
	std::cout << b.GetSize();
	std::cout << c;
	return 1;
}
int main() {
	int a[] = {1, 2, 3, 4};
	std::cout << a[4];
	return 0;
}