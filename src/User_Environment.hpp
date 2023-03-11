#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <functional>

typedef std::function<std::string(std::string)> callableObject;

class UserEnvironment
{
	class CallSign
	{
		std::string description;
		std::vector<std::string> callSigns;
		callableObject callOperation;
	public:
		CallSign(std::string inputDescription,
			std::vector<std::string> inputCallSigns,
			callableObject inputCallOperation);
		std::tuple<bool, std::string> operator()(const std::tuple<std::string, std::string>& inputString);
		void printDescription();
	};
	static CallSign exitSign, helpCall;
	std::vector<CallSign> availableCalls;
	std::string name;
	std::string description;
	std::string handleInput(const std::string& input);//return true if exit called
	void printHelp();
public:
	UserEnvironment();
	UserEnvironment(std::string inputName, std::string inputDescription);
	std::string enterEnvironment();
	std::string enterEnvironment(const std::string& input);
	void addCallSign(std::string description, std::vector<std::string> callSigns,
		callableObject callOperation);
};
