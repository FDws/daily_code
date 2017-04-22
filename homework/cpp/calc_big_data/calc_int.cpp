#include<iostream>
#include<cstring>
using namespace std;

struct sign
{
	char symble;
	sign* next;
	sign(char a='#',sign* p=NULL)
	{
		symble=a;
		next=p;
	}
};

int char_int(char ch)
{
	switch(ch)
	{
		case '(':return 6;
		case '+':return 3;
		case '-':return 3;
		case '*':return 5;
		case '/':return 5;
		case ')':return 1;
		case '#':return 0;
	}
	return -1;
}

struct numbers
{
	int num;
	numbers* next;
	numbers(int n=0, numbers* p=NULL)
	{
		num = n;
		next = p;
	}
};

class equation
{
	private:
		sign* first;
		numbers* top;
		int len;
		string e;
		int *data;
	public:
		equation();
		void push_sign(char a);
		void push_numbers(int n);
		char pop_sign();
		int pop_numbers();
		void input();
		void out_put();
		int big_than(char ch1,char ch2);
		~equation();
};

equation::equation()
{
	len = 0;
	first = new sign();
	top  = new numbers();
}
void equation::push_sign(char a)
{
	if (a!='#')
	{
		sign* temp = new sign(a,first->next);
		first->next = temp;
	}
}
void equation::push_numbers(int a)
{
	numbers* temp = new numbers(a,top->next);
	top->next = temp;
}
char equation::pop_sign()
{
	char t;
	sign* temp = first->next;
	if (temp)
	{
		t = temp->symble;
	}
	else
	{
		return first->symble;
	}

	first->next = temp->next;
	delete temp;
	return t;
}
int equation::pop_numbers()
{
	int t;
	numbers* temp = top->next;
	if (temp)
	{
		t = temp->num;
	}
	else
	{
		cout<<"Please check the equation!!"<<endl;
		return -1;
	}
	top->next = temp->next;
	delete temp;
	return t;
}
int equation::big_than(char ch1,char ch2)
{
	return (char_int(ch1)>char_int(ch2));	
}

void equation::input()
{
	cin>>e;
	unsigned long i;
	int j;
	char ch;

	e = e+'#';
	cout<<e<<" "<<e.length()<<endl;

	for (i=0;i<e.length();i++)
	{
		if (e[i]>='A'&&e[i]<='Z')
		{
			len=(len>e[i]-'A')?len:e[i]-'A';	
		}
	}
	len++;
	cout<<len<<endl;
	data = new int[len];
	for (j=0;j<len;j++)
	{
		cin>>ch>>data[j];
	}
	
}
void equation::out_put()
{
	unsigned long is=0;
	char te;
	int t;
	//int i = 50;
	while(1)
	{
		if (e[is]>='A'&& e[is]<='Z')
		{
			push_numbers(data[e[is]-'A']);
			cout<<"push number "<<data[e[is]-'A']<<endl;
			is++;
		}
		else
		{
			te=pop_sign();
			cout<<"pop sign te is "<<te<<endl;
			if (te=='('||big_than(e[is],te))
			{
				push_sign(te);
				push_sign(e[is]);
				cout<<"push te & e[is] "<<te<<" "<<e[is]<<endl;
				is++;
			}
			else 
			{
				cout<<" now calc te is "<<te<<endl;
				int t1 = pop_numbers();
				int t2 = pop_numbers();
				switch(te)
				{
					case '+': t = t2+t1;
							  break;
					case '-': t = t2-t1;
							  break;
					case '*': t = t2*t1;
							  break;
					case '/': t = t2/t1;
							  break;
				}
				push_numbers(t);
				cout<<"calc done push "<<t<<endl;
				
				if(first->next==NULL&&e[is]=='#')
				{
					break;
				}
				else if(e[is]==')')
				{
					char tt = pop_sign();
					if(tt!='(')
					{
						push_sign(tt);
					}
					else
					{
						is++;
					}
				}
				//else if(e[is]==')'&&(te=pop_sign()=='('))
				//{
				//	is++;
				//}
				//else if(e[is]==')'&&(te=pop_sign()!='('))
				//{
				//	push_sign(te);
				//}
				else if(e[is]!='#')
				{
					push_sign(e[is]);
					is++;
				}
			}
			
		}
  	}

	cout<<pop_numbers()<<endl;
}
equation::~equation()
{
	delete first->next;
	delete top->next;
	delete first;
	delete top;
	delete [] data;
}

int main()
{
	equation eq;
	eq.input();
	eq.out_put();

	return 0;
}

