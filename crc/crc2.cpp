#include <bits/stdc++.h>
using namespace std;
#define D 3 

int position(bitset<15>b)
{
	int pos=0;
	for (int i = 0; i < b.size(); ++i)
	{
		if (b.test(i))
		{
			pos=i;
		}
	}
	return pos;
}
int position2(bitset<4>b)
{
	int pos=0;
	for (int i = 0; i < b.size(); ++i)
	{
		if (b.test(i))
		{
			pos=i;
		}
	}
	return pos;
}
int main()
{
	string msg;
	cout<<"ENTER THE MESSAGE IN BITS";
	cin>>msg;
	string acc_polynomial="1101";
	int degree = D;
	bitset<15>b1(msg);
	bitset<4>b2(acc_polynomial);
	string pat;
	for (int i = 0; i < D; ++i)
	{
		pat+="0";
	}
    bitset<15> pat2(pat);
    b1 <<= 3;
    b1 |= pat2;
    bitset<15>b11(b1);
    cout<<b1<<endl;
    cout<<b2<<endl;
    int p1,p2;
    do
    {
	  	p1=position(b1);
	  	p2=position2(b2);
	  	cout<<p1<<endl<<p2<<endl;
	   for (int i = 0; i < b2.size(); ++i)
	   {
	   		b1[p1-i]=b1[p1-i]^b2[p2-i];
	   }
	   cout<<b1<<endl;
   }while(p1>p2);
   b11 |= b1;
   cout<<b11<<endl;
}