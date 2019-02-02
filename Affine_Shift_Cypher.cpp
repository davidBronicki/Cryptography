#include "Affine_Shift_Cypher.h"

#include <vector>
#include <iostream>

AffineShiftCypher::AffineShiftCypher(
	string inputAlphabet, int inputFactor, int inputShift)
:
	alphabet(inputAlphabet),
	factor(inputAlphabet, inputFactor),
	shift(inputAlphabet, inputShift)
{}

string AffineShiftCypher::encrypt(string plainText) const
{
	auto temp = factor.toAbstractCharacters(plainText);
	vector<Character> output;
	for (auto item : temp)
	{
		output.push_back(item * factor + shift);
	}
	return factor.toString(output);
}

string AffineShiftCypher::decrypt(string cypherText) const
{
	return cypherText;//not implemented (need division)
}

void AffineShiftCypher::setShift(int input)
{
	shift = Character(alphabet, input);
}

void AffineShiftCypher::setMult(int input)
{
	factor = Character(alphabet, input);
}

int AffineShiftCypher::getShift() const
{
	return shift.getNumericValue();
}

int AffineShiftCypher::getMult() const
{
	return factor.getNumericValue();
}
