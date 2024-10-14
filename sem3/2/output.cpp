#include "output.h"
#include <iostream>

std::ostream& operator<<(std::ostream& stream, const Domino& one) {
	stream << one.GetImage();
	return stream;
}
std::ostream& operator<<(std::ostream& stream, const Bunch& one) {
	for (int i = 0; i < one.GetSize(); i++) {
		stream << one[i] << std::endl;
	}
	return stream;
}