
//Affine_Shift_Cypher.h

#pragma once

#include <string>

#include "Encoding.h"

class AffineShiftCipher
{
	Alphabet alphabet;
	ModularNumber factor;
	ModularNumber shift;
public:
	AffineShiftCipher();
	AffineShiftCipher(std::string inputAlphabet, long long inputFactor, long long inputShift);
	std::string encrypt(std::string plainText) const;
	std::string decrypt(std::string cypherText) const;
	void setShift(long long input);
	void setMult(long long input);
	unsigned long long getShift() const;
	unsigned long long getMult() const;
};

