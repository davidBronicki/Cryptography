#pragma once

#include "LargeModularNumbers.h"

#include "Encoding.h"

template<size_t primeNumberSize>
class Large_RSA_Encryptor
{
	typedef LargeNumber<primeNumberSize * 2> ul;
	typedef LargeNumber<primeNumberSize> us;

	us prime1, prime2;
	ul modularBase;

	ul exponentBase;
	ul exponent;
	ul inverse;
public:
	Large_RSA_Encryptor(const us& inPrime1, const us& inPrime2, const ul& inExponent)
	:
		prime1(inPrime1), prime2(inPrime2),
		exponent(inExponent)
	{
		modularBase = ul(inPrime1) * ul(inPrime2);
		exponentBase = ul(inPrime1 - us(1u)) * (ul)(inPrime2 - us(1u));
		LargeModularNumber<primeNumberSize * 2> temp(exponent, exponentBase);
		inverse = (ul)(temp.inverse());
	}

	bool setExponent(const us& inExponent)
	{
		try
		{
			LargeModularNumber<primeNumberSize * 2> temp(inExponent, exponentBase);
			inverse = (ul)(temp.inverse());
			exponentBase = inExponent;
			return true;
		}
		catch(...)
		{
			return false;
		}
	}

	ul getModularBase()
	{
		return modularBase;
	}

	ul getExponentBase()
	{
		return exponentBase;
	}

	ul encode(const string& plainText)
	{
		return ul(ASCII_Encoder::encode(plainText, 2 * sizeof(unsigned int) * primeNumberSize));
	}

	ul encrypt(const ul& trueData)
	{
		LargeModularNumber<primeNumberSize * 2> value(trueData, modularBase);
		return ul(value.exponentiate(exponent));
	}
	ul decrypt(const ul& encryptedData)
	{
		LargeModularNumber<primeNumberSize * 2> value(encryptedData, modularBase);
		return ul(value.exponentiate(inverse));
	}

	string decode(const ul& code)
	{
		return ASCII_Encoder::decode(code.getData());
	}
};
