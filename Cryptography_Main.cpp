
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

// #include "LargeNumbers.h"
#include "LargeRSA.h"
#include "LargeNumberPrimality.h"

#define primeSize 2

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
UserEnvironment buildLargeRSA_EncryptionEnvironment(Large_RSA_Encryptor<primeSize>& rsaEncryptor);

UserEnvironment buildGroundEnvironment(
	AffineShiftCipher& affineCipher, UserEnvironment& affineEnvironment,
	ColumnarCipher& columnarCipher, UserEnvironment& columnarEnvironment,
	RSA_Encryptor& rsaEncryptor, UserEnvironment& rsaEnvironment,
	Large_RSA_Encryptor<primeSize>& rsaEncryptorLarge, UserEnvironment& rsaEnvironmentLarge);

int main(){
	// LargeNumber<primeSize> a({
	// 	0x6b8b4567, 0x327b23c6, 0x643c9869, 0x66334873,
	// 	0x74b0dc51, 0x19495cff, 0x2ae8944a, 0x625558ec,
	// 	0x238e1f29, 0x46e87ccd, 0x3d1b58ba, 0x507ed7ab,
	// 	0x2eb141f2, 0x41b71efb, 0x79e2a9e3, 0x757eb01f
	// });
	// LargeNumber<primeSize> b({
	// 	0x14e17e33, 0x3222e7cd, 0x74de0ee3, 0x68ebc550,
	// 	0x2df6d648, 0x46b7d447, 0x4a2ac315, 0x39ee015c,
	// 	0x57fc4fbb, 0x0cc1016f, 0x43f18422, 0x60ef0119,
	// 	0x26f324ba, 0x7f01579b, 0x49da307d, 0x70ac2a51
	// });

	// LargeNumber<primeSize*2> c({
	// 	0x034cf912, 0x0b9a7ca6, 0xa7e16709, 0xbcae11b1,
	// 	0x88176ee1, 0x15bd55f8, 0x64f5381a, 0x38a23001,
	// 	0x6e4109b0, 0x49e75a17, 0x536f8012, 0x9a690cef,
	// 	0x02f1875e, 0x869bcc82, 0x8df710cd, 0xbd0af5a6,
	// 	0xe970dd54, 0xb0e43d74, 0x7e74316b, 0xddc8d310,
	// 	0x90050fcf, 0x35fa14d6, 0x87819551, 0x8ea3d4c4,
	// 	0x01737ed1, 0x856f6dbc, 0xa80d2d14, 0x5b11f2d7,
	// 	0xf828dab0, 0x5b265ae3, 0xb2ce4803, 0xbdb3085b
	// })

	AffineShiftCipher affineCipher(Character::standardLowerCase, 1, 0);
	UserEnvironment affineEnvironment(buildAffineCipherEnvironment(affineCipher));


	ColumnarCipher columnarCipher(Character::standardLowerCase, "abcde");
	UserEnvironment columnarEnvironment(buildColumnarCipherEnvironment(columnarCipher));


	RSA_Encryptor rsaEncryptor(53359, 13187, 238473277);
	UserEnvironment rsaEnvironment(buildRSA_EncryptionEnvironment(rsaEncryptor));

	// Large_RSA_Encryptor<primeSize> rsaEncryptorLarge(
	// 	LargeNumber<primeSize>({
	// 		0x6b8b4567, 0x327b23c6, 0x643c9869, 0x66334873,
	// 		0x74b0dc51, 0x19495cff, 0x2ae8944a, 0x625558ec,
	// 		0x238e1f29, 0x46e87ccd, 0x3d1b58ba, 0x507ed7ab,
	// 		0x2eb141f2, 0x41b71efb, 0x79e2a9e3, 0x757eb01f}),//<-big prime
	// 	LargeNumber<primeSize>({
	// 		0x14e17e33, 0x3222e7cd, 0x74de0ee3, 0x68ebc550,
	// 		0x2df6d648, 0x46b7d447, 0x4a2ac315, 0x39ee015c,
	// 		0x57fc4fbb, 0x0cc1016f, 0x43f18422, 0x60ef0119,
	// 		0x26f324ba, 0x7f01579b, 0x49da307d, 0x70ac2a51}),//<-big prime
	// 	LargeNumber<2*primeSize>({
	// 		0x034cf912, 0x0b9a7ca6, 0xa7e16709, 0xbcae11b1,
	// 		0x88176ee1, 0x15bd55f8, 0x64f5381a, 0x38a23001,
	// 		0x6e4109b0, 0x49e75a17, 0x536f8012, 0x9a690cef,
	// 		0x02f1875e, 0x869bcc82, 0x8df710cd, 0xbd0af5a6,
	// 		0xe970dd54, 0xb0e43d74, 0x7e74316b, 0xddc8d310,
	// 		0x90050fcf, 0x35fa14d6, 0x87819551, 0x8ea3d4c4,
	// 		0x01737ed1, 0x856f6dbc, 0xa80d2d14, 0x5b11f2d7,
	// 		0xf828dab0, 0x5b265ae3, 0xb2ce4803, 0xbdb3085b})//<-really big prime
	// 	);
	Large_RSA_Encryptor<primeSize> rsaEncryptorLarge(
		LargeNumber<primeSize>({
			0xdc95547e, 0x301f78c7}),//<-big prime
		LargeNumber<primeSize>({
			0xa9cb8451, 0xa3ee3389}),//<-big prime
		LargeNumber<2*primeSize>({
			0x034cf912, 0x0b9a7ca6, 0xa7e16709, 0xbcae11b1})//<-really big prime
		);
	UserEnvironment rsaEnvironmentLarge(buildLargeRSA_EncryptionEnvironment(rsaEncryptorLarge));


	UserEnvironment groundEnvironment(buildGroundEnvironment(
		affineCipher, affineEnvironment,
		columnarCipher, columnarEnvironment,
		rsaEncryptor, rsaEnvironment,
		rsaEncryptorLarge, rsaEnvironmentLarge));
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

string enterLargeRSA_Environment(Large_RSA_Encryptor<primeSize>& cryptographer, UserEnvironment& rsaEnvironment, string arg)
{
	cout << "Entering Large RSA Encryption Environment." << endl;
	auto output = rsaEnvironment.enterEnvironment(arg);
	cout << "Exiting Large RSA Encryption Environment." << endl;
	return output;
}

UserEnvironment buildGroundEnvironment(
	AffineShiftCipher& affineCipher, UserEnvironment& affineEnvironment,
	ColumnarCipher& columnarCipher, UserEnvironment& columnarEnvironment,
	RSA_Encryptor& rsaEncryptor, UserEnvironment& rsaEnvironment,
	Large_RSA_Encryptor<primeSize>& rsaEncryptorLarge, UserEnvironment& rsaEnvironmentLarge)
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
	groundEnvironment.addCallSign("Large RSA Encryption Environment.", {"large_rsa", "rsa_large", "large_rsa_encryptor"},
		[&rsaEncryptorLarge, &rsaEnvironmentLarge](string input) -> string
		{
			return enterLargeRSA_Environment(rsaEncryptorLarge, rsaEnvironmentLarge, input);
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
	rsaEnvironment.addCallSign("Encrypt a given number.", {"encrypt"},
		[&rsaEncryptor](string arg) -> string
		{
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
	rsaEnvironment.addCallSign("Decrypt a given number.", {"decrypt"},
		[&rsaEncryptor](string arg) -> string
		{
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

UserEnvironment buildLargeRSA_EncryptionEnvironment(Large_RSA_Encryptor<primeSize>& rsaEncryptor)
{
	UserEnvironment rsaEnvironment(
		"Large RSA Encryption Environment", "RSA encryption environment using large number arithmetic, \
			serves as a user interface with a RSA encryptor and decryptor. Unlike the other rsa \
			rsa environment, this one uses 512 bit primes and a 1024 bit modular base.");

	//description of what makes this encryptor so special
	rsaEnvironment.addCallSign("Describe the mechanism.", {"description", "describe"},
		[](string arg) -> string
		{
			cout << "" << endl;
			return arg;
		});

	//encryption callsign
	rsaEnvironment.addCallSign("Encrypt a given message of 124 characters or less.", {"encrypt"},
		[&rsaEncryptor](string arg) -> string
		{
			cout << "Encoded: " << rsaEncryptor.encode(arg) << endl << endl;
			cout << "Full Cycle: " << rsaEncryptor.decrypt(rsaEncryptor.encrypt(rsaEncryptor.encode(arg))) << endl << endl;
			auto encryptedValue= rsaEncryptor.encrypt(rsaEncryptor.encode(arg));
			cout << "EncryptionValue: " << encryptedValue << endl;
			return "";
		});

	// //decryption callsign
	rsaEnvironment.addCallSign("Decrypt a given number into a plaintext message.", {"decrypt"},
		[&rsaEncryptor](string arg) -> string
		{
			vector<string> inputStrings(parse(arg));
			vector<unsigned int> inputValues;
			try
			{
				for (string input : inputStrings)
				{
					// cout << stoul("0x" + input) << endl;
					inputValues.push_back(stoul("0x" + input, nullptr, 16));
				}
			}
			catch(...)
			{
				cout << "Invalid arguments. Give a space separated list of hexadecimal numbers." << endl;
				return "";
			}
			if (inputValues.size() > primeSize * 2)
			{
				cout << "decreasing size" << endl;
				inputValues = vector<unsigned int>(
					inputValues.begin() + (inputValues.size() - primeSize * 2), inputValues.end());
			}
			else if (inputValues.size() < primeSize * 2)
			{
				cout << "increasing size" << endl;
				inputValues.insert(inputValues.begin(), primeSize * 2 - inputValues.size(),
					0);
			}
			cout << inputValues.size() << endl;
			LargeNumber<2 * primeSize> encryptedValue(inputValues);
			cout << "decoded: " << rsaEncryptor.decode(encryptedValue) << endl << endl;
			cout << "decrypted: " << rsaEncryptor.decrypt(encryptedValue) << endl << endl;
			cout << "Decrypted Value: " << rsaEncryptor.decode(rsaEncryptor.decrypt(encryptedValue)) << endl;
			return "";
		});

	// //change first prime callsign
	// rsaEnvironment.addCallSign("Change the first prime number.", {"prime1", "p1"},
	// 	[&rsaEncryptor](string input) -> string
	// 	{
	// 		auto clip = clipOne(input);//grab the first word from input
	// 		try
	// 		{
	// 			rsaEncryptor.setPrime1(stoul(get<0>(clip)));
	// 			cout << "First prime changed to " << rsaEncryptor.getPrivateData().prime1 << endl;
	// 			auto publicData = rsaEncryptor.publish();
	// 			cout << "The server has published:\n\tM = " << publicData.modularBase
	// 				<< "\nand\te = " << publicData.exponent << "\nSecretly, the server knows:\n\td = "
	// 				<< rsaEncryptor.getPrivateData().inverse << endl;
	// 		}
	// 		catch(...)
	// 		{
	// 			cout << "Invalid value given. Must be an unsigned integer" << endl;
	// 		}
	// 		return get<1>(clip);
	// 	});

	// //change second prime callsign
	// rsaEnvironment.addCallSign("Change the second prime number.", {"prime2", "p2"},
	// 	[&rsaEncryptor](string input) -> string
	// 	{
	// 		auto clip = clipOne(input);//grab the first word from input
	// 		try
	// 		{
	// 			rsaEncryptor.setPrime2(stoul(get<0>(clip)));
	// 			cout << "Second prime changed to " << rsaEncryptor.getPrivateData().prime2 << endl;
	// 			auto publicData = rsaEncryptor.publish();
	// 			cout << "The server has published:\n\tM = " << publicData.modularBase
	// 				<< "\nand\te = " << publicData.exponent << "\nSecretly, the server knows:\n\td = "
	// 				<< rsaEncryptor.getPrivateData().inverse << endl;
	// 		}
	// 		catch(...)
	// 		{
	// 			cout << "Invalid value given. Must be an unsigned integer" << endl;
	// 		}
	// 		return get<1>(clip);
	// 	});

	// //change exponent callsign
	// rsaEnvironment.addCallSign("Change the exponent.", {"exponent", "exp"},
	// 	[&rsaEncryptor](string input) -> string
	// 	{
	// 		auto clip = clipOne(input);//grab the first word from input
	// 		try
	// 		{
	// 			rsaEncryptor.setExponent(stoul(get<0>(clip)));
	// 			auto publicData = rsaEncryptor.publish();
	// 			cout << "Exponent changed to " << publicData.exponent << endl;
	// 			cout << "The server has published:\n\tM = " << publicData.modularBase
	// 				<< "\nand\te = " << publicData.exponent << "\nSecretly, the server knows:\n\td = "
	// 			<< rsaEncryptor.getPrivateData().inverse << endl;
	// 		}
	// 		catch(...)
	// 		{
	// 			cout << "Invalid value given. Exponent must be an integer and have no common factors with (p-1)(q-1)." << endl;
	// 		}
	// 		return get<1>(clip);
	// 	});
	return rsaEnvironment;
}
