#pragma once
#include<vector>
#include<string>
#include<cassert>
#include<iostream>
#include <algorithm>
using std::ostream;
using std::vector;
using std::string;

class BigInt{

public:
	typedef unsigned long base_t;
	static int base_char;
	static int base;
	static int basebitnum;
	static int basebitchar;
	static int basebit;
private:
	friend class Rsa;
	friend void test();
public:	
	friend BigInt operator + (const BigInt& a,const BigInt& b);
	friend BigInt operator - (const BigInt& a,const BigInt& b);
	friend BigInt operator * (const BigInt& a,const BigInt& b);	
	friend BigInt operator / (const BigInt& a,const BigInt& b);	
	friend BigInt operator % (const BigInt& a,const BigInt& b);	
	friend bool operator < (const BigInt& a,const BigInt& b);
	friend bool operator <= (const BigInt& a,const BigInt& b);
	friend bool operator == (const BigInt& a,const BigInt& b);
	friend bool operator != (const BigInt& a,const BigInt& b){return !(a==b);}	
	//重载版本	
	friend BigInt operator + (const BigInt& a,const long b){BigInt t(b);return a+t;}	
	friend BigInt operator - (const BigInt& a,const long b){BigInt t(b);return a-t;}	
	friend BigInt operator * (const BigInt& a,const long b){BigInt t(b);return a*t;}	
	friend BigInt operator / (const BigInt& a,const long b){BigInt t(b);return a/t;}	
	friend BigInt operator % (const BigInt& a,const long b){BigInt t(b);return a%t;}	
	friend bool operator < (const BigInt& a,const long b){BigInt t(b);return a<t;}	
	friend bool operator <= (const BigInt& a,const  long b){BigInt t(b);return a<=t;}	
	friend bool operator == (const BigInt& a,const long b){BigInt t(b);return a==t;}	
	friend bool operator != (const BigInt& a,const long b){BigInt t(b);return !(a==t);};	
	//	
	friend ostream& operator << (ostream& out,const BigInt& a); 	
	friend BigInt operator <<(const BigInt& a,unsigned int n);
public:
	typedef vector<base_t> data_t;	

	typedef const vector<base_t> const_data_t;	
	BigInt& trim()	
	{		
		int count=0;		
		//检查不为0的元素的数量		
		for(data_t::reverse_iterator it=_data.rbegin();it!=_data.rend();++it)			
			if((*it)==0)		
				++count;
			else
				break;
		if(count==_data.size())//只有零的情况保留			
			--count;
		for(int i=0;i<count;++i)
			_data.pop_back();
		return *this;
	}	
	friend class bit;
	class bit
	{	
	public:
		std::size_t size();
		bool at(std::size_t i);		
		bit(const BigInt& a);
	private:
		vector<base_t> _bitvec;
		std::size_t _size;
	};		
	//大数幂模运算	
	BigInt moden(const BigInt& exp,const BigInt& p)const;
	/* 用扩展的欧几里得算法求乘法逆元 */	
	BigInt extendEuclid(const BigInt& m);
public:	
	BigInt():_isnegative(false){_data.push_back(0);}

	BigInt(const string& num):_data(),_isnegative(false){copyFromHexString(num);trim();}

	BigInt(const long n):_isnegative(false){copyFromLong(n);}

	BigInt(const_data_t data):_data(data),_isnegative(false){trim();}	

	BigInt& operator =(string s)
	{
		_data.clear();
		_isnegative=false;
		copyFromHexString(s);
		trim();
		return *this;
	}		
	BigInt(const BigInt& a,bool isnegative):_data(a._data),_isnegative(isnegative){}		
	BigInt& operator =(const long n)	
	{
		_data.clear();
		copyFromLong(n);
		return *this;
	}
public:	
	static BigInt Zero;
	static BigInt One;
	static BigInt Two;
private:
	bool smallThan(const BigInt& a)const;//判断绝对值是否小于
	bool smallOrEquals(const BigInt& a)const;//判断绝对值是否小于相等
	bool equals(const BigInt& a)const;//判断绝对值是否相等

	BigInt& leftShift(const unsigned int n);
	BigInt& rightShift(const unsigned int n);
	BigInt& add(const BigInt& b);

	BigInt& sub(const BigInt& b);
	
	void copyFromHexString(const string& s)	
	{
		string str(s);
		if(str.length() && str.at(0)=='-')		
		{
			if(str.length()>1)
				_isnegative=true;
			str=str.substr(1);
		}
		int count=(8-(str.length()%8))%8;
		std::string temp;

		for(int i=0;i<count;++i)
			temp.push_back(0);
			
		str=temp+str;

		for(int i=0;i<str.length();i+=BigInt::base_char)	
		{
			base_t sum=0;
			for(int j=0;j<base_char;++j)
			{
				char ch=str[i+j];
								
				ch=hex2Uchar(ch);
				sum=((sum<<4)|(ch));
			}
			_data.push_back(sum);
		}
		reverse(_data.begin(),_data.end());
	}
	char hex2Uchar(char ch)
	{
		static char table[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
		if(isdigit(ch))
			ch-='0';
		else if(islower(ch))
			ch-='a'-10;
		else if(isupper(ch))
			ch-='A'-10;

		return table[ch];	
	}

	void copyFromLong(const long n)	
	{
		long a=n;		
		if(a<0)
		{
			_isnegative=true;
			a=-a;
		}
		do
		{
			BigInt::base_t ch=(a&(BigInt::base));	
			_data.push_back(ch);
			a=a>>(BigInt::basebitnum);
		}while(a);
	}		
	static void div(const BigInt& a,const BigInt& b,BigInt& result,BigInt& ca);
private:	
	vector<base_t> _data;
	//数据存储	
	bool _isnegative;
};
