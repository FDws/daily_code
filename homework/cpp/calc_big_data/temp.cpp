#include<iostream>
using namespace std;

void change_simp(int*& a,const int* t);
void output(int *a)
{
	int i; 
	for(i=1;i<a[0];i++)
	{
		cout<<a[i];
	}
	cout<<endl;
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
inline int* data_add(int* a,int* b)
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
int* data_sub(int* a,int* b)
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
inline int big_than(const int* a,const int* b)
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
void simp(int*& a,int*& b)
{
	if(a[1]!=0)
	{
		int* ta = new int[a[0]];
		int* tb = new int[b[0]];
		int* t;

		int i;
		for(i=0;i<a[0];i++)
		{
			ta[i] = a[i];
		}
		for(i=0;i<b[0];i++)
		{
			tb[i] = b[i];
		}

		while(big_than(ta,tb)||big_than(tb,ta))
		{
			if(big_than(ta,tb))
			{
				t=data_sub(ta,tb);
				delete [] ta;
				ta = tb;
				tb = t;
			}
			else 
			{
				t = data_sub(tb,ta);
				delete [] tb;
				tb = ta;
				ta = t;
			}
		}
		delete [] ta;
		t = tb;

		change_simp(a,t);
		change_simp(b,t);
	}
}
void change_simp(int*& a,const int* t)
{
	int* te = new int[a[0]];
	te[0] = a[0];
	int i;
	int* tt;
	for(i=1;i<te[0];i++)
	{
		te[i] = 9;
	}

	int i_now = 1;
	while(i_now<a[0])
	{
		tt = data_multi(t,te);
		while(big_than(tt,a)&&te[i_now])
		{
			delete [] tt;
			te[i_now] = te[i_now]-1;
			tt = data_multi(t,te);
		}
		if(big_than(a,tt))
		{
			te[i_now] = te[i_now]+1;
		}
		i_now++;
	}

	while(!te[1]&&te[0]>2)
	{
		tt = new int[te[0]-1];
		tt[0] = te[0]-1;
	
		for(i=1;i<tt[0];i++)
		{
			tt[i] = te[i+1];
		}
		delete [] te;
		te = tt;
	}

	delete [] a;
	a = te;
}
int main()
{
	int n;
	int m;
	int *a;
	int *b;

	cin>>n;
	a = new int[n+1];
	a[0] = n+1;
	int i;
	for(i=1;i<a[0];i++)
	{
		cin>>a[i];
	}

	cin>>n;
	b = new int[n+1];
	b[0] = n+1;
	for(i=1;i<b[0];i++)
	{
		cin>>b[i];
	}
	cout<<"input finish!!\ncalcing......"<<endl;

	//change_simp(a,b);
	//output(a);
	//cout<<"tewdkfj"<<endl;
	//cout<<big_than(b,a)<<endl;
	simp(a,b);
	output(a);
	output(b);
	//cout<<"差 为:";
	//output(data_sub(a,b));
	//int* c = data_multi(a,b);
	//cout<<"积为";
	//output(c);

	//cout<<"和为";
	//output(data_add(a,b));


	return 0;
}
