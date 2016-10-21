#include<iostream>
#include<cstring>
using namespace std;

struct point
{
	char sign_coefficient;
	char sign_power;
	int* top_coefficient;
	int* bottom_coefficient;
	int* top_power;
	int* bottom_power;
	point* next;

	point(char s1=' ',char s2=' ',string tc="1",string bc="1",string tp="1",string bp="1",point* p=NULL);
	void str_int(int id,string& st);
};
point::point(char s1,char s2,string tc,string bc,string tp,string bp,point* p)
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
		void push(point* p);
		point* pop();
		~multi_data();
};
multi_data::multi_data()
{
	first = new point();
}
void multi_data::input(string s)
{

void multi_data::push(point* p)
{
	p->next=first->next;
	first->next=p;
}
point* multi_data::pop()
{
	point* t;
	t=first->next;
	first->next=t->next;
	return t;
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

