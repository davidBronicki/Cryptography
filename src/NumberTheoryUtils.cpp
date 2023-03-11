
//NumberTheoryUtils.cpp

#include "NumberTheoryUtils.hpp"

#include <math.h>
#include <iostream>

using namespace std;
using namespace ntu;

typedef tuple<long long, long long, long long> vec3;

vec3 advancedEuclideanAlgorithmRecursive(vec3 n, vec3 m)
{
	//if we reached zero, return previous value
	if (get<0>(m) == 0) return n;
	else
	{
		long long quotient = get<0>(n) / get<0>(m);
		vec3 remainder(
			get<0>(n) - get<0>(m) * quotient,
			get<1>(n) - get<1>(m) * quotient,
			get<2>(n) - get<2>(m) * quotient);
		//continue process
		return advancedEuclideanAlgorithmRecursive(m, remainder);
	}
}

//user side entry point
vec3 ntu::advancedEuclideanAlgorithm(long long n, long long m)
{
	return advancedEuclideanAlgorithmRecursive(
		vec3(n, 1, 0), vec3(m, 0, 1));
}

bool ntu::divides(long long a, long long b)
{
	return a%b == 0;
}


//---------------------prime numbers segment--------------------


PrimeNumbers::PrimeNumbers(ull inputmaxPrime)
:
	maxPrime(inputmaxPrime)
{
	//Sieve of Eratosthenes
	vector<bool> isPrime(inputmaxPrime + 1, true);
	isPrime[0] = false;
	isPrime[1] = false;
	for (ull i = 0; i < inputmaxPrime + 1; ++i)
	{
		if (isPrime[i])
		{
			for (ull j = 2 * i; j < inputmaxPrime + 1; j += i)
			{
				isPrime[j] = false;
			}
		}
	}
	for (ull i = 0; i < inputmaxPrime + 1; ++i)
	{
		if (isPrime[i]) primeNumbers.push_back(i);
	}
}

void PrimeNumbers::extendMaxPrime(ull inputmaxPrime)
{
	for (ull i = maxPrime; i < inputmaxPrime + 1; ++i)
	{
		if (isPrime(i)) primeNumbers.push_back(i);
	}
}

PrimeNumbers& PrimeNumbers::getInstance(ull inputmaxPrime)
{
	static PrimeNumbers globalInstance(inputmaxPrime);//only called first time through
	if (globalInstance.maxPrime < inputmaxPrime)
	{
		globalInstance.extendMaxPrime(inputmaxPrime);
	}
	return globalInstance;
}

bool PrimeNumbers::isPrime(ull value) const
{
	if (value <= maxPrime)//if in prime pool, we can do a binary search
	{
		for (ull prime : primeNumbers)
		{
			if (value == prime) return true;
			if (value > prime) return false;
		}
		return false;
	}
	else if (value <= sqrt(maxPrime))//if sqrt in prime pool, we can check divisibility
	{
		for (ull prime : primeNumbers)
		{
			if (divides(prime, value)) return false;
		}
		return true;
	}
	else//if above square of prime pool, must check each value above prime pool (inefficient)
	{
		for (ull prime : primeNumbers)
		{
			if (divides(prime, value)) return false;
		}
		for (ull i = maxPrime * maxPrime; i <= sqrt(value); ++i)
		{
			if (divides(i, value)) return false;
		}
		return true;
	}
}

vector<ull> PrimeNumbers::reverseFactorize(ull value) const
{
	//The value checked gets appended to the back of a recursion call.
	//Since the values are checked in accending order, this results
	//in the return being in decending order.
	//This algorithm is somewhat inefficient.
	if (value == 1) return vector<ull>();
	for (ull prime : primeNumbers)
	{
		if (divides(prime, value))
		{
			auto temp = reverseFactorize(value / prime);
			temp.push_back(prime);
			return temp;
		}
	}
	return vector<ull>();
}

vector<ull> PrimeNumbers::factorize(ull value) const
{
	auto temp = reverseFactorize(value);
	vector<ull> output;
	for (auto it = temp.end() - 1; it != temp.begin() - 1; --it)
	{
		output.push_back(*it);
	}
	return output;
}

vector<ull> PrimeNumbers::uniqueFactors(ull value) const
{
	auto factors = factorize(value);
	if (factors.size() == 0) return factors;
	vector<ull> output({factors[0]});
	for (ull factor : factors)
	{
		if (factor == output.back()) continue;
		output.push_back(factor); 
	}
	return output;
}


//------------------end of prime numbers segment---------------------

