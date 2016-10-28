#include<iostream>
#include<cstring>
using namespace std;

void output(const int* a)
{
	int i;
	for(i=1;i<a[0];i++)
	{
		cout<<a[i];
	}
}
int char_int(char ch)
{
	switch(ch)
	{
		case '(':return 6;
		case '+':return 3;
		case '-':return 3;
		case '*':return 5;
		case ')':return 1;
		case '#':return 0;
	}
	return -1;
}
int big_than(char ch1,char ch2)
{
	return (char_int(ch1)>char_int(ch2));
}
int big_than(const int* a,const int* b)
{
	if(a[0]>b[0])
	{
		return 1;
	}
	else if(b[0]>a[0])
	{
		return 0;
	}

	int i=1;
	while(i<a[0])
	{
		if(a[i]>b[i])
		{
			return 1;
			break;
		}
		else if(a[i]<b[i])
		{
			return 0;
			break;
		}
		i++;
	}

	return 0;
}
int* data_multi(const int* a,const int* b)
{
	int * temp = new int[a[0]+b[0]-1]();
	temp[0] = a[0]+b[0]-1;

	int i;
	int j;
	int t;
	int* tt;
	for(j=b[0]-1;j>0;j--)
	{
		t = temp[0]-(b[0]-j);
		for(i=a[0]-1;i>0;i--,t--)
		{
			temp[t] = temp[t]+a[i]*b[j];

			temp[t-1] = temp[t-1]+temp[t]/10;
			temp[t] = temp[t]%10;

			if(t-2>0)
			{
				temp[t-2] = temp[t-2] + temp[t-1]/10;
				temp[t-1] = temp[t-1]%10;
			}
		}
	}

	while(!temp[1]&&temp[0]>2)
	{
	    tt = new int[temp[0]-1];
		tt[0] = temp[0]-1;

		for(i=1;i<tt[0];i++)
		{
			tt[i] = temp[i+1];
		}

		delete [] temp;
		temp = tt;
	}
	return temp;
}
int* data_add(int* a,int* b)
{
	int len = (a[0]>b[0]?a[0]+1:b[0]+1);
	int* temp  = new int[len]();
	temp[0] = len;

	int i;
	int j;
	int t = len-1;
	int* d;
	int* tt;
	if(a[0]<b[0])
	{
		d = a;
		a = b;
		b = d;
	}

	for(i=a[0]-1,j=b[0]-1;j>0;i--,j--,t--)
	{
		temp[t] = temp[t]+a[i]+b[j];

		temp[t-1] = temp[t-1]+temp[t]/10;
		temp[t] = temp[t]%10;

		if(t-2>0)
		{
			temp[t-2] = temp[t-2] + temp[t-1]/10;
			temp[t-1] = temp[t-1]%10;
		}
	}
	while(i)
	{
		temp[t] =temp[t]+a[i];
		temp[t-1] = temp[t-1]+temp[t]/10;
		temp[t] = temp[t]%10;
		i--;
		t--;
	}


	while(!temp[1]&&temp[0]>2)
	{
		tt = new int[temp[0]-1];
		tt[0] = temp[0]-1;

		for(i=1;i<tt[0];i++)
		{
			tt[i] = temp[i+1];
		}

		delete [] temp;
		temp = tt;
	}
	return temp;

}
int* data_sub(const int* a,const int* b)
{
	int len = a[0]>b[0]?a[0]:b[0];
	int* temp = new int[len]();
	temp[0] = len;

	int i;
	int j;
	for(i=a[0]-1,j=b[0]-1,len--;j>0;j--,i--,len--)
	{
		temp[len] = a[i]-b[j];
	}

	while(i)
	{
		temp[len] = a[i];
		i--;
		len--;
	}

	len = temp[0]-1;
	while(len)
	{
		if(temp[len]<0)
		{
			temp[len] = temp[len]+10;
			temp[len-1] = temp[len-1]-1;
		}
		len--;
	}

	while(!temp[1]&&temp[0]>2)
	{
		int* tt = new int[temp[0]-1];
		tt[0] = temp[0]-1;

		for(i=1;i<tt[0];i++)
		{
			tt[i] = temp[i+1];
		}
		delete [] temp;
		temp = tt;
	}

	return temp;
}

//void simp(int*& a,int*& b)
//{
//	int* ta = new int[a[0]];
//	int* tb = new int[b[0]];
//	int* t;
//
//	int i;
//	for(i=0;i<a[0];i++)
//	{
//		ta[i] = a[i];
//	}
//	for(i=0;i<b[0];i++)
//	{
//		tb[i] = b[i];
//	}
//
//	while(big_than(ta,tb)||big_than(tb,ta))
//	{
//		if(big_than(ta,tb))
//		{
//			t=data_sub(ta,tb);
//			delete [] ta;
//			ta = tb;
//			tb = t;
//		}
//		else 
//		{
//			t = data_sub(tb,ta);
//			delete [] tb;
//			tb = ta;
//			ta = t;
//		}
//	}
//	delete [] ta;
//	t = tb;
//
//	ta = new int[a[0]];
//	tb = new int[b[0]];
//	for(i=0;i<a[0];i++)
//	{
//		ta[i] = a[i];
//	}		
//	for(i=0;i<b[0];i++)
//	{
//		tb[i] = b[i];
//	}
//
//
//	int* num;
//	int* t1;
//	int* x = new int[2];
//	int* ad = new int[2];
//	x[0]=ad[0]=2;
//	x[1]=0;
//	ad[1] = 1;
//
//	while(ta[1])
//	{
//		t1 = data_sub(ta,t);
//		delete [] ta;
//		ta = t1;
//		num = data_add(x,ad);
//		delete [] x;
//		x = num;
//	}
//	a = x;
//
//	int* y = new int[2];
//	y[0]=2;
//	y[1]=0;
//
//	while(tb[1])
//	{
//		t1 = data_sub(tb,t);
//		delete [] tb;
//		tb = t1;
//
//		num = data_add(y,ad);
//		delete [] y;
//		y = num;
//	}
//	b = y;
//	delete [] ad;
//}
struct point
{
	string sign_coefficient;
	string sign_power;
	int* top_coefficient;
	int* bottom_coefficient;
	int* top_power;
	int* bottom_power;
	point* next;

	point(string s1,string s2,string tc,string bc,string tp,string bp,point* p = NULL);
	point();
	point(string sign_c,string sign_p,int* s_ct,int* s_cb,int* s_pt,int* s_pb,point* p = NULL);
	friend point* operator*(const point& a,const point &b);
	void str_int(int id,string& st);
	int* copy_int(int* t);
};
point* operator*(const point& a,const point& b)
{
	cout<<"Point * begin"<<endl;
	point* temp = new point();

	if(a.sign_coefficient == b.sign_coefficient)
	{
		temp->sign_coefficient = "+";
	}
	else 
	{
		temp->sign_coefficient = "-";
	}

	temp->top_coefficient = data_multi(a.top_coefficient,b.top_coefficient);
	temp->bottom_coefficient = data_multi(a.bottom_coefficient,b.bottom_coefficient);
	temp->bottom_power = data_multi(a.bottom_power,b.bottom_power);

	if(a.sign_power==b.sign_power)
	{
		temp->sign_power=a.sign_power;
		temp->top_power = data_add(data_multi(a.top_power,b.bottom_power),data_multi(a.bottom_power,b.top_power));
	}
	else if(a.sign_power=="-")
	{
		int* x = data_multi(a.top_power,b.bottom_power);
		int* y = data_multi(a.bottom_power,b.top_power);

		if(big_than(x,y))
		{
			temp->sign_power = "-";
			temp->top_power = data_sub(x,y);
		}
		else 
		{
			temp->sign_power = "+";
			temp->top_power = data_sub(y,x);
		}
	}
	else
	{
		int* x = data_multi(a.top_power,b.bottom_power);
		int* y = data_multi(a.bottom_power,b.top_power);

		if(big_than(x,y))
		{
			temp->sign_power = "+";
			temp->top_power  = data_sub(x,y);
		}
		else
		{
			temp->sign_power = "-";
			temp->top_power = data_sub(y,x);
		}
	}
	
	cout<<"Point * done"<<endl;
	return temp;
}
point::point()
{
	sign_coefficient = "+";
	sign_power = "+";
	next = NULL;
}
point::point(string s1,string s2,string tc,string bc,string tp,string bp,point* p)
{
	sign_coefficient=s1;
	sign_power=s2;

	str_int(1,tc);
	str_int(2,bc);
	str_int(3,tp);
	str_int(4,bp);
	next=p;
	next = NULL;
}
point::point(string sign_c,string sign_p,int* s_ct,int* s_cb,int* s_pt,int* s_pb,point* p)
{
	sign_coefficient = sign_c;
	sign_coefficient = sign_p;
	
	top_coefficient = copy_int(s_ct);
	bottom_coefficient = copy_int(s_cb);
	top_power = copy_int(s_pt);
	bottom_power= copy_int(s_pb);

	next = p;
	next = NULL;
}
int* point::copy_int(int* t)
{
	cout<<"copy_int begin"<<endl;;
	int* aim = new int[t[0]];
	int i;
	for(i=0;i<t[0];i++)
	{
		aim[i]=t[i];
	}
	cout<<"copy int done"<<endl;
	return aim;
}
void point::str_int(int id,string& st)
{
	cout<<"str_int begin "<<endl;
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
	cout<<"str int done"<<endl;
}
struct multi_data
{
		point *first;
		multi_data *next;
		multi_data();
		void copy_point(const multi_data* a);
		void input(string s);
		void push(string sign_c,string sign_p,string s_ct,string s_cb,string s_pt,string s_pb);
		void parse_str_data(string& t,string &s1,string &s2,string &s3,string &s4,string &s5,string &s6);
		void parse_str_data_part(string &t,string &s1,string &s2,string& s3);
		void push(string sign_c,string sign_p,int * i1,int* i2, int* i3,int* i4);
		void push(point* p);
		friend multi_data* operator+(const multi_data& m1,const multi_data& m2);
		friend multi_data* operator-(const multi_data& m1,const multi_data& m2);
		friend multi_data* operator*(const multi_data& m1,const multi_data& m2);
		friend ostream& operator<<(ostream& out,multi_data& a);
		void arrange();
		point* pop();
		~multi_data();
};
ostream& operator<<(ostream& out,multi_data& a)
{
	cout<<" cout << begin "<<endl;
	a.arrange();
	point* temp = a.first;
	while(temp)
	{
		if(temp->sign_coefficient=="+")
		{
			output(temp->top_coefficient);
		}
		else
		{
			out<<"-";
			output(temp->top_coefficient);
		}

		if(temp->bottom_coefficient[1]==1)
		{
			out<<" x ";
		}
		else
		{
			out<<"/";
			output(temp->bottom_coefficient);
			out<<" x ";
		}

		if(temp->sign_power=="+")
		{
			output(temp->top_power);
		}
		else
		{
			out<<"-";
			output(temp->top_power);
		}

		if(temp->bottom_power[1]!=1)
		{
			out<<"/";
			output(temp->bottom_coefficient);
		}
		temp = temp->next;
	}

	cout<<" cout << done"<<endl;
	return out;
}
void multi_data::arrange()
{
	cout<<"start arrange"<<endl;
	point* temp = first->next;
	point* pre = first;
	//while(temp)
	//{
	//	if(temp->top_coefficient[1]==0)
	//	{
	//		pre->next = temp->next;
	//		delete [] temp;
	//		temp = pre->next;
	//		continue;
	//	}

	//	simp(temp->top_coefficient,temp->bottom_coefficient);
	//	simp(temp->top_power,temp->bottom_power);
	//}

	point* second = first->next;
	point* move = second;
	first->next = NULL;

	while(second)
	{
		temp = first;
		move = second;
		second = second->next;

		if(move->top_coefficient[1]==0)
		{
			delete [] move;
			continue;
		}
		while(1)
		{
			if(temp->next==NULL||(move->sign_power=="+"&&temp->next->sign_power=="-")||
			  (move->sign_power=="+"&&big_than(data_multi(move->top_power,temp->next->bottom_power),data_multi(move->bottom_power,temp->next->top_power)))||
			  (move->sign_power=="-"&&big_than(data_multi(move->bottom_power,temp->next->top_power),data_multi(move->top_power,temp->next->bottom_power))))
			{
				move->next =  temp->next;
				temp->next = move;
				break;
			}
			temp = temp->next;
		}
	}
	cout<<"arrange finish"<<endl;
}

void multi_data::copy_point(const multi_data* a)
{
	cout<<"copy point start"<<endl;

	//first = new point();
	point* temp = a->first->next;
	while(temp)
	{
		cout<<"temp :"<<temp<<endl;
		output(temp->top_coefficient);
		cout<<"/";
		output(temp->bottom_coefficient);
		cout<<endl;
		output(temp->top_power);
		cout<<"/";
		output(temp->bottom_power);
		cout<<endl;
		push(temp->sign_coefficient,temp->sign_power,temp->top_coefficient,temp->bottom_coefficient,temp->top_power,temp->bottom_power);
		temp = temp->next;
	}
	cout<<" copy_point done"<<endl;
}
void multi_data::push(point* p)
{
	p->next = first->next;
	first ->next = p;
}
multi_data* operator+(const multi_data& m1,const multi_data& m2)
{
	cout<<"multi_data +  start"<<endl;
	multi_data* temp = new multi_data();

	point* t = m1.first->next;
	while(t)
	{
		temp->push(t->sign_coefficient,t->sign_power,t->top_coefficient,t->bottom_coefficient,t->top_power,t->bottom_power);
		t = t->next;
	}

	t = m2.first->next;
	while(t)
	{
		temp->push(t->sign_coefficient,t->sign_power,t->top_coefficient,t->bottom_coefficient,t->top_power,t->bottom_power);
		t = t->next;
	}
	cout<<"multi_data + done"<<endl;
	return temp;
}

multi_data* operator-(const multi_data& m1,const multi_data& m2)
{
	cout<<"multi_data - begin "<<endl;
	multi_data* temp = new multi_data();
	point* t = m1.first->next;

	while(t)
	{
		temp->push(t->sign_coefficient,t->sign_power,t->top_coefficient,t->bottom_coefficient,t->top_power,t->bottom_power);
		t=t->next;
	}

	t=m2.first->next;
	while(t)
	{
		if(t->sign_coefficient=="-")
		{
			temp->push("+",t->sign_power,t->top_coefficient,t->bottom_coefficient,t->top_power,t->bottom_power);
			t = t->next;
		}
		else
		{
			temp->push("-",t->sign_power,t->top_coefficient,t->bottom_coefficient,t->top_power,t->bottom_power);
			t = t->next;
		}

	}

	cout<<"multi_data - done"<<endl;
	return temp;
}
multi_data* operator*(const multi_data& m1,const multi_data& m2)
{
	cout<<"multi_data * start"<<endl;
	multi_data* temp = new multi_data();

	point* p1 = m1.first->next;
	point* p2 = m2.first->next;

	while(p1)
	{
		p2=m2.first->next;
		while(p2)
		{
			temp->push((*p1)*(*p2));
			p2=p2->next;
		}
		p1=p1->next;
	}

	cout<<"multi_data * done"<<endl;
	return temp;

}
multi_data::multi_data()
{
	first = new point();
	next = NULL;
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
		i++;
	}
}
void multi_data::push(string sign_c,string sign_p,string s_ct,string s_cb,string s_pt,string s_pb)
{
	point* p = new point(sign_c,sign_p,s_ct,s_cb,s_pt,s_pb);
	push(p);
	//p->next=first->next;
	//first->next=p;
}
void multi_data::push(string sign_c,string sign_p,int * i1,int* i2, int* i3,int* i4)
{
	point* p = new point(sign_c,sign_p,i1,i2,i3,i4);
	push(p);
	//p->next = first->next;
	//first->next = p;
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
struct sign
{
	char symble;
	sign* next;
	sign(char a='#',sign* p = NULL)
	{
		symble = a;
		next = p;
	}
};
class calc_multi
{
	private:
		multi_data* mul;
		multi_data* number_stack;
		sign* sign_stack;
		string expression;
		int len;
	public:

		calc_multi();
		void input();
		void push_sign(char a);
		void push_number(const multi_data* a);
		char pop_sign();
		multi_data* pop_number();
		void output();
		~calc_multi();
};
calc_multi::calc_multi()
{
	len=0;
	number_stack = new multi_data();
	sign_stack = new sign();
}
multi_data* calc_multi::pop_number()
{
	multi_data* temp = number_stack->next;

	if(temp)
	{
		number_stack->next = temp->next;
	}

	return temp;
}
char calc_multi::pop_sign()
{
	char t;
	sign* temp = sign_stack->next;
	if(temp)
	{
		t = temp->symble;
	}
	else
	{
		return sign_stack->symble;
	}

	sign_stack->next = temp->next;
	delete temp;
	return t;
}
void calc_multi::input()
{
	cin>>expression;
	expression = expression+'#';

	unsigned long i=0;
	for (i=0;i<expression.length();i++)
	{
		if(expression[i]>='A'&&expression[i]<='Z')
		{
			len=(len>expression[i]-'A')?len:expression[i]-'A';
		}
	}
	len = len+1;

	mul=new multi_data[len];
	
	int j;
	string s;
	getchar();
	for(j=0;j<len;j++)
	{
		getline(cin,s);
		s = s.substr(2);
		mul[j].input(s);		
	}
	cout<<"input finish"<<endl;
}
void calc_multi::push_sign(char a)
{
	if(a!='#')
	{
		sign* temp =  new sign(a,sign_stack->next);
		sign_stack->next = temp;
	}
}
void calc_multi::push_number(const multi_data* a)
{
	multi_data* t = new multi_data();
	t->copy_point(a);
	t->next = number_stack->next;
	number_stack->next = t->next;
}
void calc_multi::output()
{
	unsigned long is = 0;
	char te;
	multi_data* t;
	while(1)
	{
		if(expression[is]>='A'&&expression[is]<='Z')
		{
			cout<<"push number mul["<<is<<"]"<<endl;
			push_number(&mul[expression[is]-'A']);
			is++;
		}
		else
		{
			te = pop_sign();
			cout<<"pop sign "<<te<<endl;
			if(te=='('||big_than(expression[is],te))
			{
				push_sign(te);
				push_sign(expression[is]);
				cout<<"Push "<<te<<" "<<expression[is]<<endl;
				is++;
			}
			else 
			{
				cout<<"kkkkkkkkkkkkkkkkkkkkkkkkkk"<<te<<endl;
				switch(te)
				{
					case '+': t = *pop_number()+*pop_number();
							  break;
					case '-': t = *pop_number()-*pop_number();
							  break;
					case '*': t = *pop_number()**pop_number();
							  break;
				}
				cout<<"calc push_number t"<<endl;
				push_number(t);

				if(sign_stack->next == NULL&&expression[is]=='#')
				{
					break;
				}
				else if(expression[is]==')')
				{
					pop_sign();
					is++;
				}
				else  if(expression[is]!='#')
				{
					push_sign(expression[is]);
					is++;
				}
			}
		}
	}
	cout<<pop_number()<<endl;
}
calc_multi::~calc_multi()
{
	delete sign_stack;
	delete number_stack;
	delete [] mul;
}
int main()
{
	calc_multi calc;
	calc.input();
	calc.output();

	return 0;
}
