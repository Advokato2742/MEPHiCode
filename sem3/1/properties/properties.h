#pragma once
#include <string>
#include <vector>

/**
* @file
*/
/*!
* @brief creates a java properties format string from an array of integers and its name
* @param array of int which will turn into java properties string
* @param name std::string will turn into java properties string
* @returns std::string in java properties format
*/
std::string ToJavaProperties(const std::vector<int>& array, const std::string& name);
/*!
* @brief creates std::vector<int> from std::string in java properties format
* @param data std::string to translation from format
* @returns std::vector<int> java properties format
* @throws std::invalid_argument("incorrect line") if len of string less than 5
* @throws std::invalid_argument("Incorrect names") if string has incorrect format
* @throws std::invalid_argument("Incorrect numbers") if string has incorrect format
*/
std::vector<int> FromJavaProperties(const std::string& data);
/*!
* @brief creates std::vector<int> from char in java properties format
* @param data char* to translation from format
* @returns std::vector<int> java properties format
* @throws std::invalid_argument("incorrect line") if len of string less than 5
* @throws std::invalid_argument("Incorrect names") if string has incorrect format
* @throws std::invalid_argument("Incorrect numbers") if string has incorrect format
*/
std::vector<int> FromJavaProperties(const char* data);
/*!
* @brief creates std::vector<int> from char in java properties format
* @param data char* to translation from format
* @param size size_t length of *data
* @returns std::vector<int> java properties format
* @throws std::invalid_argument("incorrect line") if len of string less than 5
* @throws std::invalid_argument("Incorrect names") if string has incorrect format
* @throws std::invalid_argument("Incorrect numbers") if string has incorrect format
*/
std::vector<int> FromJavaProperties(const char* data, size_t size);