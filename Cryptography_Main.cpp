
//Cryptography_Main.cpp

#include <string>
#include <vector>
#include <iostream>
#include <functional>

#include "User_Environment.h"
#include "Affine_Shift_Cipher.h"
#include "Columnar_Cipher.h"
#include "RSA_Encryption.h"
#include "Character_Set.h"
#include "Global_Functions.h"

#include "LargeNumbers.h"

#define SET_ENCRYPTION_CALLSIGN(ENVIRONMENT, CRYPTOGRAPHER)\
ENVIRONMENT.addCallSign("Encrypt a given message.", {"encrypt"},\
	[&CRYPTOGRAPHER](string arg) -> string\
	{\
		cout << "Cipher Text: " << CRYPTOGRAPHER.encrypt(arg) << endl;\
		return "";\
	})
#define SET_DECRYPTION_CALLSIGN(ENVIRONMENT, CRYPTOGRAPHER)\
ENVIRONMENT.addCallSign("Encrypt a given message.", {"decrypt"},\
	[&CRYPTOGRAPHER](string arg) -> string\
	{\
		cout << "Plain Text: " << CRYPTOGRAPHER.decrypt(arg) << endl;\
		return "";\
	})

using namespace std;

UserEnvironment buildAffineCipherEnvironment(AffineShiftCipher& affineCipher);
UserEnvironment buildColumnarCipherEnvironment(ColumnarCipher& columnarCipher);
UserEnvironment buildRSA_EncryptionEnvironment(RSA_Encryptor& rsaEncryptor);

UserEnvironment buildGroundEnvironment(
	AffineShiftCipher& affineCipher, UserEnvironment& affineEnvironment,
	ColumnarCipher& columnarCipher, UserEnvironment& columnarEnvironment,
	RSA_Encryptor& rsaEncryptor, UserEnvironment& rsaEnvironment);

int main(){
	LargeNumber<4> test1({0, 1<<30, 0, 1});
	LargeNumber<4> test2({1, 1<<30, 1, 1});
	test1 += test2;
	test1 += test2;
	test1 += test2;
	for (auto item : test1.getData())
	{
		cout << item << endl;
	}

	AffineShiftCipher affineCipher(Character::standardLowerCase, 1, 0);
	UserEnvironment affineEnvironment(buildAffineCipherEnvironment(affineCipher));


	ColumnarCipher columnarCipher(Character::standardLowerCase, "abcde");
	UserEnvironment columnarEnvironment(buildColumnarCipherEnvironment(columnarCipher));


	RSA_Encryptor rsaEncryptor(53359, 13187, 238473277);
	UserEnvironment rsaEnvironment(buildRSA_EncryptionEnvironment(rsaEncryptor));


	UserEnvironment groundEnvironment(buildGroundEnvironment(
		affineCipher, affineEnvironment,
		columnarCipher, columnarEnvironment,
		rsaEncryptor, rsaEnvironment));
	groundEnvironment.enterEnvironment();
	return 0;
}

string enterAffineCipherEnvironment(AffineShiftCipher& cryptographer, UserEnvironment& affineEnvironment, string arg)
{
	cout << "Entering Affine Cipher Environment." << endl;
	cout << "Multiplying parameter: " << cryptographer.getMult() << endl;
	cout << "Shift parameter: " << cryptographer.getShift() << endl;
	auto output = affineEnvironment.enterEnvironment(arg);
	cout << "Exiting Affine Cipher Environment." << endl;
	return output;
}

string enterColumnarCipherEnvironment(ColumnarCipher& cryptographer, UserEnvironment& columnarEnvironment, string arg)
{
	cout << "Entering Columnar Cipher Environment." << endl;
	cout << "Key: " << cryptographer.getKey() << endl;
	auto output = columnarEnvironment.enterEnvironment(arg);
	cout << "Exiting Columnar Cipher Environment." << endl;
	return output;
}

string enterRSA_Environment(RSA_Encryptor& cryptographer, UserEnvironment& rsaEnvironment, string arg)
{
	cout << "Entering RSA Encryption Environment." << endl;
	auto privateData = cryptographer.getPrivateData();
	cout << "Primes set to " << privateData.prime1 << " and " << privateData.prime2 << "." << endl;
	auto publicData = cryptographer.publish();
	cout << "The server has published:\n\tM = " << publicData.modularBase
		<< "\nand\te = " << publicData.exponent << "\nSecretly, the server knows:\n\td = "
		<< privateData.inverse << endl;
	auto output = rsaEnvironment.enterEnvironment(arg);
	cout << "Exiting RSA Encryption Environment." << endl;
	return output;
}

UserEnvironment buildGroundEnvironment(
	AffineShiftCipher& affineCipher, UserEnvironment& affineEnvironment,
	ColumnarCipher& columnarCipher, UserEnvironment& columnarEnvironment,
	RSA_Encryptor& rsaEncryptor, UserEnvironment& rsaEnvironment)
{
	UserEnvironment groundEnvironment("Ground Environment", "Base environment, \
		serves as the entry point of the program and a place to choose which \
		encryption environment you would like to enter.");
	groundEnvironment.addCallSign("Affine Cipher Environment.", {"affine", "affine_cipher"},
		[&affineCipher, &affineEnvironment](string input) -> string
		{
			return enterAffineCipherEnvironment(affineCipher, affineEnvironment, input);
		});
	groundEnvironment.addCallSign("Columnar Cipher Environment.", {"column", "columnar_cipher", "columnar"},
		[&columnarCipher, &columnarEnvironment](string input) -> string
		{
			return enterColumnarCipherEnvironment(columnarCipher, columnarEnvironment, input);
		});
	groundEnvironment.addCallSign("RSA Encryption Environment.", {"rsa", "rsa_encryption"},
		[&rsaEncryptor, &rsaEnvironment](string input) -> string
		{
			return enterRSA_Environment(rsaEncryptor, rsaEnvironment, input);
		});
		// {{"Specify the alphabet you would like to use for the cipher.", "alphabet", "alpha", "alph"},
		// 	{"Specify the multiplier. Should fit 0 <= n < length of alphabet.", "multiplier", "mult"},
		// 	{"Specify the shift.", "shift"}});
	return groundEnvironment;
}



UserEnvironment buildAffineCipherEnvironment(AffineShiftCipher& affineCipher)
{
	UserEnvironment affineEnvironment(
		"Affine Environment", "Affine cipher environment, \
serves as a user interface with an affine encryptor and decryptor. An affine cipher \
uses modular arithmetic on some alphabet. Namely, it take the input (plain text) and \
multiplies it by some number, here called the multiplier, and adds a different number, \
here called the shift. In modular arithmetic, this results in something back inside \
our alphabet and is the final output (cipher text).");
	SET_ENCRYPTION_CALLSIGN(affineEnvironment, affineCipher);
	SET_DECRYPTION_CALLSIGN(affineEnvironment, affineCipher);
	affineEnvironment.addCallSign("Change multiplier.", {"mult", "multiplier"},
		[&affineCipher](string input) -> string
		{
			auto clip = clipOne(input);
			try
			{
				affineCipher.setMult(stoll(get<0>(clip)));
				cout << "Multiplier changed to " << affineCipher.getMult() << endl;
			}
			catch(...)
			{
				cout << "Invalid value given. Multiplier must be an integer and have no common divisors with length of alphabet." << endl;
			}
			return get<1>(clip);
		});
	affineEnvironment.addCallSign("Change shift.", {"shift"},
		[&affineCipher](string input) -> string
		{
			auto clip = clipOne(input);//grab the first word from input
			try
			{
				affineCipher.setShift(stoll(get<0>(clip)));
				cout << "Shift changed to " << affineCipher.getShift() << endl;
			}
			catch(...)
			{
				cout << "Invalid value given. Shift must be an integer." << endl;
			}
			return get<1>(clip);
		});
	return affineEnvironment;
}



UserEnvironment buildColumnarCipherEnvironment(ColumnarCipher& columnarCipher)
{
	UserEnvironment columnarEnvironment(
		"Columnar Environment", "Columnar cipher environment, \
serves as a user interface with an columnar encryptor and decryptor. ");
	SET_ENCRYPTION_CALLSIGN(columnarEnvironment, columnarCipher);
	SET_DECRYPTION_CALLSIGN(columnarEnvironment, columnarCipher);
	columnarEnvironment.addCallSign("Change encryption Key.", {"key"},
		[&columnarCipher](string input) -> string
		{
			auto clip = clipOne(input);//grab the first word from input
			try
			{
				columnarCipher.setKey(get<0>(clip));
				cout << "Key changed to " << columnarCipher.getKey() << endl;
			}
			catch(...)
			{
				cout << "Invalid value given." << endl;
			}
			return get<1>(clip);
		});
	return columnarEnvironment;
}

UserEnvironment buildRSA_EncryptionEnvironment(RSA_Encryptor& rsaEncryptor)
{
	UserEnvironment rsaEnvironment(
		"RSA Encryption Environment", "RSA encryption environment, \
			serves as a user interface with a RSA encryptor and decryptor.");

	//encryption callsign
	rsaEnvironment.addCallSign("Encrypt a given number.", {"encrypt"},\
	[&rsaEncryptor](string arg) -> string\
	{\
		try
		{
			unsigned long inputNumber = stoul(arg);
			cout << "Encrypted Number: " << rsaEncryptor.encrypt(inputNumber) << endl;
		}
		catch(...)
		{
			cout << "Invalid value given. Must be an unsigned integer" << endl;
		}
		return "";
	});

	//decryption callsign
	rsaEnvironment.addCallSign("Decrypt a given number.", {"decrypt"},\
	[&rsaEncryptor](string arg) -> string\
	{\
		try
		{
			unsigned long inputNumber = stoul(arg);
			cout << "Encrypted Number: " << rsaEncryptor.decrypt(inputNumber) << endl;
		}
		catch(...)
		{
			cout << "Invalid value given. Must be an unsigned integer" << endl;
		}
		return "";
	});

	//change first prime callsign
	rsaEnvironment.addCallSign("Change the first prime number.", {"prime1", "p1"},
		[&rsaEncryptor](string input) -> string
		{
			auto clip = clipOne(input);//grab the first word from input
			try
			{
				rsaEncryptor.setPrime1(stoul(get<0>(clip)));
				cout << "First prime changed to " << rsaEncryptor.getPrivateData().prime1 << endl;
				auto publicData = rsaEncryptor.publish();
				cout << "The server has published:\n\tM = " << publicData.modularBase
					<< "\nand\te = " << publicData.exponent << "\nSecretly, the server knows:\n\td = "
					<< rsaEncryptor.getPrivateData().inverse << endl;
			}
			catch(...)
			{
				cout << "Invalid value given. Must be an unsigned integer" << endl;
			}
			return get<1>(clip);
		});

	//change second prime callsign
	rsaEnvironment.addCallSign("Change the second prime number.", {"prime2", "p2"},
		[&rsaEncryptor](string input) -> string
		{
			auto clip = clipOne(input);//grab the first word from input
			try
			{
				rsaEncryptor.setPrime2(stoul(get<0>(clip)));
				cout << "Second prime changed to " << rsaEncryptor.getPrivateData().prime2 << endl;
				auto publicData = rsaEncryptor.publish();
				cout << "The server has published:\n\tM = " << publicData.modularBase
					<< "\nand\te = " << publicData.exponent << "\nSecretly, the server knows:\n\td = "
					<< rsaEncryptor.getPrivateData().inverse << endl;
			}
			catch(...)
			{
				cout << "Invalid value given. Must be an unsigned integer" << endl;
			}
			return get<1>(clip);
		});

	//change exponent callsign
	rsaEnvironment.addCallSign("Change the exponent.", {"exponent", "exp"},
		[&rsaEncryptor](string input) -> string
		{
			auto clip = clipOne(input);//grab the first word from input
			try
			{
				rsaEncryptor.setExponent(stoul(get<0>(clip)));
				auto publicData = rsaEncryptor.publish();
				cout << "Exponent changed to " << publicData.exponent << endl;
				cout << "The server has published:\n\tM = " << publicData.modularBase
					<< "\nand\te = " << publicData.exponent << "\nSecretly, the server knows:\n\td = "
				<< rsaEncryptor.getPrivateData().inverse << endl;
			}
			catch(...)
			{
				cout << "Invalid value given. Exponent must be an integer and have no common factors with (p-1)(q-1)." << endl;
			}
			return get<1>(clip);
		});
	return rsaEnvironment;
}

