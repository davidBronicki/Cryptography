#include "User_Environment.hpp"

#include <string>
#include <iostream>

#include "Global_Functions.hpp"

using std::tuple;
using std::string;
using std::vector;
using std::cout;
using std::get;

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
	cout
		<< "Primary callsign: " << callSigns[0] << "\n"
		<< description << "\n"
		<< "Possible callsigns: ";
	string temp;
	for (string sign : callSigns)
	{
		temp += sign;
		temp += ", ";
	}
	cout << temp.substr(0, temp.length() - 2) << "\n";
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
	return std::make_tuple(false, "");
}

UserEnvironment::CallSign UserEnvironment::exitCall(
	"Exit the current user environment.",
	vector<string>{"exit", "done", "back", "up", "quit", "q"},
	[](string argument) -> string {return "";});

UserEnvironment::CallSign UserEnvironment::helpCall(
	"Gives descriptor of current environment.",
	vector<string>{"help", "h", "ls"},
	[](string argument) -> string {return "";});


UserEnvironment::UserEnvironment()
:
	name(""),
	description("")
{}

UserEnvironment::UserEnvironment(string inputName, string inputDescription)
:
	name(inputName),
	description(inputDescription)
{}

void UserEnvironment::printHelp()
{
	cout << "\n"
		<< "Current environment: " << name << "\n"
		<< "Description: " << description << "\n\n"
		<< "Available calls:\n\n";
	helpCall.printDescription();
	cout << "\n";
	exitCall.printDescription();
	for (auto call : availableCalls)
	{
		cout << "\n";
		call.printDescription();
	}
	cout << "\n";
}

string UserEnvironment::handleInput(const string& input)
{
	if (input == "") return "";
	auto clip = clipOne(input);
	if (get<0>(exitCall(clip))) return get<1>(clip) == "" ? "pass" : get<1>(clip);
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
		std::getline(std::cin, input);
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
