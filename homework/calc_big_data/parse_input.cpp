#include<iostream>
#include<string>
using namespace std;

void parse_str(string str);
void parse_str_data(string &t,string &s1,string &s2, string &s3,string &s4,string &s5,string &s6);
void parse_str_data_part(string& t,string &s1,string &s2,string &s3);
int main()
{
	int i;
	string s;

	for(i=0;i<2;i++){
	getline(cin,s);
	s=s.substr(2);
	parse_str(s);}

	return 0;
}

void parse_str(string str)
{
	//cout<<"Begin parse_str "<<str<<endl;
	unsigned long i=0;
	int l=0;
	int b=0;
	string s1;
	string s2;
	string s3;
	string s4;
	string s5;
	string s6;
	string t;
	while(i<str.length())
	{
		s1="+";	
		s2="1";	
		s3="1";	
		s4="+";	
		s5="1";	
		s6="1";	
		b=0;
		l=i;

		while(b!=3&&i<str.length())
		{
			if(str[i]==' ')
			{
				b++;
			}
			i++;
		}

		if(b==3)
		{
			t=str.substr(l,i-l-1);
		}
		else 
		{
			t=str.substr(l,i-l);
		}

		//cout<<"t"<<t<<endl;
		parse_str_data(t,s1,s2,s3,s4,s5,s6);
		
		cout<<s1<<"%"<<s2<<"%"<<s3<<"%"<<s4<<"%"<<s5<<"%"<<s6<<endl;
	}
}

void parse_str_data(string &t,string &s1,string &s2, string &s3,string &s4,string &s5,string &s6)
{
	//cout<<"begin parse_str_data"<<endl;
	unsigned long i=0;
	int l=0;
	string t1;
	string t2;
	
	while(i<t.length())
	{
		if(t[i]==' ')
		{
			t1=t.substr(0,i);
			t2=t.substr(i+3);
			parse_str_data_part(t1,s1,s2,s3);
			parse_str_data_part(t2,s4,s5,s6);
			break;
		}
		i++;
	}
}

void parse_str_data_part(string& t,string &s1,string &s2,string &s3)
{
	//cout<<"begin parse_str_data_part"<<endl;
	if(t[0]=='-'||t[0]=='+')
	{
		s1=t[0];
		t=t.substr(1);
	}

	unsigned long i=0;
	while(t[i]!='/'&&i<t.length())
	{
		i++;
	}

	s2=t.substr(0,i);
	if(i<t.length())
	{
		s3=t.substr(i+1);
	}
}
