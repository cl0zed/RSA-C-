#ifndef __TINYINT__
#define __TINYINT__
#include<iostream>
#include<string>
#include<cmath>
#include<fstream>
#include<ctime>
using namespace std;
class tinyInt
{
	int len;
	string digit;
	bool isNegative;
public:
	/*Конструктор*/
	tinyInt():len(0), isNegative(false){}
	void set(const char* s)
	{
		if (s[0] == '-') 
		{
			int tmp = 1;
			while (s[tmp] == '0') ++tmp;
			len = strlen(s) - tmp;
			if (tmp == strlen(s)) isNegative = false; else isNegative = true;
			if (len <= 1) 
			{
				len = 1;
				digit.push_back(s[strlen(s) - 1]);
			}else
			{
				for (int i = strlen(s)-1; i >0; --i)
				digit.push_back(s[i]);
			}
		} else
		{
			isNegative = false;
			int tmp = 0;
			while (s[tmp] == '0') ++tmp;
			len = strlen(s) - tmp;
			if (len == 0)
			{
				digit += '0';
				len = 1;
			}else
			{
				for (int i = strlen(s)-1; i>=0; --i)
				digit.push_back(s[i]);
			}
		}
	}
	void set(int x)
	{
		if (x < 0) isNegative = true;
		else isNegative = false;
		x = abs(x);
		len = 0;
		if (x == 0) 
		{
			digit.push_back('0');
			len = 1;
		}
		while (x > 0)
		{
			digit += (char)(x%10 + '0');
			x /= 10;
			++len;
		}
	}
	~tinyInt()
	{
		len = 0;
		digit.clear();
	}


	/*Возвращение значений*/
	const string getDigit() const{ return digit;}
	const int getLen() const{ return len;}
	const bool getSign() const{return isNegative;}

	/*Копирующий конструктор */
	tinyInt(const tinyInt& a)
	{
		isNegative = a.isNegative;
		len = a.len;
		for (int i = 0; i<len; ++i)
			digit += a.digit[i];
	}

	/*Присваивание*/
	tinyInt& operator =(const tinyInt& a)
	{
		if (this != &a)
		{
			isNegative = a.getSign();
			len = a.getLen();
			digit.erase(digit.begin(), digit.end());
			for (int i = 0; i< len; ++i)
				digit += a.digit[i];
		}
		return *this;
	}


	/*Вспомогательные функции*/
	tinyInt& clearFirstsNulls()
	{
		if (len == 1 && digit[0] == '0')
		{
			digit.erase(digit.begin());
			len = 0;
		}
		else while (digit[len - 1] == '0')
				{
					digit.erase(len-1);
					--len;
				}
		return *this;
	}
	tinyInt toBinary()
	{
		tinyInt tmp1, tmp2;
		tmp1.set(0);
		tmp2.set(2);
		tinyInt result;
		while (tmp1 < *this)
		{
			tinyInt tmp3 = (*this)%tmp2;
			result.digit.push_back(tmp3.digit[0]);
			++result.len;
			(*this)= (*this)/tmp2;
		}
		return result;
	}
	tinyInt push_front(char c)
	{
		++len;
		string tmp;
		tmp+=c;
		tmp+= digit;
		digit = tmp;
		return *this;
	}
	bool PrimeTest();
	void Rand(int x)
	{
		digit.clear();
		len = 0;
		while (len < x)
		{
			push_front(rand()%10 + '0');
		}
		if (digit[len - 1] == '0') digit[len -1] = rand()%9 + '1';
	}
	tinyInt gcd(tinyInt a)
	{
		tinyInt tmp(*this);
		tinyInt remainder;
		tinyInt zero, one;
		zero.set(0);
		one.set(1);
		remainder.set(0);
		while (a != zero)
		{
			remainder = tmp % a;
			tmp = a;
			a = remainder;
		}
		return tmp;
	}
	char operator[] (int i) { return digit[i];}
	void clear()
	{
		digit.clear();
		len = 0;
	}
	
	/*функции сравнения*/
	bool operator < (tinyInt& a)const
	{
		if(isNegative == true && a.isNegative == false) return true;
		if(isNegative == false && a.isNegative == true) return false;
		if ((!isNegative) && (!a.isNegative))
		{
			if (len < a.len) return true; 
			if (len > a.len) return false;
			for (int i = len - 1; i >= 0; --i)
			{
				if (digit[i] < a.digit[i]) return true;
				if (digit[i] > a.digit[i]) return false;
			}
			return false;
		}else
		{
			if (len < a.len) return false;
			if (len > a.len) return true;
			for (int i = len -1 ; i>= 0; --i)
			{
				if (digit[i] < a.digit[i]) return false;
				if (digit[i] > a.digit[i]) return true;
			}
			return false; 
		}
	}
	bool operator <= (tinyInt& a)const
	{
		if (*this < a || *this == a) return true;
		return false;
	}
	bool operator != (tinyInt& a)const
	{
		if (len != a.len) return true;
		for (int i = 0; i< len; ++i)
			if (digit[i] != a.digit[i]) return true;
		return false;
	}
	bool operator == (const tinyInt& a) const
	{
		if (len != a.len || isNegative != a.isNegative) return false;
		for (int i = 0; i<len; ++i)
			if (digit[i] != a.digit[i]) return false;
		return true;
	}
	
	
	/*вычислительные операции*/
	friend tinyInt operator+(tinyInt, tinyInt&);
	friend tinyInt operator-(tinyInt, tinyInt);
	tinyInt operator-()
	{
		tinyInt tmp;
		tmp.set(0);
		if (*this != tmp) isNegative = !isNegative;
		return *this;
	}
	friend tinyInt operator*(const tinyInt&, const tinyInt&);
	friend tinyInt operator/(tinyInt, tinyInt);
	friend tinyInt operator %(tinyInt,const tinyInt&);
	friend tinyInt Pow(tinyInt, tinyInt);
	friend tinyInt PowMod(tinyInt, tinyInt, tinyInt&);
};
ostream& operator << (ostream& out,const tinyInt& a)
{
	string tmp = a.getDigit();
	if (a.getSign() == true) out << '-';
	for (int i = a.getLen() - 1; i >= 0; --i)
			out << tmp[i];
	return out;
}
ofstream& operator <<(ofstream& out, const tinyInt& a)
{
	string tmp = a.getDigit();
	reverse(tmp.begin(), tmp.end());
	out << tmp;
	return out;
}
ifstream& operator >>(ifstream& in, tinyInt& a)
{
	char c = in.get();
	while ( c >='0' && c<='9')
	{
		a.push_front(c);
		c = in.get();
	}
	return in;
}
tinyInt operator+ (tinyInt first, tinyInt& second)
{
	tinyInt zero;
	zero.set(0);
	if (first == zero) return second;
	if (second == zero) return first;
	if ( (first.isNegative) && (!second.isNegative)) return second - (-first);
	if ((!first.isNegative) && (second.isNegative)) return first - (-second);
	while (first.len < second.len)
	{
		first.digit.push_back('0');
		++first.len;
	}
	first.digit.push_back('0');
	++first.len;
	for(int i = 0; i<second.len; ++i)
	{
		first.digit[i] += second.digit[i] - '0';
		int k = i;
		while (first.digit[k] >= '9'+1 && k < first.len)
		{
			first.digit[k+1] += 1;
			first.digit[k] -= 10;
			++k;
		}
	}
	first.clearFirstsNulls();
	return first;
}
tinyInt operator- (tinyInt first, tinyInt second)
{
	tinyInt zero;
	zero.set(0);
	if (first == second) return zero;
	if (first.isNegative != second.isNegative) return first + (-second);
	if ((first.isNegative) &&  (second.isNegative)) return -second - (-first);
	if (first < second) return -(second - first);
	while (first.len < second.len)
	{
		first.digit.push_back('0');
		++first.len;
	}
	while (second.len < first.len)
	{
		second.digit.push_back('0');
		++second.len;
	}
	for(int i = 0; i < first.len; ++i)
	{
		int tmp = i+1;
		if(first.digit[i] < second.digit[i])
		{
			while (first.digit[tmp] == '0')
				++tmp;
			while (tmp != i )
			{
				first.digit[tmp--] -= 1;
				first.digit[tmp] += 10;
			}
		}
		first.digit[i] -= second.digit[i]-'0';
	}
	first.clearFirstsNulls();
	if (first.len == 0) first.digit.push_back('0');
	return first;
}
tinyInt operator* (const tinyInt& first,const tinyInt& second)
{
	tinyInt zero;
	zero.set(0);
	if (second == zero || first == zero) return zero;
	tinyInt result;
	while (result.len < first.len + second.len)
	{
		++result.len;
		result.digit.push_back(0);
	}
	for (int j = 0; j< first.len; ++j)
	{
		int k = j;
		for (int i =0; i < second.len; ++i)
			result.digit[k++] += (first.digit[j]-'0') * (second.digit[i]-'0');
		char overload = 0;
		for (int i = 0; i<result.len ;++i)
		{
			result.digit[i] += overload;
			overload = result.digit[i] / 10;
			result.digit[i] = result.digit[i] % 10;
		}
		if (overload != 0) result.digit.push_back(overload);
	}
	result.clearFirstsNulls();
	if (first.isNegative == second.isNegative) result.isNegative = false; else result.isNegative = true;
	for (int i = 0; i < result.len; ++i)
		result.digit[i] += '0';
	result.clearFirstsNulls();
	return result;
}
tinyInt operator/ (tinyInt first, tinyInt second)
{
	tinyInt result;
	tinyInt zero;
	zero.set(0);
	if (first.isNegative == second.isNegative) result.isNegative = false; else result.isNegative = true;
	first.isNegative = false;
	second.isNegative = false;

	if (first < second) return zero;
	if (second == zero) throw "Divide by zero";

	tinyInt tmp;
	int j = first.len - 1;

	while (tmp < second)
		tmp.push_front(first.digit[j--]);

	while (j >= -1)
	{
		char toResult = 0;
		while (second <= tmp)
		{
			tmp = tmp - second;
			++toResult;
		}
		result.push_front('0' + toResult);
		tmp.clearFirstsNulls();
		if (j>=0) tmp.push_front(first.digit[j--]); else --j;
	}
	result.clearFirstsNulls();
	return result;
}
tinyInt operator%(tinyInt first,const tinyInt& second)
{
	tinyInt tmp = first / second;
	tmp = tmp*second;
	return first - tmp;

}
tinyInt Pow(tinyInt first, tinyInt second)
{
	tinyInt zero;
	zero.set(0);
	if (second == zero) return zero;
	second = second.toBinary();
	tinyInt result;
	result.set(1);
	for (int i = second.len - 1; i>=0; --i)
	{
		if (i == 0)
			if(second.digit[i] != '0')
			{
				result = result*first;
				return result;
			} else return result;
		if (second.digit[i] == '0') result = result*result;else result = (result*first)*(result*first);
	}
}
tinyInt PowMod(tinyInt first, tinyInt second, tinyInt& mod)
{
	//second = second.toBinary();
	tinyInt tmp;
	tmp.set(1);
	tinyInt zero;
	zero.set(0);
	tinyInt two;
	two.set(2);
	tinyInt one;
	one.set(1);
	if (second == zero && mod == one) return zero;
	while (second != zero)
	{
		if (zero == (second % two))
		{
			second = second / two;
			first = (first*first)%mod;
		}
		else
		{
			second = second - one;
			tmp = (tmp * first) % mod;
		}
	}
	return tmp;
}
bool tinyInt::PrimeTest()
{
	tinyInt first(*this);
	int rounds = 20;
	tinyInt zero;
	zero.set(0);
	tinyInt one;
	one.set(1);
	tinyInt two;
	two.set(2);
	tinyInt four;
	four.set(4);
	if ( (first % two) != zero && first < one)
		return false;
	tinyInt tmp(first);
	int s = 0;
	while ((tmp - one) % two != one)
	{
		tmp = tmp / two;
		tmp = tmp+one;
		++s;
	}
	tmp = tmp - one;
	for (int i = 0; i<rounds; ++i)
	{
		bool isReturned = false;
		srand((unsigned)time(NULL));
		tinyInt a;
		tinyInt toCreate;
		toCreate.set(rand());
		if (first.len == 1 && first.digit[0] == 4) return false;
		a = toCreate%(first - four) + two;
		tinyInt x = PowMod(a, tmp, first);
		if (x == one || x == first - one) continue;
		for (int j = 0; j < s-1; ++j)
		{
			x = PowMod(x,two,first);
			if (x == one) return false;
			if (x == first - one) 
			{
				isReturned = true;
				break;
			}
		}
		if (isReturned) continue; else return false;
	}
	return true;
}
#endif