#include "User_Environment.h"

#include <string>
#include <iostream>

#include "Global_Functions.h"

using namespace std;

UserEnvironment::CallSign::CallSign(string inputDescription,
	vector<string> inputCallSigns,
	callableObject inputCallOperation)
: 
	description(inputDescription),
	callOperation(inputCallOperation)
{
	for (auto item : inputCallSigns)
	{
		callSigns.push_back(removeCase(item));
	}
}

void UserEnvironment::CallSign::printDescription()
{
	cout << "Primary callsign: " << callSigns[0] << endl;
	cout << description << endl;
	cout << "Possible callsigns: ";
	string temp;
	for (string sign : callSigns)
	{
		temp += sign;
		temp += ", ";
	}
	cout << temp.substr(0, temp.length() - 2) << endl;
}

tuple<bool, string> UserEnvironment::CallSign::operator()(const tuple<string, string>& inputStrings)
{
	string flag = removeCase(get<0>(inputStrings));
	for (string sign : callSigns)
	{
		if(sign == flag)
		{
			return make_tuple(true, callOperation(get<1>(inputStrings)));
		}
	}
	return make_tuple(false, "");
}

UserEnvironment::CallSign UserEnvironment::exitSign(
	"Exit the current user environment.",
	vector<string>{"exit", "done", "back"},
	[](string argument) -> string {return "";});

UserEnvironment::CallSign UserEnvironment::helpCall(
	"Gives descriptor of current environment.",
	vector<string>{"help", "h"},
	[](string argument) -> string {return "";});


UserEnvironment::UserEnvironment(string inputName, string inputDescription)
:
	name(inputName),
	description(inputDescription)
{}

void UserEnvironment::printHelp()
{
	cout << endl;
	cout << "Current environment: " << name << endl;
	cout << "Description: " << description << endl;
	cout << endl << "Available calls: " << endl << endl;
	helpCall.printDescription();
	cout << endl;
	exitSign.printDescription();
	for (auto call : availableCalls)
	{
		cout << endl;
		call.printDescription();
	}
	cout << endl;
}

string UserEnvironment::handleInput(const string& input)
{//return true if exit called
	if (input == "") return "";
	auto clip = clipOne(input);
	if (get<0>(exitSign(clip))) return get<1>(clip) == "" ? "pass" : get<1>(clip);
	if (get<0>(helpCall(clip)))
	{
		printHelp();
		return handleInput(get<1>(clip));
	}
	for (auto call : availableCalls)
	{
		auto value = call(clip);
		if (get<0>(value)) return handleInput(get<1>(value));
	}
	return handleInput(get<1>(clip));
}

string UserEnvironment::enterEnvironment()
{
	while (true)
	{
		string input;
		getline(cin, input);
		string output = handleInput(input);
		if (output != "") return output;
	}
}

string UserEnvironment::enterEnvironment(const string& input)
{
	string output = handleInput(input);
	if (output != "") return output;
	else return enterEnvironment();
}

void UserEnvironment::addCallSign(string description,
	vector<string> callSigns,
	callableObject callOperation)
{
	availableCalls.push_back(UserEnvironment::CallSign(
		description, callSigns, callOperation));
}
