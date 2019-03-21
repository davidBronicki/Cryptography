
//Encoding.cpp

#include "Encoding.h"
// #include "ModularUtils.h"

#include <stdexcept>

using namespace std;

Alphabet::Alphabet(const std::string& inAlphabet)
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
		throw domain_error("alphabet length does not match modular base");
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
	throw invalid_argument("char input does not exist in alphabet");
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
		catch (invalid_argument e)
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
