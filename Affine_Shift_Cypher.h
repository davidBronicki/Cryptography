#pragma once

#include <string>

#include "Character_Set.h"

using namespace std;

class AffineShiftCypher
{
	string alphabet;
	Character factor;
	Character shift;
public:
	AffineShiftCypher(string inputAlphabet, int inputFactor, int inputShift);
	string encrypt(string plainText) const;
	string decrypt(string cypherText) const;
	void setShift(int input);
	void setMult(int input);
	int getShift() const;
	int getMult() const;
};

