#include<iostream>
#include<ctime>
#include"BigInt.h"
#include"Rsa.h"
using std::cout;
using std::endl;
using std::cin;

void menu()
{//菜单显示函数
	cout<<"==========Welcome to use RSA encoder=========="<<endl;
	cout<<"               e.encrypt 加密              "<<endl;
	cout<<"               d.decrypt 解密              "<<endl;
	cout<<"               s.setkey 重置               "<<endl;
	cout<<"               p.print 显示               "<<endl;
	cout<<"               q.quit 退出                 "<<endl;
	cout<<"input your choice:"<<endl;
}

bool islegal(const string& str)
{//判断输入是否合法
	for(string::const_iterator it=str.begin();it!=str.end();++it)
		if(!isalnum(*it))//不是字母数字
			return false;
	return true;
}

bool decode(Rsa& rsa)
{//解密
	string str;
	do
	{
		cout<<">输入16进制数据:";
		cin>>str;
	}while(cin && str.length()<1);
	if(!cin || islegal(str)==false)
		return false;
	BigInt c(str);
	
	long t1=clock();
	BigInt m=rsa.decodeByPr(c);
	long t2=clock();
	cout<<"用时:"<<(t2-t1)<<"ms."<<endl;

	cout<<"密文:"<<c<<endl
		<<"明文:"<<m<<endl;
	return true;
}

bool encry(Rsa& rsa,BigInt& c)
{//加密
	string str;
	do
	{
		cout<<">输入16进制数据:";
		cin>>str;
	}while(cin && str.length()<1);
	if(!cin || islegal(str)==false)
		return false;
	BigInt m(str);

	c=rsa.encryptByPu(m);

	cout<<"明文:"<<m<<endl
		<<"密文:"<<c<<endl;
	return true;
}

void print(Rsa& rsa)
{//输出
	cout<<rsa<<endl;
}

void init(Rsa& rsa,int n)
{//初始化

	cout<<"初始化...."<<endl;
	long t1=clock();
	rsa.init(n);
	long t2=clock();
	cout<<"初始化完成."<<endl;
	cout<<"用时:"<<(t2-t1)/1000<<"s."<<endl;
}

int go()
{//控制函数
	char ch;
	string str;
	Rsa rsa;
	BigInt c,m;
	cout<<"输入位数:";
	int n;
	cin>>n;
	init(rsa,n/2);

	while(true)
	{
		menu();//菜单显示
		cout<<">";
		cin>>str;
		if(!cin)
			return 0;
		
		if(str.length()<1)
			cout<<"重新输入"<<endl;
		else
		{
			ch=str.at(0);
			switch(ch)
			{
			case 'e':
			case 'E':
				encry(rsa,c);//加密
				break;
			case 'd':
			case 'D':
				decode(rsa);//解密
				break;
			case 's':
			case 'S':
				go();//重新开始初始
				break;
			case 'p':
			case 'P':
				print(rsa);//输出公私钥信息
				break;
			case 'q':
			case 'Q':
				return 0;
			}
		}
	}
}


int main()
{
	go();
}