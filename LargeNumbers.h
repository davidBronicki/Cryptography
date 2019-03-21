#include <vector>
#include <exception>
#include <stdexcept>
#include <type_traits>
#include <algorithm>
#include <iterator>

#include <iostream>

using namespace std;

typedef unsigned long long ull;



template<size_t bit32Length,//number of 32 bit ints composing the number
	class = enable_if<bit32Length != 0>>//0 size numbers not allowed
class LargeNumber
{
	ull data[bit32Length];//64 bit numbers are used to make multiplication easier
public:
	LargeNumber()
	{
		for (int i = 0; i < bit32Length; ++i)
		{
			data[i] = 0;
		}
	}

	LargeNumber(vector<unsigned int> inputData)
	{
		if (inputData.size() != bit32Length) throw invalid_argument(
			"passed wrongly sized initial data for LargeNumber class");
		for (int i = 0; i < bit32Length; ++i)
		{
			data[i] = inputData[i];
		}
	}

	vector<unsigned int> getData()
	{
		vector<unsigned int> output(bit32Length);
		for (int i = 0; i < bit32Length; ++i)
		{
			output[i] = data[i];
		}
		return output;
	}

	LargeNumber<bit32Length>& operator+=(const LargeNumber<bit32Length>& other)
	{
		bool overflowBit = false;
		for (int i = 0; i < bit32Length; ++i)
		{
			data[i] += other.data[i];
			if (overflowBit) ++data[i];
			overflowBit = data[i] >> 32;
			data[i] &= 0xffffffff;
		}
		return *this;
	}

	LargeNumber<bit32Length>& operator-=(const LargeNumber<bit32Length>& other)
	{
		//subtracting a larger number from a smaller is undefined behavior
		bool underflowBit = false;
		for (int i = 0; i < bit32Length; ++i)
		{
			data[i] -= other.data[i];
			if (underflowBit) --data[i];
			underflowBit = data[i] >> 32;
			data[i] &= 0xffffffff;
		}
		return *this;
	}

	LargeNumber<bit32Length>& operator*=(const LargeNumber<bit32Length>& other)
	{
		ull currentData[bit32Length];
		copy(begin(data), end(data), begin(currentData));
		ull rollover = 0;
		for (int i = 0; i < bit32Length; ++i)//the place we are calculating for
		{
			data[i] = rollover;
			rollover = 0;
			for (int j = 0; j <= i; ++j)//index of our data
			{
				int k = i - j;//index of other data
				ull temp = currentData[j] * other.data[k];
				rollover += temp >> 32;
				data[i] += temp & 0xffffffff;
			}
			rollover += data[i] >> 32;
			data[i] &= 0xffffffff;
		}
		return *this;
	}

	template<size_t newBit32Length>
	operator LargeNumber<newBit32Length>()
	{
		if (newBit32Length <= bit32Length)
		{
			return LargeNumber<newBit32Length>(
				vector<unsigned int>(begin(data), end(data)));
					// &data,
					// (&data) + bit32Length));
		}
		else
		{
			vector<unsigned int> initialData(newBit32Length, 0);
			for (int i = 0; i < bit32Length; ++i)
			{
				initialData[i] = data[i];
			}
			return LargeNumber<newBit32Length>(initialData);
		}
	}

	operator ull()
	{
		ull output = data[0];
		if (bit32Length != 1) output |= data[1] << 32;
		return output;
	}
};


void unitTest_LargeNumbers()
{
	{
		LargeNumber<2> a({(unsigned int)1 << 31, 0});
		LargeNumber<2> b({(unsigned int)1 << 31, 0});
		a += b;
		if ((ull)a == (ull)1 << 32)
		{
			cout << "addition rollover working" << endl;
		}
		else
		{
			cout << "*****addition rollover not working*****" << endl;
		}
	}
	{
		LargeNumber<2> a({0, 1});
		LargeNumber<2> b({1, 0});
		a -= b;
		ull check = ((ull)1 << 32) - 1;
		if ((ull)a == check)
		{
			cout << "subtraction carryover working" << endl;
		}
		else
		{
			cout << "*****subtraction carryover not working*****" << endl;
		}
	}
	{
		LargeNumber<4> a({(unsigned int)1 << 31, (unsigned int)1 << 31, 0, 0});
		LargeNumber<4> b({(unsigned int)1 << 31, (unsigned int)1 << 31, 0, 0});
		a *= b;
		vector<unsigned int> data(a.getData());
		bool working = true;
		working &= data[0] == 0;
		working &= data[1] == (unsigned int)1 << (31 + 31 - 32);
		working &= data[2] == (unsigned int)1 << (31 + 31 + 1 + 32 - 64);
		working &= data[3] == (unsigned int)1 << (31 + 31 + 64 - 96);
		if (working)
		{
			cout << "multiplication rollover working" << endl;
		}
		else
		{
			cout << "*****multiplication rollover not working*****" << endl;
		}
	}
}


int main()
{
	unitTest_LargeNumbers();
	return 0;
}


