#include "stdafx.h"
#include<iostream>
#include <fstream>
#include<string>
#include "TinyInt.h"
#include "RSArealization.h"
using namespace std;
int main()
{
	ofstream out("Keys.txt");
	tinyInt a1;
	tinyInt c1;
	c1.set("123");
	RSA a;
	keys publickeys;
	keys privatekeys;
	a.createKeys(publickeys, privatekeys);
	out << publickeys << privatekeys;

	a.EncryptFile("input.txt", "output.txt", publickeys);
	a.DecryptFile("output.txt", "Decrypt.txt", privatekeys);
	system("pause");
	return 0;
}

