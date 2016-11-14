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
		void outTable(int t=0);
		~prim();
};
void prim::outTable(int t)
{
	int** tt;
	if(!t)
	{
		tt = out_table;
	}
	else 
	{
		tt = pic_table;
	}
	int i;
	int j;
	for(i=0;i<length;i++)
	{
		for(j=0;j<length;j++)
		{
			cout<<tt[i][j]<<" ";
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
	now = new int[length]();

	for(i=0;i<length;i++)
	{
		pic_table = new int*[length];
		out_table = new int*[length];
	}

	for(i=0;i<length;i++)
	{
		pic_table[i] = new int[length]();
		out_table[i] = new int[length]();
	}
	
	int j;
	for(i=0;i<length;i++)
	{
		for(j=0;j<length;j++)
		{
			cin>>pic_table[i][j];
		}
	}

	cout<<n<<endl;
	outTable(1);

	for(i=0;i<length;i++)
	{
		for(j=0;j<length;j++)
		{
			if(pic_table[i][j]==0)
			{
				pic_table[i][j]=maxValue;
			}
		}
	}
}

void prim::search()
{
	outTable();
	now[0] = 1;//push the first point
	lowcost[0]=0;

	int n = 1;
	while(n!=length)
	{
		int i;
		int j;
		int k;

		for(k=0;k<length;k++)
		{
			if(now[k]==1)
			{
				continue;
			}
			else
			{
				lowcost[k]=pic_table[k][0];
				closest[k]=0;
				for(i=1;i<length;i++)
				{
					if(now[i]&&pic_table[k][i]<lowcost[k])
					{
						lowcost[k] = pic_table[k][i];
						closest[k] = i;
					}
				}
			}
		}

		j = maxValue;
		int l = 0;
		for(i=0;i<length;i++)
		{
			if(now[i]==0&&lowcost[i]<j)
			{
				j = lowcost[i];
				l = i;
			}
		}

		//now the l is the point waiting to push
		now[l] = 1;
		out_table[l][closest[l]] = out_table[closest[l]][l] = pic_table[l][closest[l]];
		n++;
		outTable();
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
class kruskal:public prim
{
	private:
	public:
};
int main()
{
	prim pr;
	pr.intput();
	pr.search();

	return 0;
}
