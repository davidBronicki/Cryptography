#include "Global_Functions.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<string> parse(const string& input, char delimiter)
{
	vector<string> output;
	auto breakPointIterator = input.begin();
	for (auto it = input.begin(); it != input.end(); ++it)
	{
		if (*it == delimiter)
		{
			output.push_back(string(breakPointIterator, it));
			breakPointIterator = ++it;
		}
	}
	output.push_back(string(breakPointIterator, input.end()));
	return output;
}

tuple<string, string> clipOne(const string& input, char delimiter)
{
	int loc = 0;
	for (; loc < input.length(); ++loc)
	{
		if (input[loc] == delimiter) break;
	}
	if (loc == input.length()) return make_tuple(input, "");
	else
	{
		return make_tuple(input.substr(0, loc),
			input.substr(loc + 1, input.length() - loc - 1));
	}
}

string fullConcat(const vector<string>& input, string pad)
{
	string output;
	for (string item : input)
	{
		output += item;
		output += pad;
	}
	return output.substr(0, output.length() - pad.length());
}

string removeCase(const string& input)
{
	string output;
	for (char letter : input)
	{
		if (letter > 64 && letter < 91)
		{
			output += letter + 32;
		}
		else
		{
			output += letter;
		}
	}
	return output;
}

