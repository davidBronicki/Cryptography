#include "Affine_Shift_Cypher.h"

#include <vector>
#include <iostream>

using namespace std;

AffineShiftCypher::AffineShiftCypher(
	string inputAlphabet, long long inputFactor, long long inputShift)
:
	alphabet(inputAlphabet),
	factor(inputAlphabet.length(), inputFactor),
	shift(inputAlphabet.length(), inputShift)
{}

string AffineShiftCypher::encrypt(string plainText) const
{
	auto modularValues = alphabet.stringToNumeric(plainText);
	vector<ModularNumber> output;
	for (auto value : modularValues)
	{
		output.push_back(value * factor + shift);
	}
	return alphabet.numericToString(output);
}

string AffineShiftCypher::decrypt(string cypherText) const
{
	auto modularValues = alphabet.stringToNumeric(cypherText);
	vector<ModularNumber> output;
	for (auto value : modularValues)
	{
		output.push_back((value - shift) / factor);
	}
	return alphabet.numericToString(output);
}

void AffineShiftCypher::setShift(long long input)
{
	shift = ModularNumber(alphabet.length(), input);
}

void AffineShiftCypher::setMult(long long input)
{
	ModularNumber test(alphabet.length(), input);
	ModularNumber(alphabet.length(), 1ll)/test;//will throw if there is no inverse
	factor = test;
}

unsigned long long AffineShiftCypher::getShift() const
{
	return (unsigned long long)shift;
}

unsigned long long AffineShiftCypher::getMult() const
{
	return (unsigned long long)factor;
}
