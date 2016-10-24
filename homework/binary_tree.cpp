//know the mid sequences and front sequences to make the binary tree
#include <iostream>
#include <string>
using namespace std;

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
binary_node* make_tree(const int* pre,const int* mid)
{
	binary_node* root;
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

    int* mid_right = new int[mid[0]-i];
    mid_right[0]=mid[0]-i;

    for(j=1; j<mid_right[0]; j++,i++)
    {
        mid_right[j] = mid[i+1];
    }

    int* pre_lift = new int[mid_left[0]];
    pre_lift[0] = mid_left[0];

    for(i=1; i<mid_left[0]; i++)
    {
        pre_lift[i] = pre[i+1];
    }

    int* pre_right = new int[mid_right[0]];
    pre_right[0]=mid_right[0];

    for(j=1; j<mid_right[0]; j++,i++)
    {
        pre_right[j] = pre[i+1];
    }

	if(mid_left[0]!=1)
    {
        root->left=make_tree(pre_lift,mid_left);
    }
	if(mid_right[0]!=1)
    {
        root->right=make_tree(pre_right,mid_right);
    }

	return root;
}
void binary_output(binary_node* root)
{
    if(root)
    {
        binary_output(root->left);
        binary_output(root->right);
        cout<<root->data<<" ";
    }
}
struct holder_tree
{
	binary_node* tree;
	holder_tree* next;
	holder_tree(binary_node* bi = NULL,holder_tree* ho = NULL);
};
holder_tree::holder_tree(binary_node* bi,holder_tree* ho)
{
	tree = bi;
	next = ho;
}

class binary_queue
{
	private:
		holder_tree* front;
		holder_tree* last;
	public:
		binary_queue();
		void push(binary_node* bi);
		binary_node* pop();
		void output(binary_node* root);
		~binary_queue();
};
binary_queue::binary_queue()
{
	front = new holder_tree();
	last=front;
}
void binary_queue::push(binary_node* bi)
{
	if(bi)
	{
		holder_tree* temp = new holder_tree(bi);
		last->next = temp;
		last = temp;
	}
}
binary_node* binary_queue::pop()
{
	if(front->next)
	{
		holder_tree* t = front->next;
		binary_node* te = t->tree;
		front->next = t->next;

		delete t;
		if(front->next==NULL)
		{
			last = front;
		}
		return te;
	}
	return NULL;
}
void binary_queue::output(binary_node* root)
{
	push(root);
	binary_node* temp;
	while(1)
	{
		temp = pop();
		cout<<temp->data<<" ";
		if(temp->right==NULL&&temp->left==NULL&&front->next==NULL)
		{
			break;
		}
		if(temp->left)
		{
			push(temp->left);
		}
		if(temp->right)
		{
			push(temp->right);
		}
	}
	cout<<endl;
}
binary_queue::~binary_queue()
{
	delete front;
}
int main()
{
    int* p;
    int* m;
    binary_node* root=NULL;

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

    root = make_tree(p,m);

	binary_queue que;
	que.output(root);

    binary_output(root);
	cout<<endl;

    return 0;
}
