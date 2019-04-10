#pragma once

// #include <tuple>

#include "LargeNumbers.h"

template<size_t bit32Length>
class LargeModularNumber
{
	typedef LargeNumber<bit32Length> ul;//actual size of data
	typedef LargeNumber<bit32Length * 2> ull;//size used for arithmetic purposes
	typedef LargeModularNumber<bit32Length> modNum;
	ull base;//base of the modular arithmetic
	ull value;//0 <= value < base
	void buildInverse();
	typedef tuple<ul, ul, ul, bool> vec3;//last value true means 3rd value negative,
	//last value false means 2nd value negative

	static void advancedEuclideanAlgorithmRecursive(vec3& n, vec3& m)
	{
		// static int i = 0;
		//if we reached zero, return previous value
		if (get<0>(m) == ul::zero()) return;//value in n position (m solved for zero)

		{
			// ++i;
			// if (i < 3)
			// {
			// 	cout << (get<0>(n) > get<0>(m)) << endl;
			// }
			// if (i > 1000)
			// {
			// 	cout << i << endl;
			// 	cout << get<0>(n) << endl << endl;
			// 	cout << get<0>(m) << endl << endl;
			// 	cout << (get<0>(n) / get<0>(m)) << endl << endl << endl;
			// 	// cout << (get<0>(n) > get<0>(m)) << endl << endl << endl;
			// }
			// cout << get<0>(n) << endl << endl;
			ul quotient = get<0>(n) / get<0>(m);
			vec3 remainder(
				get<0>(n) - get<0>(m) * quotient,
				get<1>(n) + get<1>(m) * quotient,
				get<2>(n) + get<2>(m) * quotient,
				get<3>(n));//sign always switches so we want to
				//use !(most previous value), so !get<3>(m).
				//however because it is alternating throughout,
				//we can instead use get<3>(n).
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
		// return advancedEuclideanAlgorithmRecursive(
		// 	vec3(n, ul(1u), ul(0u), true), vec3(m, ul(0u), ul(1u), false));
	}
public:
	LargeModularNumber(const ul& inValue, const ul& inBase)
	:
		value(inValue),
		base(inBase)
	{}

	modNum inverse() const//returns multiplicative inverse
	{
		// vec3 euclidResult(advancedEuclideanAlgorithm(ul(value), ul(base)));
		vec3 euclidResult(advancedEuclideanAlgorithm(ul(base), ul(value)));
		if (get<0>(euclidResult) == ul::unity())
		{
			if (get<3>(euclidResult))
			{
				return modNum(get<1>(euclidResult), base);
			}
			else
			{
				modNum temp(get<1>(euclidResult), base);
				return -temp;
			}
		}
		else
		{
			throw domain_error("Modular Division by Zero Divisor");
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
			// if ((unsigned long long)((exponent >> i) & ul::unity()))//check if ith bit is on
			// {
			// 	operator*=(binaryExponent);
			// }
			// binaryExponent *= binaryExponent;
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


