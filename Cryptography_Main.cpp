
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

#define primeSize 16

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

	typedef LargeNumber<4> num;

	// num a({0x23842232, 0x47323423, 0x83916578, 0x91029579});
	// num b({0x00012123, 0xabcdef12, 0x2301fba8, 0x9112febc});
	// cout << (a/b) << endl;
	// cout << hex << (0x23842232/0x00012123) << dec << endl;

	cout << (num::maxInt() / num::maxInt()) << endl;

	// const size_t primeSize = 8;

	// typedef LargeNumber<primeSize> primeNum;
	// typedef LargeNumber<primeSize * 2> modBaseNum;
	// // typedef

	// primeNum p1(generatePrime(primeNum::maxInt()));
	// primeNum p2(generatePrime(primeNum::maxInt()));

	// cout << "reached" << endl;

	// Large_RSA_Encryptor<primeSize> testEncryptor(p1, p2, modBaseNum::unity());

	// cout << "reached" << endl;

	// while(!(testEncryptor.setExponent(generateRandomNumber(
	// 	modBaseNum::unity(), testEncryptor.getExponentBase()))))
	// {
	// 	cout << "doing something" << endl;
	// }
	// auto temp = testEncryptor.decode(testEncryptor.decrypt(
	// 	testEncryptor.encrypt(testEncryptor.encode("abcdefghijklmnopqrstuvwxyz"))));
	// cout << temp << endl;

	// Large_RSA_Encryptor<4> testEncryptor(
	// 	LargeNumber<4>({0x5FC591F8, 0x9068E88C, 0xE1D610C0, 0x59D0598D}),
	// 	LargeNumber<4>({0xE0F1EA21, 0xC306376F, 0x0C1572D3, 0x4F4AB4A1}),
	// 	LargeNumber<8>({0x31277B47, 0xD2EBC175, 0x7E542D69, 0x1700DAC9,
	// 					0xE5D4B275, 0x80E8CB16, 0x38DE03F4, 0x5967504D}));

	// auto temp = testEncryptor.decode(testEncryptor.decrypt(
	// 	testEncryptor.encrypt(testEncryptor.encode("abcdefghijklmnopqrstuvwxyz"))));

	// cout << temp << endl;
	// LargeNumber<primeSize> a({
	// 	0x44c972ae, 0x4f5d0597, 0x439d4af3, 0x384a3464,
	// 	0x55f5f29b, 0x22e5bb2c, 0x604989f8, 0x07cea81b,
	// 	0x73272b61, 0x0be1a3b2, 0x7d1426b7, 0x56d5179e,
	// 	0x52c46260, 0x74191f49, 0x3899d23b, 0xccb6ab1});
	// LargeNumber<primeSize> b({
	// 	0x6b8b4567, 0x327b23c6, 0x643c9869, 0x66334873,
	// 	0x74b0dc51, 0x19495cff, 0x2ae8944a, 0x625558ec, 
	// 	0x238e1f29, 0x46e87ccd, 0x3d1b58ba, 0x507ed7ab,
	// 	0x2eb141f2, 0x41b71efb, 0x79e2a9e3, 0x757eb01f});

	// LargeNumber<primeSize*2> c({
	// 	0x0d7168ac 0xe64f6478 0xcc87930d 0x2cc6690e
	// 	0x6e961b8a 0x23292b9f 0xe55d1289 0x4c4aab1d
	// 	0x8471c3e5 0x28dd0f99 0xa7a36b17 0x4a0fdaf5
	// 	0x65d6283e 0x4836e3df 0x6f3c553c 0x6ea8bc28
	// 	0xca2be00f 0x8b7a0c58 0x4244010a 0x89b624ff
	// 	0x0042c463 0x63e2dd3d 0x023219bc 0xecdde871
	// 	0xa281c1ee 0xc66a44ab 0x42139f25 0xc1bdae4c
	// 	0x6ffb9846 0x637dfaf3 0xe834f899 0x2dcedf8b
	// })

	// typedef LargeNumber<primeSize*2> primeNum;
	// // cout << generatePrime(primeNum::maxInt()) << endl << endl;
	// cout << generatePrime(primeNum(a)*primeNum(b)) << endl;

	// return 0;

	// AffineShiftCipher affineCipher(Character::standardLowerCase, 1, 0);
	// UserEnvironment affineEnvironment(buildAffineCipherEnvironment(affineCipher));


	// ColumnarCipher columnarCipher(Character::standardLowerCase, "abcde");
	// UserEnvironment columnarEnvironment(buildColumnarCipherEnvironment(columnarCipher));


	// RSA_Encryptor rsaEncryptor(53359, 13187, 238473277);
	// UserEnvironment rsaEnvironment(buildRSA_EncryptionEnvironment(rsaEncryptor));

	// Large_RSA_Encryptor<primeSize> rsaEncryptorLarge(
	// 	LargeNumber<primeSize>({
	// 		0x44c972ae, 0x4f5d0597, 0x439d4af3, 0x384a3464,//prime 1
	// 		0x55f5f29b, 0x22e5bb2c, 0x604989f8, 0x07cea81b,
	// 		0x73272b61, 0x0be1a3b2, 0x7d1426b7, 0x56d5179e,
	// 		0x52c46260, 0x74191f49, 0x3899d23b, 0x0ccb6ab1}),//<-big prime
	// 	LargeNumber<primeSize>({
	// 		0x6b8b4567, 0x327b23c6, 0x643c9869, 0x66334873,//prime 2
	// 		0x74b0dc51, 0x19495cff, 0x2ae8944a, 0x625558ec, 
	// 		0x238e1f29, 0x46e87ccd, 0x3d1b58ba, 0x507ed7ab,
	// 		0x2eb141f2, 0x41b71efb, 0x79e2a9e3, 0x757eb01f}),//<-big prime
	// 	LargeNumber<2*primeSize>({
	// 		0x0d7168ac, 0xe64f6478, 0xcc87930d, 0x2cc6690e,//exponent
	// 		0x6e961b8a, 0x23292b9f, 0xe55d1289, 0x4c4aab1d,
	// 		0x8471c3e5, 0x28dd0f99, 0xa7a36b17, 0x4a0fdaf5,
	// 		0x65d6283e, 0x4836e3df, 0x6f3c553c, 0x6ea8bc28,
	// 		0xca2be00f, 0x8b7a0c58, 0x4244010a, 0x89b624ff,
	// 		0x0042c463, 0x63e2dd3d, 0x023219bc, 0xecdde871,
	// 		0xa281c1ee, 0xc66a44ab, 0x42139f25, 0xc1bdae4c,
	// 		0x6ffb9846, 0x637dfaf3, 0xe834f899, 0x2dcedf8b})//<-really big prime
	// 	);
	// UserEnvironment rsaEnvironmentLarge(buildLargeRSA_EncryptionEnvironment(rsaEncryptorLarge));


	// UserEnvironment groundEnvironment(buildGroundEnvironment(
	// 	affineCipher, affineEnvironment,
	// 	columnarCipher, columnarEnvironment,
	// 	rsaEncryptor, rsaEnvironment,
	// 	rsaEncryptorLarge, rsaEnvironmentLarge));
	// groundEnvironment.enterEnvironment();
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
			auto encryptedValue= rsaEncryptor.encrypt(rsaEncryptor.encode(arg));
			cout << "EncryptionValue: " << encryptedValue << endl;
			return "";
		});

	// //decryption callsign
	// rsaEnvironment.addCallSign("Decrypt a given number.", {"decrypt"},
	// 	[&rsaEncryptor](string arg) -> string
	// 	{
	// 		try
	// 		{
	// 			unsigned long inputNumber = stoul(arg);
	// 			cout << "Encrypted Number: " << rsaEncryptor.decrypt(inputNumber) << endl;
	// 		}
	// 		catch(...)
	// 		{
	// 			cout << "Invalid value given. Must be an unsigned integer" << endl;
	// 		}
	// 		return "";
	// 	});

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
