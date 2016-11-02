#include<iostream>
using namespace std;
struct node
{
	int num;
	node* left;
	node* right;
	node(int n = 0);
};
node::node(int n)
{
	num = n;
	left = NULL;
	right = NULL;
}
int num_in(int* a,int b)
{
	int i;
	for(i=1;i<a[0];i++)
	{
		if(a[i]==b)
		{
			return 1;
		}
	}
	return 0;
}
void make_tree(node*& root,int* arr,int* mid)
{
	if(arr[0]!=1)
	{
		root = new node(arr[1]);
		if(arr[0]!=2)
		{
			int* left_arr;
			int* left_mid;
			int* right_arr;
			int* right_mid;

			int i;
			int pos;
			for(i=1;i<mid[0];i++)
			{
				if(mid[i]==arr[1])
				{
					break;
				}
			}

			pos =  i;
			left_arr = new int[pos]();
			left_mid = new int[pos]();
			left_arr[0] = pos;
			left_mid[0] = pos;

			right_arr = new int[mid[0]-pos]();
			right_mid = new int[mid[0]-pos]();
			right_arr[0] = mid[0]-pos;
			right_mid[0] = mid[0]-pos;

			for(i=1;i<left_mid[0];i++)
			{
				left_mid[i] = mid[i];
			}
			i++;
			int j;
			for(j=1;i<mid[0];j++,i++)
			{
				right_mid[j] = mid[i];
			}

			int l=1;
			int r=1;
			for(i=2;i<arr[0];i++)
			{
				if(num_in(left_mid,arr[i]))
				{
					left_arr[l] = arr[i];
					l++;
				}
				else
				{
					right_arr[r]=arr[i];
					r++;
				}
			}

			make_tree(root->left,left_arr,left_mid);
			make_tree(root->right,right_arr,right_mid);
			delete [] left_arr;
			delete [] right_arr;
			delete [] left_mid;
			delete [] right_mid;
		}
	}
}
void output(node* root)
{
	if(root)
	{
		cout<<root->num<<" ";
		output(root->left);
		output(root->right);
	}
}
void out_put(node* root)
{
	if(root)
	{
		out_put(root->left);
		out_put(root->right);
		cout<<root->num<<" ";
	}
}
int main()
{
	int n;
	cin>>n;

	int* arr = new int[n+1];
	int* mid = new int[n+1];
	arr[0] = n+1;
	mid[0] = n+1;

	int i;
	for(i=1;i<n+1;i++)
	{
		cin>>mid[i];
	}
	for(i=1;i<n+1;i++)
	{
		cin>>arr[i];
	}

	node* root;
	make_tree(root,arr,mid);
	output(root);
	cout<<endl;
	out_put(root);
	cout<<endl;

	return 0;
}
