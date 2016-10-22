#include<iostream>
#include<cstring>
using namespace std;

struct point
{
	string sign_coefficient;
	string sign_power;
	int* top_coefficient;
	int* bottom_coefficient;
	int* top_power;
	int* bottom_power;
	point* next;

	point(string s1="+",string s2="+",string tc="1",string bc="1",string tp="1",string bp="1",point* p=NULL);
	void str_int(int id,string& st);
};
point::point(string s1,string s2,string tc,string bc,string tp,string bp,point* p)
{
	sign_coefficient=s1;
	sign_power=s2;

	str_int(1,tc);
	str_int(2,bc);
	str_int(3,tp);
	str_int(4,bp);
	next=p;
}
void point::str_int(int id,string& st)
{
	int* te=new int[st.length()+1];//The first position save the length of this data;
	te[0]=st.length()+1;
	
	int i;
	for (i=1;i<te[0];i++)
	{
		te[i]=st[i-1]-'0';
	}

	switch(id)
	{
		case 1:top_coefficient=te;break;
		case 2:bottom_coefficient=te;break;
		case 3:top_power=te;break;
		case 4:bottom_power=te;break;
	}
}
class multi_data
{
	private:
		point *first;
	public:
		multi_data();
		void input(string s);
		void push(string sign_c,string sign_p,string s_ct,string s_cb,string s_pt,string s_pb);
		void parse_str_data(string& t,string &s1,string &s2,string &s3,string &s4,string &s5,string &s6);
		void parse_str_data_part(string &t,string &s1,string &s2,string& s3);
		point* pop();
		~multi_data();
};
multi_data::multi_data()
{
	first = new point();
}
void multi_data::parse_str_data_part(string &t,string &s1,string &s2,string& s3)
{
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

void multi_data::parse_str_data(string& t,string &s1,string &s2,string &s3,string &s4,string &s5,string &s6)
{
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
	}
}
void multi_data::push(string sign_c,string sign_p,string s_ct,string s_cb,string s_pt,string s_pb)
{
	point* p = new point(sign_c,sign_p,s_ct,s_cb,s_pt,s_pb);
	p->next=first->next;
	first->next=p;
}
point* multi_data::pop()
{
	point* t;
	t=first->next;

	if(t)
	{
		first->next=t->next;
		return t;
	}
	else 
	{
		return t;
	}
}
void multi_data::input(string str)
{
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

		if (b==3)
		{
			t=str.substr(l,i-l-1);
		}
		else
		{
			t=str.substr(l,i-l);
		}
		
		parse_str_data(t,s1,s2,s3,s4,s5,s6);

		push(s1,s4,s2,s3,s5,s6);	
	}
}

multi_data::~multi_data()
{
	point* t=first;
	while (t)
	{
		t=t->next;
		delete first;
		first=t;
	}
}
class calc_multi
{
	private:
		multi_data* mul;
		string expression;
		int len;
	public:
		calc_multi();
		void input();
		void output();
		~calc_multi();
};
calc_multi::calc_multi()
{
	len=0;
}
void calc_multi::input()
{
	cin>>expression;

	unsigned long i=0;
	for (i=0;i<expression.length();i++)
	{
		if(expression[i]>='A'&&expression[i]<='Z')
		{
			len=(len>expression[i]-'A')?len:expression[i]-'A';
		}
	}

	mul=new multi_data[len];
	
	int j;
	string te;
	for(j=0;j<len;j++)
	{
		cin>>te;
		mul[i].input(te);		
	}
}

