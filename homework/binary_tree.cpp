#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

int N=0;
struct binary_node
{
    int data;
    binary_node* left;
    binary_node* right;

    binary_node(int d=0, binary_node* l=NULL, binary_node* r=NULL);
};
binary_node::binary_node(int d,binary_node* l,binary_node* r)
{
    data = d;
    left = l;
    right = r;
}
void ot(int* a)
{
    int i;
    for(i=0;i<a[0];i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}
void make_tree(binary_node* root,int* pre,int* mid)
{
	ot(pre);
	ot(mid);
    sleep(1);
    root = new binary_node(pre[1]);
    int i;
    for(i=1; i<mid[0]; i++)
    {
        if(pre[1]==mid[i])
        {
            break;
        }
    }

    int* mid_left = new int[i];
    mid_left[0]=i;

    int j;
    for(j=1; j<mid_left[0]; j++)
    {
        mid_left[j] = mid[j];
    }
    //cout<<"Mid_left ";
    //ot(mid_left);

    int* mid_right = new int[mid[0]-i];
    mid_right[0]=mid[0]-i;

    for(j=1; j<mid_right[0]; j++,i++)
    {
        mid_right[j] = mid[i+1];
    }

    //cout<<"mid right ";
    //ot(mid_right);

    int* pre_lift = new int[mid_left[0]];
    pre_lift[0] = mid_left[0];

    for(i=1; i<mid_left[0]; i++)
    {
        pre_lift[i] = pre[i+1];
    }
    //cout<<"pre left ";
    //ot(pre_lift);

    int* pre_right = new int[mid_right[0]];
    pre_right[0]=mid_right[0];

    for(j=1; j<mid_right[0]; j++,i++)
    {
        pre_right[j] = pre[i+1];
    }
    //cout<<"pre right ";
    //ot(pre_right);

    //if(pre[1]!=mid[1])
	if(mid_left[0]!=1)
    {
        make_tree(root->left,pre_lift,mid_left);
    }
    //if(pre[1]!=mid[mid[0]-1])
	if(mid_right[0]!=1)
    {
        make_tree(root->right,pre_right,mid_right);
    }
}
void binary_output(binary_node* root)
{
    if(root)
    {
        binary_output(root->left);
        binary_output(root->right);
        cout<<root->data<<" "<<endl;
    }
}
int main()
{
    int* p;
    int* m;
    binary_node* root;

    int n;
    cin>>n;

    p = new int[n+1];
    m = new int[n+1];
    p[0] = n+1;
    m[0] = n+1;

    int i;
    for(i=1;i<n+1;i++)
    {
        cin>>p[i];
    }
    for(i=1;i<n+1;i++)
    {
        cin>>m[i];
    }

    make_tree(root,p,m);
    binary_output(root);

    return 0;
}
