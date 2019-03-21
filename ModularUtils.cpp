
//ModularUtils.cpp

#include "ModularUtils.h"

#include <exception>
#include <vector>

#include "NumberTheoryUtils.h"

using namespace std;

ModularNumber::ModularNumber()
:
	base(1),
	value(0),
	inverseValue(0)
{}

ModularNumber::ModularNumber(ull inBase, ull inValue)
:
	base(inBase),
	value(inValue%inBase)
{
	buildInverse();
}

ModularNumber::ModularNumber(ull inBase, long long inValue)
:
	base(inBase),
	value((ull)(inValue%((long long)inBase)))
{
	if (value > 0xf0000000)
	{
		value += inBase;
	}
	buildInverse();
}

ModularNumber::ModularNumber(ull inBase, ull inValue, ull inInverse)
:
	base(inBase),
	value(inValue),
	inverseValue(inInverse)
{}

ModularNumber::ull ModularNumber::getBase() const
{
	return base;
}

void ModularNumber::buildInverse()
{
	auto gcdData(ntu::advancedEuclideanAlgorithm(value, base));
	if (get<0>(gcdData) == 1)
	{
		if (get<1>(gcdData) < 0)
		{
			inverseValue = get<1>(gcdData) + base;
		}
		else
		{
			inverseValue = get<1>(gcdData);
		}
	}
	else
	{
		inverseValue = 0;//no inverse state
	}
}

bool ModularNumber::operator<(const ModularNumber& other) const
{
	return value < other.value;
}

ModularNumber ModularNumber::operator-() const
{
	return ModularNumber(base, base - value, base - inverseValue);
}

ModularNumber ModularNumber::inverse() const
{
	if (inverseValue == 0)
	{
		throw domain_error("Modular Division by Zero Divisor");
	}
	return ModularNumber(base, inverseValue, value);
}

ModularNumber& ModularNumber::operator+=(const ModularNumber& other)
{
	if (base != other.base)
	{
		throw domain_error("Modular Base Mismatch in Addition Function");
	}
	value += other.value;
	if (value >= base) value -= base;
	buildInverse();
	return *this;
}

ModularNumber& ModularNumber::operator-=(const ModularNumber& other)
{
	return *this += -other;//I'm somewhat lazy
}

ModularNumber& ModularNumber::operator*=(const ModularNumber& other)
{
	if (base != other.base)
	{
		throw domain_error("Modular Base Mismatch in Multiplication Function");
	}
	value *= other.value;
	value %= base;
	inverseValue *= other.inverseValue;
	inverseValue %= base;
	return *this;
}

ModularNumber& ModularNumber::operator/=(const ModularNumber& other)
{
	return *this *= other.inverse();
}

ModularNumber ModularNumber::exponentiate(ull exponent)
{
	ModularNumber output(base, 1ull);
	ModularNumber binaryExponent(*this);
	for (int i = 0; i < 64; ++i)
	{
		if ((exponent >> i) & 1)//check if ith bit is on
		{
			output *= binaryExponent;
		}
		if ((exponent >> i+1) == 0) break;//check if any significant bits left
		binaryExponent *= binaryExponent;
	}
	return output;
}

ModularNumber::operator ModularNumber::ull() const
{
	return value;
}
