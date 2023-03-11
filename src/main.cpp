#include <string>
#include <vector>
#include <iostream>
#include <functional>

#include "User_Environment.hpp"
#include "Affine_Shift_Cipher.hpp"
#include "Columnar_Cipher.hpp"
#include "RSA_Encryption.hpp"
#include "Global_Functions.hpp"

#include "LargeNumbers.hpp"
#include "LargeRSA.hpp"
#include "LargeNumberPrimality.hpp"

constexpr size_t primeSize = 16;

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

	std::cout
		<< "Welcome to my cryptography exploration program!\n"
		<< "You can type \"help\" for a list of commands.\n";

	std::string lowerCaseChars = "abcdefghijklmnopqrstuvwxyz";
	// std::string alphaNumeric("0123456789abcdefghijklmnopqrstuvwxyz");
	// std::string decimalSet("0123456789");
	// std::string octalSet("01234567");
	// std::string hexSet("0123456789abcdef");

	AffineShiftCipher affineCipher(lowerCaseChars, 1, 0);
	UserEnvironment affineEnvironment(buildAffineCipherEnvironment(affineCipher));


	ColumnarCipher columnarCipher(lowerCaseChars, "abcde");
	UserEnvironment columnarEnvironment(buildColumnarCipherEnvironment(columnarCipher));


	RSA_Encryptor rsaEncryptor(53359, 13187, 238473277);
	UserEnvironment rsaEnvironment(buildRSA_EncryptionEnvironment(rsaEncryptor));

	Large_RSA_Encryptor<primeSize> rsaEncryptorLarge(
		LargeNumber<primeSize>({
			0x6b8b4567, 0x327b23c6, 0x643c9869, 0x66334873,
			0x74b0dc51, 0x19495cff, 0x2ae8944a, 0x625558ec,
			0x238e1f29, 0x46e87ccd, 0x3d1b58ba, 0x507ed7ab,
			0x2eb141f2, 0x41b71efb, 0x79e2a9e3, 0x757eb01f}),//<-big prime
		LargeNumber<primeSize>({
			0x14e17e33, 0x3222e7cd, 0x74de0ee3, 0x68ebc550,
			0x2df6d648, 0x46b7d447, 0x4a2ac315, 0x39ee015c,
			0x57fc4fbb, 0x0cc1016f, 0x43f18422, 0x60ef0119,
			0x26f324ba, 0x7f01579b, 0x49da307d, 0x70ac2a51}),//<-big prime
		LargeNumber<2*primeSize>({
			0x034cf912, 0x0b9a7ca6, 0xa7e16709, 0xbcae11b1,
			0x88176ee1, 0x15bd55f8, 0x64f5381a, 0x38a23001,
			0x6e4109b0, 0x49e75a17, 0x536f8012, 0x9a690cef,
			0x02f1875e, 0x869bcc82, 0x8df710cd, 0xbd0af5a6,
			0xe970dd54, 0xb0e43d74, 0x7e74316b, 0xddc8d310,
			0x90050fcf, 0x35fa14d6, 0x87819551, 0x8ea3d4c4,
			0x01737ed1, 0x856f6dbc, 0xa80d2d14, 0x5b11f2d7,
			0xf828dab0, 0x5b265ae3, 0xb2ce4803, 0xbdb3085b})//<-really big prime for exponent
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

std::string enterAffineCipherEnvironment(AffineShiftCipher& cryptographer, UserEnvironment& affineEnvironment, std::string arg)
{
	std::cout << "Entering Affine Cipher Environment." << "\n";
	std::cout << "Multiplying parameter: " << cryptographer.getMult() << "\n";
	std::cout << "Shift parameter: " << cryptographer.getShift() << "\n";
	auto output = affineEnvironment.enterEnvironment(arg);
	std::cout << "Exiting Affine Cipher Environment." << "\n";
	return output;
}

std::string enterColumnarCipherEnvironment(ColumnarCipher& cryptographer, UserEnvironment& columnarEnvironment, std::string arg)
{
	std::cout << "Entering Columnar Cipher Environment." << "\n";
	std::cout << "Key: " << cryptographer.getKey() << "\n";
	auto output = columnarEnvironment.enterEnvironment(arg);
	std::cout << "Exiting Columnar Cipher Environment." << "\n";
	return output;
}

std::string enterRSA_Environment(RSA_Encryptor& cryptographer, UserEnvironment& rsaEnvironment, std::string arg)
{
	std::cout << "Entering RSA Encryption Environment." << "\n";
	auto privateData = cryptographer.getPrivateData();
	std::cout << "Primes set to " << privateData.prime1 << " and " << privateData.prime2 << "." << "\n";
	auto publicData = cryptographer.publish();
	std::cout << "The server has published:\n\tM = " << publicData.modularBase
		<< "\nand\te = " << publicData.exponent << "\nSecretly, the server knows:\n\td = "
		<< privateData.inverse << "\n";
	auto output = rsaEnvironment.enterEnvironment(arg);
	std::cout << "Exiting RSA Encryption Environment." << "\n";
	return output;
}

std::string enterLargeRSA_Environment(Large_RSA_Encryptor<primeSize>& cryptographer, UserEnvironment& rsaEnvironment, std::string arg)
{
	std::cout << "Entering Large RSA Encryption Environment." << "\n";
	auto output = rsaEnvironment.enterEnvironment(arg);
	std::cout << "Exiting Large RSA Encryption Environment." << "\n";
	return output;
}

UserEnvironment buildGroundEnvironment(
	AffineShiftCipher& affineCipher, UserEnvironment& affineEnvironment,
	ColumnarCipher& columnarCipher, UserEnvironment& columnarEnvironment,
	RSA_Encryptor& rsaEncryptor, UserEnvironment& rsaEnvironment,
	Large_RSA_Encryptor<primeSize>& rsaEncryptorLarge, UserEnvironment& rsaEnvironmentLarge)
{
	UserEnvironment groundEnvironment(
		"Ground Environment",
		"Base environment, serves as the entry point of the program and a place \
to choose which encryption environment you would like to enter.\n\n\
Each \"Callsign\" is what you can type in to run a command. \
Each command has a primary callsign as well as alternative callsigns you can use.");
	groundEnvironment.addCallSign("Affine Cipher Environment.", {"affine", "affine_cipher"},
		[&affineCipher, &affineEnvironment](std::string input) -> std::string
		{
			return enterAffineCipherEnvironment(affineCipher, affineEnvironment, input);
		});
	groundEnvironment.addCallSign("Columnar Cipher Environment.", {"column", "columnar_cipher", "columnar"},
		[&columnarCipher, &columnarEnvironment](std::string input) -> std::string
		{
			return enterColumnarCipherEnvironment(columnarCipher, columnarEnvironment, input);
		});
	groundEnvironment.addCallSign("RSA Encryption Environment.", {"rsa", "rsa_encryption"},
		[&rsaEncryptor, &rsaEnvironment](std::string input) -> std::string
		{
			return enterRSA_Environment(rsaEncryptor, rsaEnvironment, input);
		});
	groundEnvironment.addCallSign("Large RSA Encryption Environment.", {"large_rsa", "rsa_large", "large_rsa_encryptor"},
		[&rsaEncryptorLarge, &rsaEnvironmentLarge](std::string input) -> std::string
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
		"Affine Environment", "The affine cipher environment \
serves as a user interface with an affine encryptor and decryptor. An affine cipher \
uses modular arithmetic on some alphabet. Namely, it take the input (plain text) and \
multiplies it by some number (multiplier) and adds a different number (shift). \
In modular arithmetic, this results in something back inside \
our alphabet and is the final output (cipher text).");
	affineEnvironment.addCallSign("Encrypt a given string. Must use only lower case letters.", {"encrypt"},
		[&affineCipher](std::string arg) -> std::string
		{
			try
			{
				std::cout << "Encrypted Number: " << affineCipher.encrypt(arg) << "\n";
			}
			catch(...)
			{
				std::cout << "Invalid value given. Must be a string with only lower case letters." << "\n";
			}
			return "";
		});

	affineEnvironment.addCallSign("Decrypt a given string. Must use only lower case letters.", {"decrypt"},
		[&affineCipher](std::string arg) -> std::string
		{
			try
			{
				std::cout << "Encrypted Number: " << affineCipher.decrypt(arg) << "\n";
			}
			catch(...)
			{
				std::cout << "Invalid value given. Must be a string with only lower case letters." << "\n";
			}
			return "";
		});

	affineEnvironment.addCallSign("Change multiplier. Accepts one unsigned integer relatively prime to 26.", {"mult", "multiplier"},
		[&affineCipher](std::string input) -> std::string
		{
			auto clip = clipOne(input);
			try
			{
				affineCipher.setMult(stoull(std::get<0>(clip)));
				std::cout << "Multiplier changed to " << affineCipher.getMult() << "\n";
			}
			catch(...)
			{
				std::cout << "Invalid value given. Multiplier must be an integer and have no common divisors with length of alphabet." << "\n";
			}
			return std::get<1>(clip);
		});
	affineEnvironment.addCallSign("Change shift. Accepts one unsigned integer relatively prime to 26.", {"shift"},
		[&affineCipher](std::string input) -> std::string
		{
			auto clip = clipOne(input);//grab the first word from input
			try
			{
				affineCipher.setShift(stoll(std::get<0>(clip)));
				std::cout << "Shift changed to " << affineCipher.getShift() << "\n";
			}
			catch(...)
			{
				std::cout << "Invalid value given. Shift must be an integer." << "\n";
			}
			return std::get<1>(clip);
		});
	return affineEnvironment;
}



UserEnvironment buildColumnarCipherEnvironment(ColumnarCipher& columnarCipher)
{
	UserEnvironment columnarEnvironment(
		"Columnar Environment", "The columnar cipher environment \
serves as a user interface with a columnar encryptor and decryptor. \
This cipher writes the message to a grid in row major order and reads it \
back in column major order. The columns are also rearranged according \
to the permutation needed to put the key into alphabetical order.");
	columnarEnvironment.addCallSign("Encrypt a given string.", {"encrypt"},
		[&columnarCipher](std::string arg) -> std::string
		{
			try
			{
				std::cout << "Encrypted Number: " << columnarCipher.encrypt(arg) << "\n";
			}
			catch(...)
			{
				std::cout << "Invalid value given. Arbitrary text is allowed; this is an internal error." << "\n";
			}
			return "";
		});

	columnarEnvironment.addCallSign("Decrypt a given string.", {"decrypt"},
		[&columnarCipher](std::string arg) -> std::string
		{
			try
			{
				std::cout << "Encrypted Number: " << columnarCipher.decrypt(arg) << "\n";
			}
			catch(...)
			{
				std::cout << "Invalid value given. Arbitrary text is allowed; this is an internal error." << "\n";
			}
			return "";
		});

	columnarEnvironment.addCallSign("Change encryption Key to a given string.", {"key"},
		[&columnarCipher](std::string input) -> std::string
		{
			auto clip = clipOne(input);//grab the first word from input
			try
			{
				columnarCipher.setKey(std::get<0>(clip));
				std::cout << "Key changed to " << columnarCipher.getKey() << "\n";
			}
			catch(...)
			{
				std::cout << "Invalid value given." << "\n";
			}
			return std::get<1>(clip);
		});
	return columnarEnvironment;
}

UserEnvironment buildRSA_EncryptionEnvironment(RSA_Encryptor& rsaEncryptor)
{
	UserEnvironment rsaEnvironment(
		"RSA Encryption Environment",
		"The RSA encryption environment serves as a user interface with an \
RSA encryptor and decryptor. RSA is the theoretically most sophisticated algorithm \
implemented in this program. This algorithm uses two primes, p and q, (whose size dictates \
the level of security of the system) and works in a number system modulo n=pq. In this system, \
a pair of exponential inverses can be made, e and d. (I.e., (x^e)^d = x mod n for all x) \
The server then publishes e and n. By keeping p, q, and d secret, secure messages can \
be sent from the public to the server.");

	//encryption callsign
	rsaEnvironment.addCallSign("Encrypt a given number.", {"encrypt"},
		[&rsaEncryptor](std::string arg) -> std::string
		{
			try
			{
				unsigned long inputNumber = stoul(arg);
				std::cout << "Encrypted Number: " << rsaEncryptor.encrypt(inputNumber) << "\n";
			}
			catch(...)
			{
				std::cout << "Invalid value given. Must be an unsigned integer" << "\n";
			}
			return "";
		});

	//decryption callsign
	rsaEnvironment.addCallSign("Decrypt a given number.", {"decrypt"},
		[&rsaEncryptor](std::string arg) -> std::string
		{
			try
			{
				unsigned long inputNumber = stoul(arg);
				std::cout << "Encrypted Number: " << rsaEncryptor.decrypt(inputNumber) << "\n";
			}
			catch(...)
			{
				std::cout << "Invalid value given. Must be an unsigned integer" << "\n";
			}
			return "";
		});

	//change first prime callsign
	rsaEnvironment.addCallSign("Change the first prime to a given number.", {"prime1", "p1"},
		[&rsaEncryptor](std::string input) -> std::string
		{
			auto clip = clipOne(input);//grab the first word from input
			try
			{
				rsaEncryptor.setPrime1(stoul(std::get<0>(clip)));
				std::cout << "First prime changed to " << rsaEncryptor.getPrivateData().prime1 << "\n";
				auto publicData = rsaEncryptor.publish();
				std::cout << "The server has published:\n\tM = " << publicData.modularBase
					<< "\nand\te = " << publicData.exponent << "\nSecretly, the server knows:\n\td = "
					<< rsaEncryptor.getPrivateData().inverse << "\n";
			}
			catch(...)
			{
				std::cout << "Invalid value given. Must be an unsigned integer" << "\n";
			}
			return std::get<1>(clip);
		});

	//change second prime callsign
	rsaEnvironment.addCallSign("Change the second prime to a given number.", {"prime2", "p2"},
		[&rsaEncryptor](std::string input) -> std::string
		{
			auto clip = clipOne(input);//grab the first word from input
			try
			{
				rsaEncryptor.setPrime2(stoul(std::get<0>(clip)));
				std::cout << "Second prime changed to " << rsaEncryptor.getPrivateData().prime2 << "\n";
				auto publicData = rsaEncryptor.publish();
				std::cout << "The server has published:\n\tM = " << publicData.modularBase
					<< "\nand\te = " << publicData.exponent << "\nSecretly, the server knows:\n\td = "
					<< rsaEncryptor.getPrivateData().inverse << "\n";
			}
			catch(...)
			{
				std::cout << "Invalid value given. Must be an unsigned integer" << "\n";
			}
			return std::get<1>(clip);
		});

	//change exponent callsign
	rsaEnvironment.addCallSign("Change the exponent.", {"exponent", "exp"},
		[&rsaEncryptor](std::string input) -> std::string
		{
			auto clip = clipOne(input);//grab the first word from input
			try
			{
				rsaEncryptor.setExponent(stoul(std::get<0>(clip)));
				auto publicData = rsaEncryptor.publish();
				std::cout << "Exponent changed to " << publicData.exponent << "\n";
				std::cout << "The server has published:\n\tM = " << publicData.modularBase
					<< "\nand\te = " << publicData.exponent << "\nSecretly, the server knows:\n\td = "
				<< rsaEncryptor.getPrivateData().inverse << "\n";
			}
			catch(...)
			{
				std::cout << "Invalid value given. Exponent must be an integer and have no common factors with (p-1)(q-1)." << "\n";
			}
			return std::get<1>(clip);
		});
	return rsaEnvironment;
}

UserEnvironment buildLargeRSA_EncryptionEnvironment(Large_RSA_Encryptor<primeSize>& rsaEncryptor)
{
	UserEnvironment rsaEnvironment(
		"Large RSA Encryption Environment", "The large number RSA encryption environment \
serves as a user interface with an RSA encryptor and decryptor. Unlike the non-large RSA \
environment, this one uses 512 bit primes and a 1024 bit modular base. See the \
non-large variant for a more detailed description of RSA.");

	//encryption callsign
	rsaEnvironment.addCallSign("Encrypt a given message of 124 characters or less.", {"encrypt"},
		[&rsaEncryptor](std::string arg) -> std::string
		{
			std::cout << "Encrypted Value: " << rsaEncryptor.encrypt(rsaEncryptor.encode(arg)) << "\n";
			return "";
		});

	// //decryption callsign
	rsaEnvironment.addCallSign("Decrypt a given number into a plaintext message.\
Accepts 32 space seperated 32-bit numbers in hex format.", {"decrypt"},
		[&rsaEncryptor](std::string arg) -> std::string
		{
			std::vector<std::string> inputStrings(parse(arg));
			std::vector<unsigned int> inputValues;
			try
			{
				for (std::string input : inputStrings)
				{
					// std::cout << stoul("0x" + input) << "\n";
					inputValues.push_back(stoul("0x" + input, nullptr, 16));
				}
			}
			catch(...)
			{
				std::cout << "Invalid arguments. Give a space separated list of hexadecimal numbers." << "\n";
				return "";
			}
			if (inputValues.size() > primeSize * 2)
			{
				inputValues = std::vector<unsigned int>(
					inputValues.begin() + (inputValues.size() - primeSize * 2), inputValues.end());
			}
			else if (inputValues.size() < primeSize * 2)
			{
				inputValues.insert(inputValues.begin(), primeSize * 2 - inputValues.size(),
					0);
			}
			LargeNumber<2 * primeSize> encryptedValue(inputValues);
			std::cout << "Decrypted Text: " << rsaEncryptor.decode(rsaEncryptor.decrypt(encryptedValue)) << "\n";
			return "";
		});

	// //change first prime callsign
	// rsaEnvironment.addCallSign("Change the first prime number.", {"prime1", "p1"},
	// 	[&rsaEncryptor](std::string input) -> std::string
	// 	{
	// 		auto clip = clipOne(input);//grab the first word from input
	// 		try
	// 		{
	// 			rsaEncryptor.setPrime1(stoul(std::get<0>(clip)));
	// 			std::cout << "First prime changed to " << rsaEncryptor.getPrivateData().prime1 << "\n";
	// 			auto publicData = rsaEncryptor.publish();
	// 			std::cout << "The server has published:\n\tM = " << publicData.modularBase
	// 				<< "\nand\te = " << publicData.exponent << "\nSecretly, the server knows:\n\td = "
	// 				<< rsaEncryptor.getPrivateData().inverse << "\n";
	// 		}
	// 		catch(...)
	// 		{
	// 			std::cout << "Invalid value given. Must be an unsigned integer" << "\n";
	// 		}
	// 		return std::get<1>(clip);
	// 	});

	// //change second prime callsign
	// rsaEnvironment.addCallSign("Change the second prime number.", {"prime2", "p2"},
	// 	[&rsaEncryptor](std::string input) -> std::string
	// 	{
	// 		auto clip = clipOne(input);//grab the first word from input
	// 		try
	// 		{
	// 			rsaEncryptor.setPrime2(stoul(std::get<0>(clip)));
	// 			std::cout << "Second prime changed to " << rsaEncryptor.getPrivateData().prime2 << "\n";
	// 			auto publicData = rsaEncryptor.publish();
	// 			std::cout << "The server has published:\n\tM = " << publicData.modularBase
	// 				<< "\nand\te = " << publicData.exponent << "\nSecretly, the server knows:\n\td = "
	// 				<< rsaEncryptor.getPrivateData().inverse << "\n";
	// 		}
	// 		catch(...)
	// 		{
	// 			std::cout << "Invalid value given. Must be an unsigned integer" << "\n";
	// 		}
	// 		return std::get<1>(clip);
	// 	});

	// //change exponent callsign
	// rsaEnvironment.addCallSign("Change the exponent.", {"exponent", "exp"},
	// 	[&rsaEncryptor](std::string input) -> std::string
	// 	{
	// 		auto clip = clipOne(input);//grab the first word from input
	// 		try
	// 		{
	// 			rsaEncryptor.setExponent(stoul(std::get<0>(clip)));
	// 			auto publicData = rsaEncryptor.publish();
	// 			std::cout << "Exponent changed to " << publicData.exponent << "\n";
	// 			std::cout << "The server has published:\n\tM = " << publicData.modularBase
	// 				<< "\nand\te = " << publicData.exponent << "\nSecretly, the server knows:\n\td = "
	// 			<< rsaEncryptor.getPrivateData().inverse << "\n";
	// 		}
	// 		catch(...)
	// 		{
	// 			std::cout << "Invalid value given. Exponent must be an integer and have no common factors with (p-1)(q-1)." << "\n";
	// 		}
	// 		return std::get<1>(clip);
	// 	});
	return rsaEnvironment;
}
