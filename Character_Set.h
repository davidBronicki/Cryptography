#pragma once

#include <string>
#include <vector>
#include <memory>

using namespace std;

class Character
{
	string alphabet;
	char letter;
	char numericValue;
	char charLookup(char numericValue) const;
	char numericValueLookup(char letter) const;
public:
	static string standardLowerCase, alphaNumeric,
		decimalSet, octalSet, hexSet;
	Character();
	Character(string inputAlphabet, char inputNumericValue);
	char getNumericValue() const;
	char getLetter() const;
	vector<Character> toAbstractCharacters(string inputString) const;
	string toString(vector<Character> abstractCharacters) const;
	Character& operator+=(const Character& other);
	Character& operator+=(char other);
	Character& operator-=(const Character& other);
	Character& operator-=(char other);
	Character& operator*=(const Character& other);
	Character& operator*=(char other);
	// Character& operator/=(const Character& other);
	// Character& operator/=(char other);
	Character& operator-();
};

Character operator+(Character left, const Character& right);
Character operator+(Character left, char right);
Character operator+(char left, Character right);
Character operator-(Character left, const Character& right);
Character operator-(Character left, char right);
Character operator-(char left, Character right);
Character operator*(Character left, const Character& right);
Character operator*(Character left, char right);
Character operator*(char left, Character right);
// Character operator/(Character left, const Character& right);
// Character operator/(Character left, char right);
// Character operator/(char left, const Character& right);