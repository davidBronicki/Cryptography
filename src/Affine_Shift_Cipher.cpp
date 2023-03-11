
//Affine_Shift_Cipher.cpp

#include "Affine_Shift_Cipher.hpp"

#include <vector>
#include <iostream>

using std::string, std::vector;

AffineShiftCipher::AffineShiftCipher()
:
	alphabet(""),
	factor(1ll, 1ll),
	shift(0ll, 1ll)
{}

AffineShiftCipher::AffineShiftCipher(
	string inputAlphabet, long long inputFactor, long long inputShift)
:
	alphabet(inputAlphabet),
	factor(inputAlphabet.length(), inputFactor),
	shift(inputAlphabet.length(), inputShift)
{}

string AffineShiftCipher::encrypt(string plainText) const
{

	auto modularValues = alphabet.forceStringToNumeric(plainText);
	vector<ModularNumber> output;
	for (auto value : modularValues)
	{
		output.push_back(value * factor + shift);
	}
	return alphabet.numericToString(output);
}

string AffineShiftCipher::decrypt(string cypherText) const
{
	auto modularValues = alphabet.forceStringToNumeric(cypherText);
	vector<ModularNumber> output;
	for (auto value : modularValues)
	{
		output.push_back((value - shift) / factor);
	}
	return alphabet.numericToString(output);
}

void AffineShiftCipher::setShift(long long input)
{
	shift = ModularNumber(alphabet.length(), input);
}

void AffineShiftCipher::setMult(long long input)
{
	ModularNumber test(alphabet.length(), input);
	ModularNumber(alphabet.length(), 1ll)/test;//will throw if there is no inverse
	factor = test;
}

unsigned long long AffineShiftCipher::getShift() const
{
	return (unsigned long long)shift;
}

unsigned long long AffineShiftCipher::getMult() const
{
	return (unsigned long long)factor;
}
