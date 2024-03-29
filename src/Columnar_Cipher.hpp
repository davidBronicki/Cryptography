#pragma once

#include <string>
#include <vector>

#include "Encoding.hpp"

class ColumnarCipher
{
	Alphabet alphabet;
	std::vector<ModularNumber> key;
public:
	ColumnarCipher();
	ColumnarCipher(std::string inAlphabet, std::string inKey);
	std::string encrypt(std::string plainText);
	std::string decrypt(std::string cypherText);
	void setKey(std::string inputKey);
	std::string getKey();
};
