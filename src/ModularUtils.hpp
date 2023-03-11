#pragma once

class Alphabet;

class ModularNumber
{
	typedef unsigned long long ull;
	ull base;//base of the modular arithmetic
	ull value;//0 <= value < base
	ull inverseValue;//(inverse * value) mod base = 1
	void buildInverse();
	friend Alphabet;
	// ModularNumber(ull inBase, ull inValue, ull inInverse);
	// //specifying inverse in constructor is restricted to
	// //private so an incorrect value can't be given
public:
	ModularNumber();
	ModularNumber(ull inBase, ull inValue, ull inInverse);
	ModularNumber(ull inBase, ull inValue);
	ModularNumber(ull inBase, long long inValue);

	ull getBase() const;
	bool operator<(const ModularNumber& other) const;//to allow for sorting (and alphabetizing)
	ModularNumber inverse() const;//returns multiplicative inverse
	
	ModularNumber operator-() const;
	template<typename T>
	ModularNumber& operator+=(T other);
	ModularNumber& operator+=(const ModularNumber& other);
	template<typename T>
	ModularNumber& operator-=(T other);
	ModularNumber& operator-=(const ModularNumber& other);
	template<typename T>
	ModularNumber& operator*=(T other);
	ModularNumber& operator*=(const ModularNumber& other);
	template<typename T>
	ModularNumber& operator/=(T other);
	ModularNumber& operator/=(const ModularNumber& other);

	ModularNumber exponentiate(ull exponent);

	operator ull() const;
};

template<typename T>
ModularNumber& ModularNumber::operator+=(T other)
{
	return operator+=(ModularNumber(base, other));
}
template<typename T>
ModularNumber& ModularNumber::operator-=(T other)
{
	return operator-=(ModularNumber(base, other));
}
template<typename T>
ModularNumber& ModularNumber::operator*=(T other)
{
	return operator*=(ModularNumber(base, other));
}
template<typename T>
ModularNumber& ModularNumber::operator/=(T other)
{
	return operator/=(ModularNumber(base, other));
}




template<typename T>
ModularNumber operator+(ModularNumber left, const T& right)
{
	return left += right;
}
template<typename T>
ModularNumber operator-(ModularNumber left, const T& right)
{
	return left -= right;
}
template<typename T>
ModularNumber operator*(ModularNumber left, const T& right)
{
	return left *= right;
}
template<typename T>
ModularNumber operator/(ModularNumber left, const T& right)
{
	return left /= right;
}
