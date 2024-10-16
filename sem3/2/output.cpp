#include "output.h"
#include <iostream>
//number of domino values
const uint8_t q{7};
//height of domino image
const uint8_t h{4};
//width of domino image
const uint8_t w{9};
const std::string images[q] = {
	" _______ \n|       |\n|       |\n|_______|\n",
	" _______ \n|       |\n|   O   |\n|_______|\n",
	" _______ \n| O     |\n|       |\n|_____O_|\n",
	" _______ \n| O     |\n|   O   |\n|_____O_|\n",
	" _______ \n| O   O |\n|       |\n|_O___O_|\n",
	" _______ \n| O   O |\n|   O   |\n|_O___O_|\n",
	" _______ \n| O   O |\n| O   O |\n|_O___O_|\n",
};

std::ostream& operator<<(std::ostream& stream, const Domino& one) {
	stream << images[one.Left()] << images[one.Right()];
	return stream;
}
std::ostream& operator<<(std::ostream& stream, const Bunch& one) {
	for (int i = 0; i < one.GetSize(); i++) {
		stream << one[i] << std::endl;
	}
	return stream;
}