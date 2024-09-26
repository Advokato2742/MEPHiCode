#include <iostream>
#include "ui.h"
#include "../properties/properties.h"
#include <stdexcept>
#include <limits>

int ReadInt() {
	int tmp;
	std::cin >> tmp;
	while (!std::cin.good()) {
		if (std::cin.bad()) {
			throw std::invalid_argument("bad stream");
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<size_t>::max(), '\n');
		std::cin >> tmp;
	}
	return tmp;
}

std::string GetParams() {
	std::string str = "";
	std::cout << "please enter a count of elements" << std::endl;
	int n = ReadInt();
	std::cout << "please enter your properties line by line" << std::endl;
	int count = 0;
	std::string tmp;
	getchar();
	while (count < n) {
		getline(std::cin, tmp);
		str += tmp + "\n";
		count++;
	}
	return str;
}

void GetParams(std::string& name, std::vector<int>& array) {
	std::cout << "please enter a name of your array" << std::endl;
	std::cin >> name;
	std::cout << "please enter a count of elements" << std::endl;
	int n = ReadInt();
	std::cout << "please enter elements" << std::endl;
	int count = 0;
	array.reserve(n);
	while (count < n) {
		array.push_back(ReadInt());
		count++;
	}
}

void UI() {
	std::cout << "hello" << std::endl;
	bool flag = true;
	while (flag) {
		std::cout << "choose option:\n1 - properties to array\n2 - array to properties\n0 - exit" << std::endl;
		int option = ReadInt();
		switch (option) {
		case 0:
			flag = false;
			break;
		case 1: {
			std::string tmp;
			tmp = GetParams();
			std::cout << "your string:" << std::endl;
			std::cout << tmp << std::endl;
			std::vector<int> ans = FromJavaProperties(tmp);
			std::cout << "array:" << std::endl;
			for (auto i: ans) {
				std::cout << i << " ";
			}
			std::cout << std::endl;
			break;
		}
		case 2: {
			std::string tmp;
			std::vector<int> arr;
			GetParams(tmp, arr);
			std::cout << "your input: " << tmp << std::endl;
			for (auto i: arr) {
				std::cout << i << " ";
			}
			std::cout << std::endl;
			std::string res = ToJavaProperties(arr, tmp);
			std::cout << "properties:" <<std::endl;
			std::cout << res << std::endl;
		}
		}
	}
}