#include<iostream>
#include<stack>
using namespace std;

class topology
{
	private:
		int length;
		int* in_num;
		int** pic_table;
	public:
		topology();
		void input();
		void judge_circle();
		void cut_in(int k);
		~topology();
};
topology::topology()
{
	input();
}
void topology::cut_in(int k)
{
	int i;
	for(i=0;i<length;i++)
	{
		if(pic_table[k][i]!=0)
		{
			in_num[i]--;
		}
	}
}
void topology::input()
{
	cin>>length;
	int i;
	int j;

	in_num = new int[length]();
	pic_table = new int*[length];

	for(i=0;i<length;i++)
	{
		pic_table[i] = new int[length]();
	}

	for(i=0;i<length;i++)//init the pic_table
	{
		for(j=0;j<length;j++)
		{
			cin>>pic_table[i][j];
			if(pic_table[i][j])
			{
				in_num[j]++;
			}
		}
	}
}
void topology::judge_circle()
{
	int i = 0;
	int j;
	int flag = 1;
	while(i++!=length)
	{
		for(j=0;j<length;j++)
		{
			if(in_num[j]==0)
			{
				cut_in(j);
				in_num[j]=-1;
			}
		}
	}

	for(i=0;i<length;i++)
	{
		if(in_num[i]!=-1)
		{
			cout<<"YES"<<endl;
			flag = 0;
			break;
		}
	}

	if(flag==1)
	{
		cout<<"NO"<<endl;
	}
}
topology::~topology()
{
	for(;length;length--)
	{
		delete [] pic_table[length-1];
	}
	delete [] pic_table;
	delete [] in_num;
}
int main()
{
	topology top;
	top.judge_circle();
	
	return 0;
}
