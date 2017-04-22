#include<iostream>
#include<string>
#include<stack>
#define maxValue 9999999
using namespace std;

class cri
{
	private:
		stack<int> st_in;
		stack<int> st_out;
		string out;
		int** pic_table;
		int* e;
		int* l;
		int* ve;
		int* vl;
		int* in_point;
		int length;
	public:
		~cri();
		void input();
		void search();
		void cut_in(int k);
		void set_max(int k);
		void set_min(int k,int flag = 0);
		void judge(int k);
};
void cri::cut_in(int k)
{
	int i;
	for(i=0;i<length;i++)
	{
		if(pic_table[k][i])
		{
			in_point[i]--;
		}
	}
}
void cri::input()
{
	cin>>length;
	e = new int[length]();
	l = new int[length]();
	ve = new int[length]();
	vl = new int[length]();
	in_point = new int[length]();
	pic_table = new int*[length];
	
	int i;
	for(i=0;i<length;i++)
	{
		pic_table[i] = new int[length]();
	}

	int j;
	for(i=0;i<length;i++)
	{
		for(j=0;j<length;j++)
		{
			cin>>pic_table[i][j];
			if(pic_table[i][j])
			{
				in_point[j]++;
			}
		}
	}
	cout<<"input finish"<<endl;
}
void cri::judge(int k)
{
	int i;
	for(i=0;i<length;i++)
	{
		if(pic_table[i][k])
		{
			cout<<"ve["<<i<<"] is "<<ve[i]<<"vl["<<k<<"] is "<<vl[k]<<"pic_table between is "<<pic_table[i][k]<<endl;
			if(ve[i]==vl[k]-pic_table[i][k])
			{
				char t = k+'0';
				out = out + t;
				break;
			}
		}
	}
}
void cri::set_max(int k)
{
	ve[k] = 0;
	int i;
	for(i=0;i<length;i++)
	{
		if(pic_table[i][k])
		{
			if(ve[i]+pic_table[i][k]>ve[k])
			{
				ve[k] = ve[i]+pic_table[i][k];
			}
		}
	}
}
void cri::set_min(int k,int flag)
{
	vl[k] = maxValue;
	if(flag) vl[k] = ve[k];

	int i;
	for(i=0;i<length;i++)
	{
		if(pic_table[k][i])
		{
			if(vl[k]>vl[i]-pic_table[k][i])
			{
				vl[k] = vl[i] - pic_table[k][i];
			}
		}
	}
}
void outPut(int l,int* a)
{
	int i;
	for(i=0;i<l;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
void cri::search()
{
	int i;
	int flag = length;
	int one = 1;
	while(flag)
	{
		cout<<"in_point is ";
		outPut(length,in_point);
		for(i=0;i<length;i++)
		{
			if(in_point[i] == 0)
			{
				cout<<"now push "<<i<<endl;
				if(one)
				{
					char t = i + '0';
					out = out + t;
					one = 0;
				}
				st_in.push(i);
				set_max(i);
				in_point[i]--;
				cut_in(i);
				flag--;
			}
		}
	}
	
	cout<<"in finish"<<endl;
	flag = 1;
	for(i=0;i<length;i++)
	{
		cout<<"now in top is "<<st_in.top()<<endl;
		if(flag)
		{
			flag = 0;
			set_min(st_in.top(),1);
		}
		else
		{
			set_min(st_in.top());
		}
		judge(st_in.top());
		st_in.pop();
	}
	cout<<out[0]<<" ";
	for(i=out.length()-1;i;i--)
	{
		cout<<out[i]<<" ";
	}
	cout<<endl;
}
cri::~cri()
{
	delete [] e;
	delete [] l;
	delete [] ve;
	delete [] vl;
	delete [] in_point;

	int i;
	for(i=0;i<length;i++)
	{
		delete [] pic_table[i];
	}
	delete [] pic_table;
}
int main()
{
	cri cc;
	cc.input();
	cc.search();

	return 0;
}
