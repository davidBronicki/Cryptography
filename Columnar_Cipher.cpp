
//Columnar_Cipher.cpp

#include "Columnar_Cipher.h"

#include <algorithm>
#include <iostream>

using namespace std;

struct columnSortingHelper
{
	ModularNumber sortingKey;
	int originalPosition;
	string column;
};

ColumnarCipher::ColumnarCipher()
:
	alphabet("")
{}

ColumnarCipher::ColumnarCipher(string inAlphabet, string inKey)
:
	alphabet(inAlphabet),
	key(alphabet.stringToNumeric(inKey))
{}

string ColumnarCipher::encrypt(string plainText)
{
	vector<columnSortingHelper> columns;
	for (int i = 0; i < key.size(); ++i)
	{
		columns.push_back({key[i], i, ""});
	}
	for (int i = 0; i < plainText.length(); ++i)
	{
		int column = i % key.size();
		columns[column].column += plainText[i];
		//add the next character (plainText[i])
		//to the struct string element (.column)
		//of the ([column])th element of (columns).
	}
	sort(columns.begin(), columns.end(),
		[](columnSortingHelper a, columnSortingHelper b)
		{
			return a.sortingKey < b.sortingKey;
		});
	string output;
	for (auto column : columns)
	{
		output += column.column;
		//reading down the columns
	}
	return output;
}

string ColumnarCipher::decrypt(string cypherText)
{
	vector<columnSortingHelper> columns;
	for (int i = 0; i < key.size(); ++i)
	{
		columns.push_back({key[i], i, ""});
	}
	sort(columns.begin(), columns.end(),
		[](columnSortingHelper a, columnSortingHelper b)
		{
			return a.sortingKey < b.sortingKey;
		});//pre sort and use the "original position"
		//to undo the sorting later.

	//we need to figure out how many chars to put into
	//each colum so we do division algorithm.
	int charsPerColumn = cypherText.length() / key.size();
	int extraChars = cypherText.length() % key.size();
	char* it = &*cypherText.begin();
	for (int i = 0; i < key.size(); ++i)
	{
		if (columns[i].originalPosition < extraChars)
		{
			//this is one of the last columns in the unsorted
			//version, so we add standard amount
			columns[i].column = string(it, charsPerColumn + 1);
			it += charsPerColumn + 1;
		}
		else
		{
			//one of the first in unsorted version,
			//so we add an extra one to it
			columns[i].column = string(it, charsPerColumn);
			it += charsPerColumn;
		}
	}
	sort(columns.begin(), columns.end(),
		[](columnSortingHelper a, columnSortingHelper b)
		{
			return a.originalPosition < b.originalPosition;
		});//undo sorting by using originalPosition for sorting key

	string output;
	for (int i = 0; i < cypherText.length(); ++i)
	{
		//we need to read across rows rather than columns,
		//so given a character position in plaintext,
		//we need to caclulate the position in our
		//columns. This is done with division algorithm
		//where quotient is the row (position in the column string)
		//and remainder is column
		int column = i % key.size();
		int position = i / key.size();
		output += columns[column].column[position];
		//the ([column])th member of (columns), grab the
		//string member (.column) of the struct, and
		//grab the ([position])th char in the string.
	}

	return output;
}

void ColumnarCipher::setKey(string inputKey)
{
	key = alphabet.forceStringToNumeric(inputKey);
}

string ColumnarCipher::getKey()
{
	return alphabet.numericToString(key);
}
