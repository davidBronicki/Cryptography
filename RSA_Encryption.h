
class RSA_Encryptor
{
	typedef unsigned long long ull;
	typedef unsigned int ul;
	typedef unsigned short us;

	us prime1, prime2;
	ul modularBase;

	ul exponentBase;
	ul exponent;
	ul inverse;
public:
	struct publicData
	{
		ul modularBase;
		ul exponent;
	};

	struct privateData
	{
		us prime1;
		us prime2;
		ul exponentBase;
		ul inverse;
	};

	RSA_Encryptor();
	RSA_Encryptor(us inPrime1, us inPrime2, ul exponent);
	void setPrime1(us prime);
	void setPrime2(us prime);
	void setExponent(ul inExponent);
	publicData publish();
	privateData getPrivateData();

	ul encrypt(ul trueData);
	ul decrypt(ul encryptedData);
};
