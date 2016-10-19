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
	first = new sign();
	top  = new numbers();
}
void equation::push_sign(char a)
{
	sign* temp = new sign(a,first->next);
	first->next = temp;
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
		input();
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
	int i;
	len=0;
	char ch;

	e = e+'#';
	cout<<e<<" "<<e.length()<<endl;

	for (i=0;i<e.length();i++)
	{
		if (e[i]>='A'&&e[i]<='Z')
		{
			len++;
		}
	}

	data = new int[len];
	for (i=0;i<len;i++)
	{
		cin>>ch>>data[i];
	}
	
}
void equation::out_put()
{
	int is;
	char te;
	int t;
	for(is=0;is<e.length();is++)
	{
		if (e[is]>='A'&&e[is]<='Z')
		{
			push_numbers(data[e[is]-'A']);
		}
		else
		{
			te=pop_sign();
			if (te=='('||big_than(e[is],te))
			{
				push_sign(te);
				push_sign(e[is]);
			}
			else 
			{
				switch(te)
				{
					case '+': t = pop_numbers()+pop_numbers();
							  break;
					case '-': t = pop_numbers()-pop_numbers();
							  break;
					case '*': t = pop_numbers()*pop_numbers();
							  break;
					case '/': t = pop_numbers() / pop_numbers();
							  break;
				}
				push_numbers(t);
				if (e[is]==')')
				{
					pop_sign();
				}
				else is--; 
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

