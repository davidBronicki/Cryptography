#pragma once

#include "ModularUtils.hpp"

#include <vector>
#include <string>

class Alphabet
{
	typedef unsigned long long ull;
	std::string alphabet;
	std::vector<ull> inverseValues;
public:
	Alphabet(const std::string& inAlphabet);
	char numericToChar(const ull input) const;
	char numericToChar(const long long input) const;
	char numericToChar(const ModularNumber& input) const;
	std::string numericToString(const std::vector<ull>& input) const;
	std::string numericToString(const std::vector<long long>& input) const;
	std::string numericToString(const std::vector<ModularNumber>& input) const;
	ModularNumber charToNumeric(char input) const;
	std::vector<ModularNumber> stringToNumeric(const std::string& input) const;
	std::vector<ModularNumber> forceStringToNumeric(const std::string& input) const;
	size_t length() const;
};

class ASCII_Encoder
{
public:
	ASCII_Encoder() = delete;
	static std::vector<unsigned int> encode(std::string plainText, size_t targetSize);
	static std::string decode(const std::vector<unsigned int>& code);
};
