#pragma once
#include "seq.h"

int GetInt(void);
int GetFromInterval(int, int);

template <class T>
void PrintElement(const int index, const Sequence<T>* array) {
    T element = array->GetElement(index);
    std::cout << element;
}

template <class T>
void Print(const Sequence<T>* array) {
    if (!array->GetLength()) {
    	std::cout << "empty" << std::endl;
    	return;
    }
    for (int i = 0; i < array->GetLength(); i++) {
    	PrintElement(i, array);
	    std::cout << " ";
    }
    std::cout << std::endl;
}

template<class T>
void PrintOptions(Sequence<T>* list, int count) {
	const int colscount = 2;
	const int celllength = 22;
	int rowscount = count / colscount;
	int n, m = 0;
	for (int i = 0; i < count; i++) {
		std::cout << "|";
        PrintElement(i, list);
		n = list->GetElement(i).size();
		for (int j = 0; j < celllength-n; j++)
			std::cout << " ";
		std::cout << "|";
		m++;
		if (colscount % m == 0 && m != 1) {
			std::cout << std::endl;
			m = 0;
		}
	}
	if (count % colscount != 0)
		std::cout << std::endl;
	return;
}
