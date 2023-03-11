#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <functional>
// #include <memory>
// #include <span>


// enum class ParseTypes
// {
// 	std::string,
// 	std::string_Keyword,
// 	std::string_VarName,
// 	std::string_Value,
// 	Integer,
// 	BigInt
// };

// namespace ParseTypeFlags
// {
// enum Flags
// {
// 	Keyword = 1,
// 	Integer = 2,
// 	BigInt = 4,
// 	Bounded = 8,
// 	Prime = 16
// };
// }

// struct ParseSlotType
// {
// 	ParseTypeFlags::Flags typeFlags;
// };

// class CLIArgumentSlot
// {
// 	std::std::string argumentName;

// };

// class CLIState
// {
// 	protected:

// 	std::std::string & getVar(std::std::string_view handle);
// 	std::std::string const & getVar(std::std::string_view handle) const;

// 	void removeVar(std::std::string_view handle);

// 	public:

// 	enum ParseTypeFlags : std::size_t
// 	{
// 		Keyword = 1,
// 		Var = 2,
// 		Integer = 4,
// 		BigInt = 8,
// 		Bounded = 16,
// 		Prime = 32
// 	};

// 	virtual std::unique_ptr<CLIState> parseLine(std::span<std::std::string_view> words) = 0;
// 	std::unique_ptr<CLIState> parseLine(std::std::string_view line);

// 	virtual ~CLIState() = 0;
// };

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
	static CallSign exitCall, helpCall, cdCall;
	std::vector<CallSign> availableCalls;
	std::string name;
	std::string description;
	std::string handleInput(const std::string& input);
	void printHelp();
public:
	UserEnvironment();
	UserEnvironment(std::string inputName, std::string inputDescription);
	std::string enterEnvironment();
	std::string enterEnvironment(const std::string& input);
	void addCallSign(std::string description, std::vector<std::string> callSigns,
		callableObject callOperation);
};
