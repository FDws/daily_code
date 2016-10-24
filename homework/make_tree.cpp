//kown the sequence structure of one tree 
//make the tree and output it
#include<iostream>
using namespace std;

struct tree_node
{
	int data;
	tree_node* left;
	tree_node* right;
	tree_node(int p = 0,tree_node* l = NULL, tree_node* r = NULL);
};
tree_node::tree_node(int p,tree_node* l,tree_node* r)
{
	data = p;
	left = l;
	right = r;
}
struct holder_tree
{
	tree_node* tree;
	holder_tree* next;
	holder_tree(tree_node* t = NULL,holder_tree* ho = NULL);
};
holder_tree::holder_tree(tree_node* t, holder_tree* ho)
{
	tree = t;
	next = ho;
}
class binary_queue
{
	private:
		holder_tree* front;
		holder_tree* last;
		tree_node* root;
		int* in;
	public:
		binary_queue();
		void push(tree_node* t);
		void make_tree();
		void front_output(tree_node* r);
		void mid_output(tree_node* r);
		void back_output(tree_node* r);
		void output();
		tree_node* pop();
		~binary_queue();
};
binary_queue::binary_queue()
{
	front = new holder_tree();
	last = front;
	root  = NULL;
	int n;
	int i;
	cin>>n;
	in = new int[n+1];

	in[0] = n+1;
	for(i=1;i<n+1;i++)
	{
		cin>>in[i];
	}

}
void binary_queue::output()
{
	front_output(root);
	cout<<endl;
	mid_output(root);
	cout<<endl;
	back_output(root);
	cout<<endl;
}
void binary_queue::front_output(tree_node* t)
{
	if(t)
	{
		if(t->data) cout<<t->data<<"  ";
		front_output(t->left);
		front_output(t->right);
	}
}

void binary_queue::mid_output(tree_node* t)
{
	if(t)
	{
		mid_output(t->left);
		if(t->data) cout<<t->data<<"  ";
		mid_output(t->right);
	}
}
void binary_queue::back_output(tree_node* t)
{
	if(t)
	{
		back_output(t->left);
		back_output(t->right);
		if(t->data) cout<<t->data<<"  ";
	}
}
void binary_queue::push(tree_node* t)
{
	holder_tree* temp = new holder_tree(t);
	last->next = temp;
	last = temp;
}
tree_node* binary_queue::pop()
{
	if(front->next)
	{
		tree_node* temp = front->next->tree;
		holder_tree* te = front->next;
		front->next = te->next;

		if(front->next == NULL)
		{
			last = front;
		}
		delete te;
		return temp;
	}
	return NULL;
}
void binary_queue::make_tree()
{
	//cout<<"begin make"<<endl;
	root = new tree_node(in[1]);

	push(root);
	tree_node* t;
	tree_node* temp;
	int i=2;
	while(i<in[0])
	{
		temp = pop();
		//if(in[i])
		{
			t = new tree_node(in[i]);
			temp->left = t;
			push(t);
		}	
		i++;
		if(i==in[0])
		{
			continue;
		}
		//if(in[i])
		{
			t = new tree_node(in[i]);
			temp ->right = t;
			push(t);
		}	
		i++;
	}
	//cout<<"make done"<<endl;
}
binary_queue::~binary_queue()
{
	delete front;
	delete [] in;
}
int main()
{
	binary_queue qu;
	qu.make_tree();
	qu.output();

	return 0;
}
