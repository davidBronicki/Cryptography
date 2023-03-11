
//Encoding.cpp

#include "Encoding.hpp"
// #include "ModularUtils.h"

#include <stdexcept>

using std::string, std::vector;

Alphabet::Alphabet(const string& inAlphabet)
:
	alphabet(inAlphabet)
{
	for (ull i = 0; i < alphabet.length(); ++i)
	{
		inverseValues.push_back(
			ModularNumber(alphabet.length(), i).inverseValue);
	}
}

char Alphabet::numericToChar(const ull input) const
{
	return alphabet[input%(alphabet.length())];
}

char Alphabet::numericToChar(const long long input) const
{
	return alphabet[input%(alphabet.length())];
}

char Alphabet::numericToChar(const ModularNumber& input) const
{
	if (input.getBase() != alphabet.length())
	{
		throw std::domain_error("alphabet length does not match modular base");
	}
	return alphabet[input.value];
}

string Alphabet::numericToString(const vector<ull>& input) const
{
	string output;
	for (auto number : input)
	{
		output += numericToChar(number);
	}
	return output;
}

string Alphabet::numericToString(const vector<long long>& input) const
{
	string output;
	for (auto number : input)
	{
		output += numericToChar(number);
	}
	return output;
}

string Alphabet::numericToString(const vector<ModularNumber>& input) const
{
	string output;
	for (auto number : input)
	{
		output += numericToChar(number);
	}
	return output;
}

ModularNumber Alphabet::charToNumeric(char input) const
{
	for (ull i = 0; i < alphabet.length(); ++i)
	{
		if (alphabet[i] == input)
		{
			return ModularNumber(alphabet.length(),
				i, inverseValues[i]);
		}
	}
	throw std::invalid_argument("char input does not exist in alphabet");
}

vector<ModularNumber> Alphabet::stringToNumeric(const string& input) const
{
	vector<ModularNumber> output;
	for (auto letter : input)
	{
		output.push_back(charToNumeric(letter));
	}
	return output;
}

vector<ModularNumber> Alphabet::forceStringToNumeric(const string& input) const
{
	vector<ModularNumber> output;
	for (auto letter : input)
	{
		try
		{
			output.push_back(charToNumeric(letter));
		}
		catch (std::invalid_argument e)
		{
			continue;
		}
	}
	return output;
}

size_t Alphabet::length() const
{
	return alphabet.length();
}





vector<unsigned int> ASCII_Encoder::encode(string plainText, size_t targetSize)
{
	int lengthDifference = targetSize - plainText.length();
	if (lengthDifference < 0)
	{
		plainText = plainText.substr(-lengthDifference);
	}
	else
	{
		string temp(lengthDifference, '\0');
		plainText = temp + plainText;
	}
	const char* cString = plainText.c_str();
	unsigned int * data = (unsigned int *)(cString);
	vector<unsigned int> check(data, data + targetSize/sizeof(unsigned int));
	return check;
	// return vector<unsigned int>(data, data + targetSize);
}

string ASCII_Encoder::decode(const vector<unsigned int>& code)
{
	const unsigned int * data= code.data();
	char* cString = (char*)(data);
	return string(cString, code.size() * sizeof(unsigned int));
}
