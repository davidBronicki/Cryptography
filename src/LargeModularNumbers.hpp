#pragma once

#include "LargeNumbers.hpp"

template<size_t bit32Length>
class LargeModularNumber
{
	typedef LargeNumber<bit32Length> ul;//actual size of data
	typedef LargeNumber<bit32Length * 2> ull;//size used for arithmetic purposes
	typedef LargeModularNumber<bit32Length> modNum;
	ull base;//base of the modular arithmetic
	ull value;//0 <= value < base
	void buildInverse();
	typedef std::tuple<ul, ul, ul, bool> vec3;//last value true means 3rd value negative,
	//last value false means 2nd value negative

	static void advancedEuclideanAlgorithmRecursive(vec3& n, vec3& m)
	{
		//if we reached zero, return previous value
		if (std::get<0>(m) == ul::zero()) return;//value in n position (m solved for zero)

		{
			ul quotient = std::get<0>(n) / std::get<0>(m);
			vec3 remainder(
				std::get<0>(n) - std::get<0>(m) * quotient,
				std::get<1>(n) + std::get<1>(m) * quotient,
				std::get<2>(n) + std::get<2>(m) * quotient,
				std::get<3>(n));//sign always switches so we want to
				//use !(most recent value), so !std::get<3>(m).
				//however because it is alternating throughout,
				//we can instead use std::get<3>(n).
			n = m;
			m = remainder;
		}
		advancedEuclideanAlgorithmRecursive(n, m);
	}

	//user side entry point
	static vec3 advancedEuclideanAlgorithm(ul n, ul m)
	{
		vec3 a(n, ul::unity(), ul::zero(), true);
		vec3 b(m, ul::zero(), ul::unity(), false);
		advancedEuclideanAlgorithmRecursive(a, b);
		return a;
	}
public:
	LargeModularNumber(const ul& inValue, const ul& inBase)
	:
		base(inBase),
		value(inValue)
	{}

	modNum inverse() const//returns multiplicative inverse
	{
		vec3 euclidResult(advancedEuclideanAlgorithm(ul(value), ul(base)));
		if (std::get<0>(euclidResult) == ul::unity())
		{
			if (std::get<3>(euclidResult))
			{
				return modNum(std::get<1>(euclidResult), base);
			}
			else
			{
				modNum temp(std::get<1>(euclidResult), base);
				return -temp;
			}
		}
		else
		{
			throw std::domain_error("Modular Division by Zero Divisor");
		}
	}
	
	modNum operator-() const
	{
		return modNum(
			value == value + value ? value : base - value, base);
	}

	modNum& operator+=(const modNum& other)
	{
		value += other.value;
		if (value >= base) value -= base;
		return *this;
	}

	modNum& operator-=(const modNum& other)
	{
		value += base - other.value;
		if (value >= base) value -= base;
		return *this;
	}

	modNum& operator*=(const modNum& other)
	{
		value *= other.value;
		value %= base;
		return *this;
	}

	modNum& exponentiate(const ul& exponent)
	{
		modNum binaryExponent(*this);
		*this = modNum(ul::unity(), base);
		unravelledForLoop<bit32Length>([this, &binaryExponent, &exponent](size_t i)
		{
			unravelledForLoop<32>([this, &binaryExponent, &exponent, &i](size_t j)
			{
				if ((unsigned long long)((exponent >> (i * 32 + j)) & ul::unity()))//check if ith bit is on
				{
					operator*=(binaryExponent);
				}
				binaryExponent *= binaryExponent;
			});
		});
		return *this;
	}

	operator ul() const
	{
		return (ul)value;
	}
};

template<size_t bit32Length>
LargeModularNumber<bit32Length> operator+(
	LargeModularNumber<bit32Length> left, const LargeModularNumber<bit32Length>& right)
{
	return left += right;
}
template<size_t bit32Length>
LargeModularNumber<bit32Length> operator-(
	LargeModularNumber<bit32Length> left, const LargeModularNumber<bit32Length>& right)
{
	return left -= right;
}
template<size_t bit32Length>
LargeModularNumber<bit32Length> operator*(
	LargeModularNumber<bit32Length> left, const LargeModularNumber<bit32Length>& right)
{
	return left *= right;
}
template<size_t bit32Length>
LargeModularNumber<bit32Length> operator/(
	LargeModularNumber<bit32Length> left, const LargeModularNumber<bit32Length>& right)
{
	return left /= right;
}


