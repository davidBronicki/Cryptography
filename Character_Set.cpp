#include "Character_Set.h"

Character::Character()
{
	alphabet = "";
	numericValue = 0;
	letter = 0;
}

Character::Character(string inputAlphabet, char inputNumericValue)
{
	alphabet = inputAlphabet;
	numericValue = inputNumericValue;
	letter = alphabet[numericValue];
}

char Character::getNumericValue() const
{
	return numericValue;
}

char Character::getLetter() const
{
	return letter;
}

vector<Character> Character::toAbstractCharacters(string inputString) const
{
	vector<Character> output;
	for (char item : inputString)
	{
		output.push_back(Character(alphabet, numericValueLookup(item)));
	}
	return output;
}

string Character::toString(vector<Character> abstractCharacters) const
{
	string output;
	for (auto item : abstractCharacters)
	{
		output += item.getLetter();
	}
	return output;
}

char Character::charLookup(char numericValue) const
{
	return Character::alphabet[numericValue];
}

char Character::numericValueLookup(char letter) const
{
	for (char i = 0; i < alphabet.length(); ++i)
	{
		if (letter == alphabet[i]) return i;
	}
	return alphabet.length();
}

Character& Character::operator+=(const Character& other)
{
	return *this += other.numericValue;
}
Character& Character::operator+=(char other)
{
	numericValue += other;
	if (numericValue >= alphabet.length()) numericValue -= alphabet.length();
	letter = alphabet[numericValue];
	return *this;
}

Character& Character::operator-=(const Character& other)
{
	return *this -= other.numericValue;
}
Character& Character::operator-=(char other)
{
	numericValue -= other;
	if (numericValue >= alphabet.length()) numericValue += alphabet.length();
	letter = alphabet[numericValue];
	return *this;
}

Character& Character::operator*=(const Character& other)
{
	return *this *= other.numericValue;
}
Character& Character::operator*=(char other)
{
	int temp = numericValue;
	temp *= other;
	numericValue = temp - (temp / alphabet.length()) * alphabet.length();
	letter = alphabet[numericValue];
	return *this;
}

Character& Character::operator-()
{
	numericValue = alphabet.length()-numericValue;
	if (numericValue == alphabet.length()) numericValue = 0;
	letter = alphabet[numericValue];
	return *this;
}

string Character::standardLowerCase("abcdefghijklmnopqrstuvwxyz");
string Character::alphaNumeric("0123456789abcdefghijklmnopqrstuvwxyz");
string Character::decimalSet("0123456789");
string Character::octalSet("01234567");
string Character::hexSet("0123456789abcdef");


Character operator+(Character left, const Character& right)
{
	return left += right;
}
Character operator+(Character left, char right)
{
	return left += right;
}
Character operator+(char left, Character right)
{
	return right += left;
}

Character operator-(Character left, const Character& right)
{
	return left -= right;
}
Character operator-(Character left, char right)
{
	return left -= right;
}
Character operator-(char left, Character right)
{
	return -(right -= left);
}

Character operator*(Character left, const Character& right)
{
	return left *= right;
}
Character operator*(Character left, char right)
{
	return left *= right;
}
Character operator*(char left, Character right)
{
	return right *= left;
}
