#ifndef __RSA__
#define __RSA__
#include "TinyInt.h"
#include <fstream>
#include <string>
#include<iostream>
#define KeyLength 8
struct keys
{
	tinyInt firstKey;
	tinyInt secondKey;
};
std::ofstream& operator <<(std::ofstream& out,const keys& a)
{
	out << a.firstKey << ' ' << a.secondKey << ' ';
	return out;
}
std::ifstream& operator>>(std::ifstream& in, keys& a)
{
	in >> a.firstKey >> a.secondKey;
	return in;
}
class RSA
{
	void EuclidAlhorithm(tinyInt a, tinyInt b, tinyInt& y)
	{
		tinyInt a11, a12, a21, a22;
		a11.set(1); a12.set(0); a21.set(0); a22.set(1);
		tinyInt balance, quotient;
		balance.set(0); quotient.set(0);
		tinyInt A11, A12, A21, A22;
		A11.set(0); A12.set(0); A21.set(0); A22.set(0);

		tinyInt zero; zero.set(0);
		while (zero < b )
		{
			balance = a%b;
			quotient = a /b;
		
			if ( balance == zero) break;
			A11 = a12;
			A12 = a11 - a12 * (quotient);
			A21 = a22;
			A22 = a21 - a22 * (quotient);

			a11 = A11;
			a12 = A12;
			a21 = A21;
			a22 = A22;

			a = b;
			b = balance;
		}
		y = a22;
	}
public:
	void createKeys(keys& keysPublic, keys& keysPrivate)
	{
		cout << "Keys Generating" <<endl;
		srand((unsigned)time(NULL));
		tinyInt one;
		one.set(1);
		tinyInt p,q;
		p.Rand(KeyLength);
		q.Rand(KeyLength);
		while (!p.PrimeTest()) p.Rand(KeyLength);

		while (!q.PrimeTest() || p == q) q.Rand(KeyLength);
		
		tinyInt n = p*q;

		tinyInt Phi = (p - one)*(q-one);
		
		tinyInt e;
		tinyInt d;
		tinyInt zero;
		zero.set(0);
		do
		{
			do {
				e.Rand(KeyLength);
			}while ( Phi.gcd(e) != one || e == q); 
			EuclidAlhorithm(Phi, e, d);
		}while (d < zero);
		keysPublic.firstKey = e;
		keysPublic.secondKey = n;

		keysPrivate.firstKey= d;
		keysPrivate.secondKey = n;
		cout << "Keys are generated" << endl;
	}
	void encrypt(std::string data, keys& publicKey, tinyInt& result)
	{
		tinyInt tmp;
		for (int i = 0; i< data.length(); ++i)
		{
			unsigned char c = data[i];
			tmp.push_front((int)c / 100 +'0');
			tmp.push_front((int)c%100 / 10 +'0');
			tmp.push_front((int)c%10 + '0');
		}
		result = PowMod(tmp, publicKey.firstKey, publicKey.secondKey);
	}
	void decrypt(keys& privateKey,tinyInt& data, std::string& result)
	{
		tinyInt tmp = PowMod(data, privateKey.firstKey, privateKey.secondKey);
		for (int i = 0; i < tmp.getLen(); i+=3)
		{
			unsigned char c;
			if (i+2 < tmp.getLen())
				c = (tmp[i] -'0') + (tmp[i+1] - '0') * 10 + (tmp[i+2] - '0') * 100;
			else if (i+1 < tmp.getLen())
				c = (tmp[i] -'0') + (tmp[i+1] - '0') * 10;
			else c = tmp[i] - '0';
			result += c;
		}
		reverse(result.begin(), result.end());
	}
	void EncryptFile(const char* instr, const char* outstr, keys& publicKey)
	{
		ifstream in(instr);
		ofstream out(outstr);
		tinyInt tmp;
		cout << "Encrypting..." << endl;
		while (in.peek() != EOF)
		{
			std::string buffer;
			unsigned char c;
			for (int i = 0; i < publicKey.secondKey.getLen() / 4; ++i)
			{
				if (in.peek() != EOF)
				{
					c = in.get();
					buffer += c;
				}
			}
			encrypt(buffer, publicKey, tmp);
			buffer.clear();
			out << tmp << ' ';
		}
		cout << "Encrypt complited" << endl;
		in.close();
		out.close();
	}
	void DecryptFile(const char* instr, const char* outstr, keys& privateKey)
	{
		std::string buffer;
		tinyInt tmp;
		ifstream in(instr);
		ofstream out(outstr);
		cout << "Decripting..." <<endl;
		while (in >> tmp)
		{
			decrypt(privateKey, tmp, buffer);
			out << buffer;
			buffer.clear();
			tmp.clear();
		}
		cout << "Decrypt complited" << endl;
		in.close();
		out.close();
	}
};
#endif