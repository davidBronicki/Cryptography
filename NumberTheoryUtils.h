
//NumberTheoryUtils.h

#pragma once

#include <tuple>
#include <vector>

namespace NumberTheoreticUtils
{
	//---------------------------prime numbers segment--------------------------------

	//Singleton class for prime number generation and prime number utilities.
	//Only one instance of this exists at run time and it exists as
	//a static variable in a static method (PrimeNumbers::getInstance(ull maxPrimeValue))
	//For convenience, brief named functions exist for the purpose of calling this
	//function, namely primes() and primes(ull length).

	typedef unsigned long long ull;

	class PrimeNumbers
	{
		ull maxPrime;
		std::vector<ull> primeNumbers;
		void extendMaxPrime(ull inputMaxPrime);//used to increase the max prime number
		std::vector<ull> reverseFactorize(ull value) const;//middle step for factorize(ull value)
		PrimeNumbers(ull maxPrimeValue);//executed exactly once
	public:
		static PrimeNumbers& getInstance(ull maxPrimeValue);//get reference to singleton object
		bool isPrime(ull value) const;//check if value is prime
		std::vector<ull> factorize(ull value) const;//return ordered list of factors with repeats
		std::vector<ull> uniqueFactors(ull value) const;//ordered list without repeats
		PrimeNumbers() = delete;//singleton design pattern
		PrimeNumbers(const PrimeNumbers& value) = delete;//singleton design pattern
		void operator=(const PrimeNumbers& value) = delete;//singleton design pattern
	};

	inline PrimeNumbers& primes(ull length)//abreviated version of getInstance
	{
		return PrimeNumbers::getInstance(length);
	}

	inline PrimeNumbers& primes()//after first instantiation, specifying maxPrime isn't necessary
	{
		return PrimeNumbers::getInstance(2);
	}

	//--------------------------end of prime numbers segment-------------------------------

	std::tuple<long long, long long, long long>
		advancedEuclideanAlgorithm(long long n, long long m);

	bool divides(long long a, long long b);
}

namespace ntu = NumberTheoreticUtils;
