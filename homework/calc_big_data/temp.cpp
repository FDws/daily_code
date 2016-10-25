#include<iostream>
using namespace std;

void output(int *a)
{
	int i; 
	for(i=1;i<a[0];i++)
	{
		cout<<a[i];
	}
	cout<<endl;
}
int* data(int* a,int* b)
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

	if(temp[1]==0)
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

	int* c = data(a,b);
	output(c);

	return 0;
}
