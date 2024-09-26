#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "properties.h"

std::string ToJavaProperties(const std::vector<int>& array, const std::string& name) {
	std::string res{};
	std::string new_name = (name.length() == 0) ? "array": name;
	for (int i = 0; i < array.size(); i++) {
		res += new_name + "." + std::to_string(i + 1) + "=" + std::to_string(array[i]) + "\n";
	}
	return res;
}

bool NameCheck(const std::vector<std::string>& names) {
	std::string first = names.size() > 0 ? names[0]: "";
	return std::all_of(names.begin(), names.end(), [&first](auto& s) { return first == s; });
}

bool IntCheck(const std::string& s) {
	return std::all_of(s.begin(), s.end(), [](auto& n) { return std::isdigit(n); });
}

bool NumberCheck(const std::vector<std::string>& arr) {
	return std::all_of(arr.begin(), arr.end(), IntCheck);
}

std::vector<int> FromJavaProperties(const std::string& data) {
	if (data.length() < 5) throw std::invalid_argument("incorrect line");
	std::string s = data + "\n";
	std::vector<std::string> arr;
	std::vector<std::string> names;
	int len = s.length();
	int begin = 0;
	while (begin < len - 1 && begin != std::string::npos) {
		int cur = s.find('.', begin);
		if (cur == len - 1 || cur == std::string::npos || cur < 0) {
			break;
		}
		names.push_back(s.substr(begin, cur - begin));

		begin = s.find('=', begin);
		if (begin == len - 1 || begin == std::string::npos) {
			break;
		}
		cur = s.find('\n', cur);
		arr.push_back(s.substr(begin + 1, cur - begin-1));
		begin = cur + 1;
	}

	if (!NameCheck(names)) {
		throw std::invalid_argument("Incorrect names");
	}
	if (!NumberCheck(arr)) {
		throw std::invalid_argument("Incorrect numbers");
	}
	std::vector<int> res;
	res.reserve(arr.size());
	std::transform(arr.begin(), arr.end(), std::back_inserter(res),
					[](const std::string& s) { return stoi(s); });
	return res;
}

std::vector<int> FromJavaProperties(const char* data) {
	return FromJavaProperties(std::string(data));
}

std::vector<int> FromJavaProperties(const char* data, size_t size) {
	return FromJavaProperties(std::string(data));
}