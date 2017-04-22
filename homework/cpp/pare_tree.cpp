#include<iostream>
#include<string>
using namespace std;

void out_put(string s)
{
	string temp = "";

	unsigned int l = s.length();
	if(l)
	{
		s = s.substr(1);
		s = s.substr(0,s.length()-1);
		unsigned int i = 0;
		if(s[0]!='('&&s[0]!=')')
		{
			cout<<s[0];
		}
		int num = 0;
		for(i=1;i<l;i++)
		{
			if(s[i]=='(')
			{
				num++;
				temp = temp+s[i];
				continue;
			}
			else if(s[i]==')')
			{
				num--;
				temp = temp+s[i];
				continue;
			}

			if(num==0)
			{
				if(s[i]!='('&&s[i]!=')')
				{
					cout<<s[i];
				}
			}
			else
			{
				temp=temp+s[i];
			}
		}
		out_put(temp);
	}
}
void remove_all(string& s,char c)
{
	string temp = "";
	unsigned int l = s.length();
	unsigned int i = 0;
	for(i=0;i<l;i++)
	{
		if(s[i]==c)
		{
			s.erase(i,1);
			i--;
			l--;
		}
	}
	cout<<s<<endl;
}
int main()
{
	string s;
	cin>>s;
	remove_all(s,',');
	out_put(s);
	cout<<endl;

	return 0;
}
