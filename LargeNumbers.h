#pragma once

#include <vector>
#include <exception>
#include <stdexcept>
#include <type_traits>
#include <algorithm>
#include <iterator>
#include "math.h"

#include <iostream>
#include <string>

using namespace std;

template<size_t loopLength, size_t i, typename functionFootprint>
class UnravelledForLoop
{
public:
	inline static void result(const functionFootprint& loopCodeBlock)
	{
		loopCodeBlock(i);
		UnravelledForLoop<loopLength, i + 1, functionFootprint>::result(loopCodeBlock);
	}
};

template<size_t loopLength, typename functionFootprint>
class UnravelledForLoop<loopLength, loopLength, functionFootprint>
{
public:
	inline static void result(const functionFootprint& loopCodeBlock)
	{
		loopCodeBlock(loopLength);
	}
};

template<size_t loopLength, typename functionFootprint>
inline void unravelledForLoop(const functionFootprint& loopCodeBlock)
{
	UnravelledForLoop<loopLength - 1, 0, functionFootprint>::result(loopCodeBlock);
}


template<size_t i, typename functionFootprint>
class ReverseUnravelledForLoop
{
public:
	inline static void result(const functionFootprint& loopCodeBlock)
	{
		loopCodeBlock(i);
		ReverseUnravelledForLoop<i - 1, functionFootprint>::result(loopCodeBlock);
	}
};

template<typename functionFootprint>
class ReverseUnravelledForLoop<0, functionFootprint>
{
public:
	inline static void result(const functionFootprint& loopCodeBlock)
	{
		loopCodeBlock(0);
	}
};

template<typename functionFootprint>
class ReverseUnravelledForLoop<-1u, functionFootprint>
{
public:
	inline static void result(const functionFootprint& loopCodeBlock)
	{
	}
};

template<size_t loopLength, typename functionFootprint>
inline void reverseUnravelledForLoop(const functionFootprint& loopCodeBlock)
{
	ReverseUnravelledForLoop<loopLength - 1, functionFootprint>::result(loopCodeBlock);
}


template<size_t bit32Length,//number of 32 bit ints composing the number
	class sizeCheck = enable_if<bit32Length != 0>>//0 size numbers not allowed
class LargeNumber
{
	typedef unsigned long long ull;
	static const ull mask_32bit = 0xffffffff;
	ull data[bit32Length];//64 bit numbers are used to make multiplication easier

public:
	LargeNumber()
	{
		unravelledForLoop<bit32Length>([this](size_t i)
		{
			data[i] = 0;
		});
	}

	LargeNumber(unsigned int inputNumber)
	{

		unravelledForLoop<bit32Length>([this](size_t i)
		{
			data[i] = 0;
		});
		data[0] = inputNumber;
	}

	LargeNumber(const vector<unsigned int>& inputData)
	{
		if (inputData.size() != bit32Length) throw invalid_argument(
			"passed wrongly sized initial data for LargeNumber class");
		unravelledForLoop<bit32Length>([this, &inputData](size_t i)
		{
			data[bit32Length - i - 1] = inputData[i];
		});
	}

	template<size_t otherBit32Length>
	LargeNumber(const LargeNumber<otherBit32Length>& inputValue)
	{
		if (bit32Length <= otherBit32Length)
		{
			unravelledForLoop<bit32Length>([this, &inputValue](size_t i)
			{
				data[i] = inputValue[i];
			});
		}
		else
		{
			unravelledForLoop<bit32Length>([this, &inputValue](size_t i)
			{
				if (i < otherBit32Length)
				{
					data[i] = inputValue[i];
				}
				else
				{
					data[i] = 0;
				}
			});
		}
	}

	static const LargeNumber<bit32Length>& unity()
	{
		static const LargeNumber<bit32Length> unityValue(1u);
		return unityValue;
	}

	static const LargeNumber<bit32Length>& zero()
	{
		static const LargeNumber<bit32Length> zeroValue;
		return zeroValue;
	}

	static const LargeNumber<bit32Length>& maxInt()
	{
		static const LargeNumber<bit32Length> maxValue(zero() - unity());
		return maxValue;
	}

	vector<unsigned int> getData() const
	{
		vector<unsigned int> output(bit32Length);
		for (int i = 0; i < bit32Length; ++i)
		{
			output[bit32Length - i - 1] = data[i];
		}
		return output;
	}

	unsigned int operator[](size_t i) const
	{
		return data[i];
	}

	bool operator<(const LargeNumber<bit32Length>& other) const
	{
		bool returnValue = false;
		unravelledForLoop<bit32Length>([this, &other, &returnValue](size_t i)
		{
			if (data[i] < other.data[i])
			{
				returnValue = true;
				return;
			}
			if (data[i] > other.data[i])
			{
				returnValue = false;//not necessary since already set to false
				return;
			}
		});

		return returnValue;
	}
	
	bool operator<=(const LargeNumber<bit32Length>& other) const
	{
		bool returnValue = true;
		unravelledForLoop<bit32Length>([this, &other, &returnValue](size_t i)
		{
			if (data[i] < other.data[i]) 
			{
				returnValue = true;//not necessary since already set to true
				return;
			}
			if (data[i] > other.data[i])
			{
				returnValue = false;
				return;
			}
		});
		return returnValue;
	}

	bool operator>(const LargeNumber<bit32Length>& other) const
	{
		return !operator<=(other);
	}

	bool operator>=(const LargeNumber<bit32Length>& other) const
	{
		return !operator<(other);
	}

	bool operator==(const LargeNumber<bit32Length>& other) const
	{
		bool returnValue = true;
		unravelledForLoop<bit32Length>([this, &other, &returnValue](size_t i)
		{
			if (data[i] != other.data[i])
			{
				returnValue = false;
				return;
			}
		});
		return returnValue;
	}

	template<typename T, typename = typename enable_if<is_integral<T>::value && is_unsigned<T>::value>::type>
	LargeNumber<bit32Length>& operator<<=(const T& shiftValue)
	{
		unsigned int wordShift = shiftValue >> 5;//number of words we need to shift by
		unsigned int smallShift = shiftValue & 31;//number of bits we need to shift by

		if (wordShift >= bit32Length)//check if shift is larger than data size
		{
			unravelledForLoop<bit32Length>([this](size_t i)
			{
				data[i] = 0;
			});
		}

		if (wordShift > 0)
		{
			unsigned int wordAssignmentIndex = bit32Length - 1;

			while (wordAssignmentIndex != wordShift - 1)//copy data over
			{
				data[wordAssignmentIndex] = data[wordAssignmentIndex - wordShift];
				--wordAssignmentIndex;
			}
			while (wordAssignmentIndex < bit32Length)//zero out the rest
				//unsigned int, so -1 < bit32Length returns false.
			{
				data[wordAssignmentIndex] = 0;
				--wordAssignmentIndex;
			}
		}

		ull carryover = 0;
		unravelledForLoop<bit32Length>([this, smallShift, &carryover](size_t i)//do smaller shifts
		{
			data[i] <<= smallShift;
			data[i] |= carryover;
			carryover = data[i] >> 32;
			data[i] &= mask_32bit;
		});
		return *this;
	}

	template<typename T, typename = typename enable_if<is_integral<T>::value && is_unsigned<T>::value>::type>
	LargeNumber<bit32Length>& operator>>=(const T& shiftValue)
	{
		unsigned int wordShift = shiftValue >> 5;//number of words we need to shift by
		unsigned int smallShift = shiftValue & 31;//number of bits we need to shift by

		if (wordShift >= bit32Length)//check if shift is larger than data size
		{
			unravelledForLoop<bit32Length>([this](size_t i)
			{
				data[i] = 0;
			});
		}

		if (wordShift > 0)
		{
			unsigned int wordAssignmentIndex = 0;

			while (wordAssignmentIndex < bit32Length - wordShift)//copy data over
			{
				data[wordAssignmentIndex] = data[wordAssignmentIndex + wordShift];
				++wordAssignmentIndex;
			}
			while (wordAssignmentIndex < bit32Length)//zero out the rest
			{
				data[wordAssignmentIndex] = 0;
				++wordAssignmentIndex;
			}
		}

		ull carryover = 0;
		reverseUnravelledForLoop<bit32Length>([this, smallShift, &carryover](size_t i)//do smaller shifts
		{
			data[i] <<= 32 - smallShift;
			data[i] |= carryover;
			carryover = data[i] << 32;
			data[i] >>= 32;
		});
		return *this;
	}

	LargeNumber<bit32Length>& operator|=(const LargeNumber<bit32Length>& other)
	{
		unravelledForLoop<bit32Length>([this, &other](size_t i)
		{
			data[i] |= other.data[i];
		});
		return *this;
	}

	LargeNumber<bit32Length>& operator&=(const LargeNumber<bit32Length>& other)
	{
		unravelledForLoop<bit32Length>([this, &other](size_t i)
		{
			data[i] &= other.data[i];
		});
		return *this;
	}

	LargeNumber<bit32Length>& operator^=(const LargeNumber<bit32Length>& other)
	{
		unravelledForLoop<bit32Length>([this, &other](size_t i)
		{
			data[i] ^= other.data[i];
		});
		return *this;
	}

	LargeNumber<bit32Length>& operator+=(const LargeNumber<bit32Length>& other)
	{
		bool overflowBit = false;
		unravelledForLoop<bit32Length>([this, &other, &overflowBit](size_t i)
		{
			data[i] += other.data[i];
			if (overflowBit) ++data[i];
			overflowBit = data[i] >> 32;
			data[i] &= mask_32bit;
		});
		return *this;
	}

	LargeNumber<bit32Length>& operator-=(const LargeNumber<bit32Length>& other)
	{
		//subtracting a larger number from a smaller behaves in usual 2s compliment manner
		bool underflowBit = false;
		unravelledForLoop<bit32Length>([this, &other, &underflowBit](size_t i)
		{
			data[i] -= other.data[i];
			if (underflowBit) --data[i];
			underflowBit = data[i] >> 32;
			data[i] &= mask_32bit;
		});
		return *this;
	}

	LargeNumber<bit32Length>& operator*=(const LargeNumber<bit32Length>& other)
	{//other must be distinct from *this
		if (this == &other)//need to copy data if sending reference to self
		{
			LargeNumber<bit32Length> temp(other);
			return operator*=(temp);
		}
		ull currentData[bit32Length];
		unravelledForLoop<bit32Length>([this, &currentData](size_t i)
		{
			currentData[i] = data[i];
		});//copy function uses loop, use this to avoid if statements

		ull rollover = 0;
		unravelledForLoop<bit32Length>([this, &other, &currentData, &rollover](size_t i)
		{
			data[i] = rollover;
			rollover = 0;
			for (int j = 0; j <= i; ++j)//index of our data
			{
				int k = i - j;//index of other data
				ull temp = currentData[j] * other.data[k];
				rollover += temp >> 32;
				data[i] += temp & mask_32bit;
			}
			rollover += data[i] >> 32;
			data[i] &= mask_32bit;
		});
		return *this;
	}

	LargeNumber<bit32Length>& operator/=(const LargeNumber<bit32Length>& other);

	LargeNumber<bit32Length>& operator%=(const LargeNumber<bit32Length>& other)
	{
		LargeNumber<bit32Length> temp(*this);
		return operator-=((temp/=other)*=other);
	}

	operator ull() const
	{
		ull output = data[0];
		if (bit32Length != 1) output |= (data[1] << 32);
		return output;
	}
};

template<size_t bit32Length>
ostream& operator<<(ostream& os, const LargeNumber<bit32Length>& other)
{
	auto data = other.getData();
	unravelledForLoop<bit32Length - 1>([&os, &data](size_t i)
	{
		os << hex << data[i];
		os << ' ';
	});
	os << hex << data[bit32Length - 1] << dec;
	return os;
}

template<size_t bit32Length, typename T,
	typename = typename enable_if<is_integral<T>::value && is_unsigned<T>::value>::type>
LargeNumber<bit32Length> operator<<(LargeNumber<bit32Length> lhs, const T& rhs)
{
	return lhs <<= rhs;
}

template<size_t bit32Length, typename T,
	typename = typename enable_if<is_integral<T>::value && is_unsigned<T>::value>::type>
LargeNumber<bit32Length> operator>>(LargeNumber<bit32Length> lhs, const T& rhs)
{
	return lhs >>= rhs;
}

template<size_t bit32Length>
LargeNumber<bit32Length> operator&(LargeNumber<bit32Length> lhs, const LargeNumber<bit32Length>& rhs)
{
	return lhs &= rhs;
}

template<size_t bit32Length>
LargeNumber<bit32Length> operator|(LargeNumber<bit32Length> lhs, const LargeNumber<bit32Length>& rhs)
{
	return lhs |= rhs;
}

template<size_t bit32Length>
LargeNumber<bit32Length> operator^(LargeNumber<bit32Length> lhs, const LargeNumber<bit32Length>& rhs)
{
	return lhs ^= rhs;
}

template<size_t bit32Length>
LargeNumber<bit32Length> operator+(LargeNumber<bit32Length> lhs, const LargeNumber<bit32Length>& rhs)
{
	return lhs += rhs;
}

template<size_t bit32Length>
LargeNumber<bit32Length> operator-(LargeNumber<bit32Length> lhs, const LargeNumber<bit32Length>& rhs)
{
	return lhs -= rhs;
}

template<size_t bit32Length>
LargeNumber<bit32Length> operator*(LargeNumber<bit32Length> lhs, const LargeNumber<bit32Length>& rhs)
{
	return lhs *= rhs;
}

template<size_t bit32Length, class sizeCheck>
LargeNumber<bit32Length>& LargeNumber<bit32Length, sizeCheck>::operator/=(const LargeNumber<bit32Length>& other)
{
	//This algorithm is a bit worse for wear. I managed to get it working and have
	//decided to never look at it again.

	//It uses a slow division algorithm. It works by approximating the divisor by
	//its most siginificant word, and calculating the remainder to
	//use to better the approximation. This will generally take bit32Length^3 time.
	//bit32Length^2 for the multiplcation algorithm and bit32Length^1 for
	//the technique used here.

	if (*this < other)
	{
		//integer division will return 0
		unravelledForLoop<bit32Length>([this](size_t i)
		{
			data[i] = 0;
		});
		return *this;
	}

	//locate most significant word in denominator (denominator is other)
	unsigned int mostSignificantWordPosition = 0;
	unravelledForLoop<bit32Length>([&other, &mostSignificantWordPosition](size_t i)
	{
		if (other.data[i] != 0)
		{
			mostSignificantWordPosition = i;
		}
	});

	if (mostSignificantWordPosition == 0)
	{
		//implement small denominator algorithm
		ull divisor = other.data[0];
		ull smallRemainder = 0;
		reverseUnravelledForLoop<bit32Length>([this, &divisor, &smallRemainder](size_t i)
		{
			ull temp = data[i] + (smallRemainder << 32);
			data[i] = temp / divisor;
			smallRemainder = temp - data[i] * divisor;
		});
		return *this;
	}
	// else if (mostSignificantWordPosition == bit32Length - 1)
	// {
	// 	*this = LargeNumber<bit32Length>(data[mostSignificantWordPosition]
	// 		/ other.data[mostSignificantWordPositinon]);
	// 	return *this;
	// }

	//set up bit shift quantity to discard ignored bits
	unsigned int bitshiftQuantity;
	if (other.data[mostSignificantWordPosition] < (1ul << 16))
	{
		bitshiftQuantity = 32u * mostSignificantWordPosition - 16u;
	}
	else
	{
		bitshiftQuantity = 32u * mostSignificantWordPosition;
	}

	ull mostSignificantWord = (ull)(other >> bitshiftQuantity);

	LargeNumber<bit32Length> oldData(*this);
	operator>>=(bitshiftQuantity);

	{
		ull smallRemainder = 0;
		reverseUnravelledForLoop<bit32Length>([this, &mostSignificantWord, &smallRemainder](size_t i)
		{
			ull temp = data[i] + (smallRemainder << 32);
			data[i] = temp / mostSignificantWord;
			smallRemainder = temp - data[i] * mostSignificantWord;
		});
		//(*this) is now the quotient approximation, original data held in oldData.
	}

	LargeNumber<bit32Length> cutoff(other);
	// LargeNumber<bit32Length> reverseCutoff(LargeNumber<bit32Length>::zero() - cutoff);//artificial negative number
	// cutoff <<= 1u;//algorithm only guarantees within 2*divisor
	bool negative = oldData < *this * other;

	LargeNumber<bit32Length> remainder(
		negative ?
		*this * other - oldData :
		oldData - *this * other);//r_0 = a - q_0 * b

	while (remainder >= cutoff)// && remainder < reverseCutoff)
	{
		// cout << remainder << endl;
		//use most significant word to perform division and obtain new quotient approximation.
		//then find new remainder and use resulting remainder to find more precise approximation.
		remainder >>= bitshiftQuantity;
		ull smallRemainder = 0;
		reverseUnravelledForLoop<bit32Length>([&remainder, &mostSignificantWord, &smallRemainder](size_t i)
		{
			ull temp = remainder.data[i] + (smallRemainder << 32);
			remainder.data[i] = temp / mostSignificantWord;
			smallRemainder = temp - remainder.data[i] * mostSignificantWord;
		});
		negative ? operator-=(remainder) : operator+=(remainder);

		LargeNumber<bit32Length> newGuess(*this * other);
		negative = oldData < newGuess;
		remainder = negative ?
			newGuess - oldData :
			oldData - newGuess;

		// remainder = oldData - *this * other;
	}

	if (negative && remainder != LargeNumber<bit32Length>::zero())
	{
		operator-=(LargeNumber<bit32Length>::unity());
	}

	// if (remainder >= other)//check if in proper range
	// {
	// 	operator+=(LargeNumber<bit32Length>::unity());
	// }

	// if (remainder >= reverseCutoff)//check if in proper range
	// {
	// 	operator-=(LargeNumber<bit32Length>::unity());
	// }

	return *this;
}

template<size_t bit32Length>
LargeNumber<bit32Length> operator/(LargeNumber<bit32Length> lhs, const LargeNumber<bit32Length>& rhs)
{
	return lhs /= rhs;
}

