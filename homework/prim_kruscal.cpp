#include<iostream>
#define maxValue 2147483647
using namespace std;

class prim
{
	private:
		int* lowcost;
		int* closest;
		int** pic_table;
		int** out_table;
		int* now;
		int length;
	public:
		void intput();
		void search();
		void outTable();
		int in_now(int n);
		void push(int n);
		~prim();
};
void prim::push(int n)
{
	int i;
	for(i=0;i<length;i++)
	{
		if(now[i]==-1)
		{
			now[i] = n;
			break;
		}
	}
}
int prim::in_now(int n)
{
	int i;
	for(i=0;i<length;i++)
	{
		if(now[i]==n)
		{
			return 1;
		}
	}
	return 0;
}
void prim::outTable()
{
	int i;
	int j;
	for(i=0;i<length;i++)
	{
		for(j=0;j<length;j++)
		{
			cout<<out_table[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}
void prim::intput()
{
	int n;
	cin>>n;

	length = n;

	int i;
	lowcost = new int[length]();
	closest = new int[length]();
	now = new int[length];

	for(i=0;i<length;i++)
	{
		pic_table = new int*[length];
		out_table = new int*[length];
		now[i]=-1;
		lowcost[i] = maxValue;
	}
	lowcost[0] = -1;
	for(i=0;i<length;i++)
	{
		pic_table[i] = new int[length];
		out_table[i] = new int[length]();
	}
	
	int j;
	for(i=0;i<length;i++)
	{
		for(j=0;j<length;j++)
		{
			cin>>pic_table[i][j];
			if(pic_table[i][j]==0)
			{
				pic_table[i][j]=maxValue;
			}
		}
	}
}
void low_out(int n,int* a)
{
	int i;
	for(i=0;i<n;i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
}
void prim::search()
{
	low_out(length,lowcost);
	outTable();
	int i=0;
	int j;
	int k;
	now[0]=0;

	while(now[length-1]==-1)
	{
		cout<<"begin new loop";
		low_out(length,lowcost);
		for(k=1;k<length;k++)
		{
			if(lowcost[k] == -1)
			{
				cout<<"k is "<<k<<endl;
				continue;
			}
			lowcost[k]=pic_table[k][0];
			closest[k]=0;
			for(i=0;i<length;i++)
			{
				if(in_now(i))
				{
					cout<<i<<" is in now"<<endl;
					if(pic_table[k][i]<lowcost[k])
					{
						lowcost[k] = pic_table[k][i];
						closest[k] = i;
						cout<<"change path and point "<<pic_table[k][i]<<" "<<k<<" "<<i<<endl;
						low_out(length,lowcost);
					}
				}
			}
		}

		j = 1;
		for(i=1;i<length;i++)
		{
			if(lowcost[i]<lowcost[j]||lowcost[j]==-1)
			{
				j = i;
			}
		}
cout<<"j is  "<<j<<endl;
		out_table[j][closest[j]] = out_table[closest[j]][j] = pic_table[j][closest[j]];
		push(j);
		outTable();
		lowcost[j] = -1;
		low_out(length,lowcost);
	}
}
prim::~prim()
{
	delete [] lowcost;
	delete [] closest;
	delete [] now;
	int i = length;
	for(i=0;i<length;i++)
	{
		delete [] pic_table[i];
		delete [] out_table[i];
	}
	delete [] pic_table;
	delete [] out_table;
}
int main()
{
	prim pr;
	pr.intput();
	pr.search();

	return 0;
}
