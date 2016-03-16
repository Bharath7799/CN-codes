#include <bits/stdc++.h>
#include <string.h>
#include <math.h>
using namespace std;

int main()
{
	string msg;
	cout<<"ENTER THE MESSAGE IN BITS";
	cin>>msg;
	int m= msg.length();
	cout<<m<<endl;
	int r=0;
	while(pow(2,r)<(m+r+1))
	{
		r++;
	}
	cout<<r<<endl;
	bitset<12>b2;
	bitset<8>b1(msg);
	cout<<b1<<endl;
	int i,i2,j=0,k=7;
	for (i=11,i2=0; i > 0; i--,i2++)
	{
		if((pow(2,j)-1)==i2)
		{
			b2[i]=false;
			j++;
		}
		else
		{
			b2[i] = b1[k];
			k--;
		}
	}
	cout<<b2<<endl;

	int pos[4]={0,0,0,0};
	for ( i = 1,j=11; i <= 12 ; ++i,j--)
	{
		int t=i,p=0;
		//cout<<t<<endl;
		while(t>0)
		{
			if(t&1)
			{
				if(b2.test(j))
				pos[p] ^= 1 ;
				p++;
				t>>=1;
			}
			else
			{
				p++;
				t>>=1;
		    }
		}
	}

	for (i = 0; i < 4; ++i)
	{
		cout<<pos[i]<<" " ;
	}
	cout<<endl;
	j=0;

	for (i=11,i2=0; i > 0; i--,i2++)
	{
		//cout<<i<<endl;
		if((pow(2,j)-1)==i2)
		{
			cout<<i<<endl;
			b2.set(i,pos[j]);
			j++;
		}
		else
		{
			//b2[i] = b1[k];
			//k--;
		}
	}
	cout<<b2<<endl;
}