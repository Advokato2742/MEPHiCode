#include "secondary-func.h"

int GetInt() {
	int value{};
	int scanf_value{};
	scanf_value = scanf("%d", &value);
	if (!scanf_value) {	
		scanf("%*[^\n]");
		std::cout << "Invalid input. Try again: ";
		return GetInt();
	}
	return value;
}

int GetFromInterval(int leftBorder, int rightBorder) {
	int number;
	number = GetInt();
	while (number < leftBorder || number > rightBorder) {
		std::cout << "Enter number from " << leftBorder << " to " << rightBorder << ": ";
		return GetFromInterval(leftBorder, rightBorder);
	}
	return number;
}