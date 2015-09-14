#include "gtest/gtest.h"
#include "../RSA/TinyInt.h"
#include "../RSA/RSArealization.h"
#include<ctime>
#define MAX_TEST 1000000
unsigned long long factorial (int n) {return n>1?n*factorial(n-1):1;}

TEST(TestPlus, TinyIntPlusTest)
{
	srand(time(NULL));
	for(int i = 0; i < MAX_TEST; ++i)
	{
		int tmp1 = rand()-10000;
		int tmp2 = rand()-10000;
		tinyInt a, b;
		b.set(tmp2); a.set(tmp1);
		tinyInt c = a+b;
		tinyInt d;
		d.set(tmp1+tmp2);
		if (c !=d ) std::cout << tmp1 << ' '<< tmp2 <<" Expected: " << tmp1+tmp2 << " Result: " << c << std::endl; 
		ASSERT_EQ(d, c);
	}
}
TEST(TestMinus, TinyIntMinusTest)
{
	srand(time(NULL));
	for(int i = 0; i < MAX_TEST; ++i)
	{
		int tmp1 = rand()-10000;
		int tmp2 = rand()-10000;
		tinyInt a, b;
		b.set(tmp2); a.set(tmp1);
		tinyInt c = a-b;
		tinyInt d;
		d.set(tmp1-tmp2);
		if (c !=d ) std::cout << tmp1 << ' '<< tmp2 <<" Expected: " << tmp1-tmp2 << " Result: " << c << std::endl; 
		ASSERT_EQ(d, c);
	}
}
TEST(TestMulti, TinyIntMultiTest)
{
	srand(time(NULL));
	for(int i = 0; i < MAX_TEST; ++i)
	{
		int tmp1 = rand()-10000;
		int tmp2 = rand()-10000;
		tinyInt a, b;
		b.set(tmp2); a.set(tmp1);
		tinyInt c = a*b;
		tinyInt d;
		d.set(tmp1*tmp2);
		if (c !=d ) std::cout << tmp1 << ' '<< tmp2 <<" Expected: " << tmp1*tmp2 << " Result: " << c << std::endl; 
		ASSERT_EQ(d, c);
	}
}
TEST(TestDivide, TinyIntDivideTest)
{
	srand(time(NULL));
	for(int i = 0; i < MAX_TEST; ++i)
	{
		int tmp1 = rand()-10000;
		int tmp2 = rand()-10000;
		while (tmp2 == 0) tmp2 = rand();
		tinyInt a, b;
		b.set(tmp2); a.set(tmp1);
		tinyInt c = a/b;
		tinyInt d;
		d.set(tmp1/tmp2);
		if (c!=d) std::cout << tmp1 << ' '<< tmp2 <<" Expected: " << d << " Result: " << c << std::endl; 
		ASSERT_EQ(d, c);
	}
}
TEST(Modul, tinyIntModulTest)
{
	srand(time(NULL));
	for(int i = 0; i < MAX_TEST; ++i)
	{
		int tmp1 = rand()-10000;
		int tmp2 = rand()-10000;
		while (tmp2 == 0) tmp2 = rand();
		tinyInt a, b;
		b.set(tmp2); a.set(tmp1);
		tinyInt c = a%b;
		tinyInt d;
		d.set(tmp1%tmp2);
		if (c!=d) std::cout << tmp1 << ' '<< tmp2 <<" Expected: " << d << " Result: " << c << std::endl; 
		ASSERT_EQ(d, c);
	}
}
TEST(PowModTest,tinyIntPowModTest)
{
	srand((unsigned)time(NULL));
	for(int i = 0; i < MAX_TEST; ++i)
	{
		int tmp1 = rand()%10;
		int tmp2 = rand()%5+1;
		int tmp4 = rand()%100;
		while (tmp4 == 0) tmp4 = rand()%100;
		int tmp3 = (int)(pow((double)tmp1,(double)tmp2))%tmp4;
		tinyInt a , b, e;
		a.set(tmp1); b.set(tmp2); e.set(tmp4);
		tinyInt c = PowMod(a,b, e);
		tinyInt d;
		d.set(tmp3);
		if (c !=d ) std::cout << tmp1 << ' '<< tmp2 << ' ' << tmp4 <<" Expected: " << tmp3 << " Result: " << c << std::endl; 
		ASSERT_EQ(d, c);
	}
}
TEST(RSAtest, RsaFinalTest)
{
	ofstream outFile("Keys.txt");
	RSA a;
	keys privateKeys;
	keys publicKeys;
	a.createKeys(publicKeys, privateKeys);
	a.EncryptFile("input.txt", "output.txt", publicKeys);
	a.DecryptFile("output.txt", "Decrypt.txt", privateKeys);
	outFile << "Public Keys: ";
	outFile << publicKeys << "Private Keys: ";
	outFile <<privateKeys;

	ifstream checkOut1("input.txt");
	ifstream checkOut2("Decrypt.txt");
	while (checkOut1.peek() != EOF || checkOut2.peek() != EOF)
	{
		char x1, x2;
		checkOut1.get(x1);
		checkOut2.get(x2);
		if (x1 != x2) cout << "Error" << ". In beginning " << x1 << " at ending " << x2 <<endl;
		ASSERT_EQ(x1,x2);
	}
}
int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}