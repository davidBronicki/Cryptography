#pragma once

#include <vector>

using namespace std;

class PrimeNumbers
{
	int maxPrime;
	vector<int> primeNumbers;
	int getMaxPrime() const;
	void extendMaxPrime(int inputMaxPrime);
	PrimeNumbers();
	PrimeNumbers(int maxPrimeValue);
public:
	static PrimeNumbers& getInstance(int maxPrimeValue);
	bool isPrime(int value) const;
	vector<int> factorize(int value) const;
	static bool divides(int divisor, int dividesThis);
	PrimeNumbers() = delete;
	PrimeNumbers(const PrimeNumbers&  value) = delete;
	void operator=(const PrimeNumbers& value) = delete;
}
