#include<iostream>
#include<string>
#define maxValue 2147483647
using namespace std;

struct save_str
{
	string str;
	save_str* next;
	save_str(string s="");
};
save_str::save_str(string s)
{
	str = s;
	next = NULL;
}
class Str_List
{
	private:
		save_str* first;
	public:
		Str_List();
		int deal_point(char a,char b);
		~Str_List();
};
Str_List::Str_List()
{
	first = new save_str();
}
int Str_List::deal_point(char a,char b)
{
	unsigned long no = -1;
	save_str* temp_a = first;
	save_str* temp_b = first;
	save_str* tt;

	while(temp_a->next)
	{
		if(temp_a->next->str.find(a)!=no)
	   	{
		   	break;
	   	} 
		temp_a = temp_a->next;
	}

	while(temp_b->next)
	{
		if(temp_b->next->str.find(b)!=no)
		{
			break;
		} 
		temp_b = temp_b -> next;
	}

	//a = b = NULL
	//a = b !=NULL
	//a != b

	if(temp_a->next&&temp_a->next==temp_b->next)//this is circle
	{
		//cout<<"is circle"<<endl;
		return 0;
	}
	else if(temp_a->next&&temp_b->next)//a belong to one set,b belong to another
	{
		temp_a->next->str = temp_a->next->str + temp_b->next->str;
		tt = temp_b->next;
		temp_b->next = tt->next;
		delete tt;
		//cout<<" a belong to one, be belong to another"<<endl;
	}
	else if(!temp_a->next&&!temp_b->next)//a and b are not in anyone set
	{
		string s;
		s = s+a;
		s = s+b;
		tt = new save_str(s);
		tt->next = first->next;
		first->next = tt;
		//cout<<"a b are not"<<endl;
	}
	else if(temp_a->next&&!temp_b->next)//a belong to one set, b not belong to anyone set
	{
		temp_a->next->str = temp_a->next->str + b;
		//cout<<"a in, b not"<<endl;
	}
	else if(!temp_a->next&&temp_b->next)//b belong to one set, a not belong to anyone set
	{
		temp_b->next->str = temp_b->next->str + a;
	}
	else 
	{
		cout<<"not include all condition"<<endl;
	}

	return 1;
}
class prim_kruskal
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
		void prim_search();
		void kruskal_search();
		void re_set_out_table();
		void outTable(int t=0);
		~prim_kruskal();
};
void prim_kruskal::re_set_out_table()
{
	int i;
	int j;
	for(i=0;i<length;i++)
	{
		for(j=0;j<length;j++)
		{
			out_table[i][j]=0;
		}
	}
}
void prim_kruskal::outTable(int t)
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
void prim_kruskal::intput()
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
void prim_kruskal::prim_search()
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
	re_set_out_table();
}
void prim_kruskal::kruskal_search()
{
	outTable();
	int n = 0;
	Str_List* str = new Str_List();

	while(n<length-1)
	{
		int i;
		int j;
		int min_x=0;
		int min_y=0;
		int mt=maxValue;

		for(i=0;i<length;i++)
		{
			for(j=0;j<i;j++)
			{
				if(pic_table[i][j]<mt)
				{
					mt = pic_table[i][j];
					min_x = i;
					min_y = j;
				}
			}
		}

		//cout<<"find min and begin to deal"<<endl;
		//cout<<"min_x "<<min_x<<" min_y "<<min_y<<endl;
		if(str->deal_point(min_x+'0',min_y+'0'))
		{
			n++;
			out_table[min_x][min_y] = out_table[min_y][min_x] = pic_table[min_x][min_y];
			outTable();
		}

		pic_table[min_x][min_y] = maxValue;
	}
}
prim_kruskal::~prim_kruskal()
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
	prim_kruskal pr;
	pr.intput();
	cout<<"Prim:"<<endl;
	pr.prim_search();
	cout<<"Kruskal:"<<endl;
	pr.kruskal_search();

	return 0;
}
