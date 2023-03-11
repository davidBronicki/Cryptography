#pragma once

#include "LargeNumbers.hpp"
#include "LargeModularNumbers.hpp"

#include <cstdlib>

template<size_t bit32Length>
LargeNumber<bit32Length> generateRandomNumber(
	const LargeNumber<bit32Length>& smallEnd,
	const LargeNumber<bit32Length>& largeEnd)
{
	typedef LargeNumber<bit32Length> num;
	num range(largeEnd - smallEnd);
	num ratio(num::maxInt() / range);

	while(true)
	{
		std::vector<unsigned int> data;
		for (int i = 0; i < bit32Length; ++i)
		{
			data.push_back(rand());
		}
		num testPoint(data);
		testPoint /= ratio;
		testPoint += smallEnd;
		if (testPoint <= largeEnd) return testPoint;
	}
}

template<size_t bit32Length>
std::vector<LargeNumber<bit32Length>> buildTestCases(
	const LargeNumber<bit32Length>& maxSize,
	const size_t& count)
{
	std::vector<LargeNumber<bit32Length>> output(0);
	for (int i = 0; i < count; ++i)
	{
		output.push_back(generateRandomNumber(
			LargeNumber<bit32Length>::unity(),
			maxSize - LargeNumber<bit32Length>::unity()));
	}
	return output;
}

template<size_t bit32Length>
bool isPrime(const LargeNumber<bit32Length>& input)
{
	//Miller-Rabin Primality test

	//This is a strong probabilistic primality test.
	//This means there is some maximum probability, P,
	//(for this test P=1/4) such that for every
	//witness, a, the chance of a false positive
	//is less than P. The full test checks against
	//several witnesses, so that for k witnesses,
	//the false positive probability is guaranteed
	//to be less than P^k.

	//presumably the input is odd. (this function breaks if given an even number)
	//call the input n, and let n = d * 2^s + 1 where d is odd.
	//If n is prime, then d*2^s is the totient of n and so for any
	//a in Z_n, a**(d*2^s) = 1_n. By properties of squareroots on finite
	//fields (namely that the squareroot of 1 is +-1), we have either
	//a**d = 1_n
	//or
	//a**(d*2^r) = -1_n
	//for some r satisfying 0 <= r < s. This can be seen
	//by starting with a**(d*2^s) (which is one) and repeatedly
	//squarerooting. We will either reach a point where we get a -1,
	//thereby satisfying the second condition, or we will go all the way
	//through without seeing a 1, thereby satisfying the first condition.
	//The Miller-Rabin test checks if this condition is true for some
	//witness a.

	typedef LargeNumber<bit32Length> num;
	typedef LargeModularNumber<bit32Length> modNum;

	num totientOddValue(input - num::unity());//possibly the totient
	size_t powersOfTwo = 0;
	while (!(unsigned long long)(totientOddValue & num::unity()))
	{
		//if the last bit is not a 1 then totientOddValue
		//is even and we need to remove another power of two
		totientOddValue >>= 1u;
		++powersOfTwo;
	}

	static std::vector<num> testCases(buildTestCases(input, 10));

	for (auto testCase : testCases)
	{
		modNum witness(testCase, input);
		witness.exponentiate(totientOddValue);
		if ((num)witness == num::unity()) continue;
		if ((num)(-witness) == num::unity()) continue;
		bool found = false;
		for (int i = 0; i < powersOfTwo - 1; ++i)
		{
			witness *= witness;
			if ((num(-witness) == num::unity()))
			{
				found = true;
				break;
			}
		}
		if (found) continue;
		return false;
	}
	return true;
}

const unsigned int buildPreSieveProduct(const std::vector<unsigned int>& primes)
{
	int preSieveProduct = 1;
	for (auto i : primes)
	{
		preSieveProduct *= i;
	}
	return preSieveProduct;
}

const std::vector<unsigned int> buildDropLength(const std::vector<unsigned int>& primes, const int& product)
{
	std::vector<bool> sieve(product, true);
	sieve[0] = false;
	sieve[1] = false;
	for (int i = 2; i < product; ++i)
	{
		for (auto prime : primes)
		{
			if (i % prime == 0)
			{
				sieve[i] = false;
			}
		}
	}
	std::vector<unsigned int> relativePrimes;
	for (int i = 0; i < sieve.size(); ++i)
	{
		if (sieve[i]) relativePrimes.push_back(i);
	}
	std::vector<unsigned int> dropLengths;
	for (int i = relativePrimes.size() - 1; i > 0; --i)
	{
		dropLengths.push_back(relativePrimes[i] - relativePrimes[i - 1]);
	}
	dropLengths.push_back(2);
	return dropLengths;
}

template<size_t bit32Length>
LargeNumber<bit32Length> generatePrime(const LargeNumber<bit32Length>& maxSize)
{
	typedef LargeNumber<bit32Length> num;
	const static std::vector<unsigned int> preSievePrimes{2, 3, 5, 7, 11, 13, 17, 19};
	// const static vector<unsigned int> preSievePrimes{2, 3, 5, 7, 11};
	const static num preSieveProduct(buildPreSieveProduct(preSievePrimes));
	const static std::vector<unsigned int> dropLength(buildDropLength(preSievePrimes, preSieveProduct));

	num testPoint(generateRandomNumber(preSieveProduct, maxSize));
	testPoint -= (testPoint % preSieveProduct);
	testPoint -= num::unity();
	int currentIndex = 0;
	while(!isPrime(testPoint))
	{
		testPoint -= dropLength[currentIndex];
		++currentIndex;
		if (currentIndex == dropLength.size()) currentIndex = 0;
	}
	return testPoint;
}

