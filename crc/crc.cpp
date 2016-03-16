#include <bits/stdc++.h>
#include <string.h>
#include <math.h>
using namespace std;

int main()
{

		string msg;
	cout<<"ENTER THE MESSAGE IN HEX";
	cin>>msg;
		bitset<20>binary;
	int m= msg.length();
	int a[m];
	for (int i = 0; i < m; ++i)
	{
		if(msg[i]>64)
		{
			a[i]=msg[i]-55;
			//cout<<a<<endl;
			binary<<=4;
			binary |=a[i];

		}
		else
		{
			a[i]=msg[i]-48;
			//cout<<a<<endl;
			binary<<=4;
			binary |=a[i];
		}

	}

	cout<<binary<<endl;
	m= (m*4);
	cout<<m<<endl;
	int r=0;
	while(pow(2,r)<(m+r+1))
	{
		r++;
	}
	cout<<r<<endl;
	bitset<20>b2;
	//bitset<20>b1(msg);
	//cout<<b1<<endl;
	int i,i2,j=0,k=7;
	for (i=m+r-1,i2=0; i > 0; i--,i2++)
	{
		if((pow(2,j)-1)==i2)
		{
			b2[i]=false;
			j++;
		}
		else
		{
			b2[i] = binary[k];
			k--;
		}
	}
	cout<<b2<<endl;

	int pos[r];
	for (i = 0; i < r; ++i)
	{
		pos[i]=0;
	}
	//memset(pos,0,r);
	for ( i = 1,j=(m+r-1); i <= (m+r) ; ++i,j--)
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

	for (i = 0; i < r; ++i)
	{
		cout<<pos[i]<<" " ;
	}
	cout<<endl;
	j=0;

	for (i=(m+r-1),i2=0; i > 0; i--,i2++)
	{
		//cout<<i<<endl;
		if((pow(2,j)-1)==i2)
		{
			cout<<i<<endl;
			b2.set(i,pos[j]);
			j++;
		}
	}
	cout<<b2<<endl;
	/*string msg;
	cout<<"ENTER THE MESSAGE IN HEX";
	cin>>msg;
	bitset<20>binary;
	int m= msg.length();
	int a[m];
	for (int i = 0; i < m; ++i)
	{
		if(msg[i]>64)
		{
			a[i]=msg[i]-55;
			//cout<<a<<endl;
			binary<<=4;
			binary |=a[i];

		}
		else
		{
			a[i]=msg[i]-48;
			//cout<<a<<endl;
			binary<<=4;
			binary |=a[i];
		}
		cout<<binary<<endl;

	}
	cout<<binary<<endl;*/

	/*string msg;
	cout<<"ENTER THE MESSAGE IN BITS";
	cin>>msg;
	bitset<10>message(msg);
	for (int i = 0; i < message.size(); ++i)
	{
		cout<<message[i]<<'\n';
	}
	*/
	/* std::bitset<16> dest;
    std::string pattern_str = "1001";
    std::bitset<16> pattern(pattern_str);
 
    for (size_t i = 0, ie = dest.size()/pattern_str.size(); i != ie; ++i) {
        dest <<= pattern_str.size();
        dest |= pattern;
        std::cout << dest << '\n';
    }
    
    std::string pat= "1111";
     std::bitset<16> pat2(pat);
    dest <<= 4;
    dest |= pat2;

    std::cout << dest << '\n';*/

    
}