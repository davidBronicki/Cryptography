#include <string>
#include <vector>
#include <iostream>
#include <functional>

#include "User_Environment.h"
#include "Affine_Shift_Cypher.h"
#include "Character_Set.h"
#include "Global_Functions.h"

#define SET_ENCRYPTION_CALLSIGN(ENVIRONMENT, CRYPTOGRAPHER)\
ENVIRONMENT.addCallSign("Encrypt a given message.", {"encrypt"},\
	[&CRYPTOGRAPHER](string arg) -> string\
	{\
		cout << "Cypher Text: " << CRYPTOGRAPHER.encrypt(arg) << endl;\
		return "";\
	})

using namespace std;

string enterAffineCypherEnvironment(AffineShiftCypher& cryptographer, UserEnvironment& affineEnvironment, string arg)
{
	cout << "Entering Affine Cypher Environment." << endl;
	cout << "Multiplying parameter: " << cryptographer.getMult() << endl;
	cout << "Shift parameter: " << cryptographer.getShift() << endl;
	auto output = affineEnvironment.enterEnvironment(arg);
	cout << "Exiting Affine Cypher Environment." << endl;
	return output;
}

int main(){
	AffineShiftCypher affineCypher(Character::standardLowerCase, 1, 0);
	UserEnvironment affineEnvironment(
		"Affine Environment", "Affine cypher environment, \
serves as a user interface with an affine encryptor and decryptor. An affine cypher \
uses modular arithmetic on some alphabet. Namely, it take the input (plain text) and \
multiplies it by some number, here called the multiplier, and adds a different number, \
here called the shift. In modular arithmetic, this results in something back inside \
our alphabet and is the final output (cypher text).");
	SET_ENCRYPTION_CALLSIGN(affineEnvironment, affineCypher);
	affineEnvironment.addCallSign("Change multiplier.", {"mult", "multiplier"},
		[&affineCypher](string input) -> string
		{
			auto clip = clipOne(input);
			try
			{
				affineCypher.setMult(stoi(get<0>(clip)));
				cout << "Multiplier changed to " << affineCypher.getMult() << endl;
			}
			catch(...)
			{
				cout << "Invalid value given. Multiplier must be an integer." << endl;
			}
			return get<1>(clip);
		});
	affineEnvironment.addCallSign("Change shift.", {"shift"},
		[&affineCypher](string input) -> string
		{
			auto clip = clipOne(input);
			try
			{
				affineCypher.setShift(stoi(get<0>(clip)));
				cout << "Shift changed to " << affineCypher.getShift() << endl;
			}
			catch(...)
			{
				cout << "Invalid value given. Shift must be an integer." << endl;
			}
			return get<1>(clip);
		});

	UserEnvironment groundEnvironment("Ground Environment", "Base environment, \
serves as the entry point of the program and a place to choose which \
encryption environment you would like to enter.");
	groundEnvironment.addCallSign("Affine Cypher Environment.", {"affine", "affine_cypher"},
		[&affineCypher, &affineEnvironment](string input) -> string
		{
			return enterAffineCypherEnvironment(affineCypher, affineEnvironment, input);
		});
		// {{"Specify the alphabet you would like to use for the cypher.", "alphabet", "alpha", "alph"},
		// 	{"Specify the multiplier. Should fit 0 <= n < length of alphabet.", "multiplier", "mult"},
		// 	{"Specify the shift.", "shift"}});
	groundEnvironment.enterEnvironment();
	return 0;
}
