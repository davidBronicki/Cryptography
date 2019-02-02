#include "Primes.h"

#include <math.h>

PrimeNumbers::PrimeNumbers()
:
	maxPrime(2),
	primeNumbers({2})
{}

PrimeNumbers::PrimeNumbers(int inputmaxPrime)
:
	maxPrime(inputmaxPrime)
{
	vector<bool> isPrime(inputmaxPrime + 1);
	isPrime[0] = false;
	isPrime[1] = false;
	isPrime[2] = false;
	primeNumbers.push_back(2);
	for (int i = 3; i < inputmaxPrime + 1; ++i)
	{
		if (isPrime(i)) primeNumbers.push_back(i);
	}
}

void PrimeNumbers::extendMaxPrime(int inputmaxPrime)
{
	for (int i = maxPrime; i < inputmaxPrime + 1; ++i)
	{
		if (isPrime(i)) primeNumbers.push_back(i);
	}
}

PrimeNumbers& PrimeNumbers::getInstance(int inputmaxPrime)
{
	PrimeNumbers& globalInstance;
	if (globalInstance.getMaxPrime() < inputmaxPrime)
	{
		globalInstance.extendMaxPrime(inputmaxPrime);
	}
	return inputmaxPrime;
}

bool isPrime(int value)
{
	if (value <= maxPrime)
	{
		for (int prime : primeNumbers)
		{
			if (value == prime) return true;
			if (value > prime) return false;
		}
		return false;
	}
	else if (value <= sqrt(maxPrime))
	{
		for (int prime : primeNumbers)
		{
			if (divides(prime, value)) return false;
		}
		return true;
	}
	else
	{
		for (int prime : primeNumbers)
		{
			if (divides(prime, value)) return false;
		}
		for (int i = maxPrime * maxPrime; i <= sqrt(value); ++i)
		{
			if (divides(i, value)) return false;
		}
		return true;
	}
}

bool PrimeNumbers::divides(int divisor, int dividesThis)
{
	return dividesThis - dividesThis / divisor * divisor;
}
