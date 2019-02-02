#pragma once

#include "User_Environment.h"

template<typename T>
class CryptoEnvironment : UserEnvironment
{
	T cryptographer;//class instance capable of encryption-like operations
public:
	CryptoEnvironment(T inputCryptographer)
	{
		cryptographer = inputCryptographer;
		availableCalls.push_back(UserEnvironment::CallSign(
			"Encrypt a given message.",
			{"encrypt"}, true,
			[this](string message, vector<string> flags)
			{
				cryptographer.encrypt(message, flags);
			}));
		availableCalls.push_back(UserEnvironment::CallSign(
			"Decrypt a given message.",
			{"decrypt"}, true,
			[this](string message, vector<string> flags)
			{
				cryptographer.decrypt(message, flags);
			}));
	}
};

