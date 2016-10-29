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
}
int is_positive(int* a)
{
	int i;
	for(i=1;i<a[0];i++)
	{
		if(a[i]>0) return 1;
		if(a[i]<0) return 0;
	}
	
	return -1;
}
int* copy_arry(const int* a)
{
	int i;
	int* t = new int[a[0]];
	for(i=0;i<a[0];i++)
	{
		t[i]=a[i];
	}

	return t;
}
void change_simp( int*& a,const int* t)
{
	int* save_a = new int[a[0]];
	save_a[0] = a[0];
	int* mu = new int[2];
	mu[0]=2;
	mu[1]=0;


	int* be_ch = new int[t[0]+1];
	be_ch[0]=t[0]+1;
	be_ch[1]=0;
	int i;
	for(i=2;i<t[0];i++)
	{
		be_ch[i]=a[i-1];
	}

	int* yu = new int[t[0]+1];
	yu[0] = t[0]+1;
	int* c_yu = NULL;

	int* ch_ji;
	int ia_now = t[0]-1;

	while(ia_now<a[0])
	{
		for(i=0;i<9;i++)
		{
			if(c_yu) delete [] c_yu;
			c_yu = copy_arry(yu);

			mu[1] = i;
			ch_ji=data_multi(mu,t);
			int ii;

			for(ii=1;ii<t[0]+1;ii++)
			{
				int c = ch_ji[0]-ii;
				if(c<1)
				{
					c=0;
				}
				else 
				{
					c = ch_ji[ch_ji[0]-ii];
				}
				yu[yu[0]-ii]=be_ch[be_ch[0]-ii]-c;
			}
			if(!is_positive(yu))
			{
				save_a[ia_now] = i-1;
				break;
			}
		}
		for(i=0;i<yu[0];i++)
		{
			be_ch[i] = c_yu[i];
		}
		delete [] c_yu;
		for(i=1;i<be_ch[0]-1;i++)
		{
			be_ch[i] = be_ch[i+1];
		}
		ia_now++;
		be_ch[i] = a[ia_now];
	}

	delete [] a;
	a = save_a;
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

	change_simp(a,b);
	output(a);
	output(b);
	//cout<<"tewdkfj"<<endl;
	//cout<<big_than(b,a)<<endl;
	//simp(a,b);
	//output(a);
	//output(b);
	//cout<<"差 为:";
	//output(data_sub(a,b));
	//int* c = data_multi(a,b);
	//cout<<"积为";
	//output(c);

	//cout<<"和为";
	//output(data_add(a,b));


	return 0;
}
