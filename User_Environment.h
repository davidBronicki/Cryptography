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
		// class Flag
		// {
		// 	string description;
		// 	vector<string> flagNames;
		// public:
		// 	Flag(string inputDescription,
		// 		vector<string> inputNames);
		// 	string getFlagValue(const vector<string>& args);
		// 	bool matches(const string& flag);
		// 	void printDescription();
		// };
		string description;
		vector<string> callSigns;
		callableObject callOperation;
		// vector<Flag> flags;
		// vector<vector<string>> parseFlags(vector<string> flagArgs);
	public:
		CallSign(string inputDescription,
			vector<string> inputCallSigns,
			callableObject inputCallOperation);
		tuple<bool, string> operator()(const tuple<string, string>& inputString);
		void printDescription();
		// void addFlag(vector<string> arguments);
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
		// vector<vector<string>> flagArguments,
		// bool ignoreCases = true);
};