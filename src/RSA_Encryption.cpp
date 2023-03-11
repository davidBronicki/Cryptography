#include "RSA_Encryption.hpp"
#include "ModularUtils.hpp"

RSA_Encryptor::RSA_Encryptor()
:
	prime1(3), prime2(5),
	modularBase(15),
	exponentBase(8),
	exponent(1),
	inverse(1)
{}

RSA_Encryptor::RSA_Encryptor(us inPrime1, us inPrime2, ul inExponent)
:
	prime1(inPrime1), prime2(inPrime2),
	modularBase((ul)inPrime1 * (ul)inPrime2),
	exponentBase((ul)(inPrime1 - 1) * (ul)(inPrime2 - 1)),
	exponent(inExponent)
{
	ModularNumber temp((ull)exponentBase, (ull)exponent);
	inverse = (ull)(temp.inverse());
}

void RSA_Encryptor::setPrime1(us prime)
{
	ul newExponentBase = (ul)(prime - 1) * (ul)(prime2 - 1);
	ModularNumber temp((ull)newExponentBase, (ull)exponent);
	inverse = (ull)(temp.inverse());//done first so if an error is
	//thrown, the encryptor will still be in a valid state
	prime1 = prime;
	modularBase = (ul)prime1 * (ul)prime2;
	exponentBase = newExponentBase;
}

void RSA_Encryptor::setPrime2(us prime)
{
	ul newExponentBase = (ul)(prime1 - 1) * (ul)(prime - 1);
	ModularNumber temp((ull)newExponentBase, (ull)exponent);
	inverse = (ull)(temp.inverse());//done first so if an error is
	//thrown, the encryptor will still be in a valid state
	prime2 = prime;
	modularBase = (ul)prime1 * (ul)prime2;
	exponentBase = newExponentBase;
}

void RSA_Encryptor::setExponent(ul inExponent)
{
	ModularNumber temp((ull)exponentBase, (ull)inExponent);
	inverse = (ull)(temp.inverse());//done first so if an error is
	//thrown, the encryptor will still be in a valid state
	exponent = inExponent;
}

RSA_Encryptor::publicData RSA_Encryptor::publish()
{
	return publicData{modularBase, exponent};
}

RSA_Encryptor::privateData RSA_Encryptor::getPrivateData()
{
	return privateData{prime1, prime2, exponentBase, inverse};
}

RSA_Encryptor::ul RSA_Encryptor::encrypt(ul trueData)
{
	//uses only trueData and public information
	ModularNumber value((ull)modularBase, (ull)trueData);
	return (ull)(value.exponentiate(exponent));
}

RSA_Encryptor::ul RSA_Encryptor::decrypt(ul encryptedData)
{
	//uses private information
	ModularNumber value((ull)modularBase, (ull)encryptedData);
	return (ull)(value.exponentiate(inverse));
}

