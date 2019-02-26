#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

typedef function<string(string)> callableObject;

class UserEnvironment
{
	class CallSign
	{
		string description;
		vector<string> callSigns;
		callableObject callOperation;
	public:
		CallSign(string inputDescription,
			vector<string> inputCallSigns,
			callableObject inputCallOperation);
		tuple<bool, string> operator()(const tuple<string, string>& inputString);
		void printDescription();
	};
	static CallSign exitSign, helpCall;
	vector<CallSign> availableCalls;
	string name;
	string description;
	string handleInput(const string& input);//return true if exit called
	void printHelp();
public:
	UserEnvironment(string inputName, string inputDescription);
	string enterEnvironment();
	string enterEnvironment(const string& input);
	void addCallSign(string description, vector<string> callSigns,
		callableObject callOperation);
};