#pragma once

#include <string>
#include <vector>

#include "Encoding.h"

class ColumnarCypher
{
	Alphabet alphabet;
	std::vector<ModularNumber> key;
public:
	ColumnarCypher();
	ColumnarCypher(std::string inAlphabet, std::string inKey);
	std::string encrypt(std::string plainText);
	std::string decrypt(std::string cypherText);
	void setKey(std::string inputKey);
	std::string getKey();
};
