#include<iostream>
#include<string>
using namespace std;

void b_ten(int a)
{
	string s="";
	int c;
	int b;
	while(a)
	{
		b = a/2;
		c = a%2;
		a = b;
		if(c)
		{
			s = "1"+s;
		}
		else
		{
			s = "0"+s;
		}
	}
	s = s.substr(1);
	cout<<s;
}
struct tree_node
{
	char simble;
	int num;
	tree_node* left;
	tree_node* right;
	tree_node(char a = '0');
};
tree_node::tree_node(char a)
{
	simble = a;
	num = 1;
}

struct hold_tree
{
	tree_node* node;
	hold_tree* next;
	hold_tree(char a = '0');
};
hold_tree::hold_tree(char a)
{
	node= new tree_node(a);
	next = NULL;
}
struct result
{
	char simble;
	int num;
	int code;
	result* next;
	result(char s = '0',int n = 0,int c = 0);
};
result::result(char s,int n,int c)
{
	simble = s;
	num = n;
	code = c;
	next = NULL;
}
class make_tree
{
	private:
		hold_tree* first;
		result* top;
	public:
		tree_node* root;
		make_tree();
		void push(char s,int n,int c);
		void make_node(char a);
		void output();
		void push(hold_tree* h);
		void sort_hold();
		void bianli(tree_node* ro,int a);
		void out_sort();
		void make_huff();
};
make_tree::make_tree()
{
	first = new hold_tree();
	top = new result();
	root = NULL;
}
void make_tree::output()
{
	result* temp;
	temp = top->next;
	while(temp)
	{
		cout<<temp->simble<<temp->num;
		b_ten(temp->code);
		cout<<endl;
		temp = temp->next;
	}
}
void make_tree::push(char s,int n,int c)
{
	result* temp = new result(s,n,c);
	result* com = top;
	while(1)
	{
		if(com->next==NULL||temp->num>com->next->num)
		{
			temp->next = com->next;
			com->next = temp;
			break;
		}
		com = com->next;
	}
}
void make_tree::make_huff()
{
	hold_tree* temp = first;
	hold_tree* new_hold;
	while(temp->next->next)
	{
		new_hold = new hold_tree();
		new_hold->node->num = temp->next->node->num+temp->next->next->node->num;
		new_hold->node->left = temp->next->node;
		new_hold->node->right = temp->next->next->node;
		push(new_hold);
	}

	root = temp->next->node;
	bianli(root,1);
}
void make_tree::push(hold_tree* h)
{
	hold_tree* temp = first;
	temp->next = temp->next->next->next;
	while(temp->next)
	{
		if(temp->next->node->num>h->node->num)
		{
			break;
		}
		temp = temp->next;
	}
	h->next = temp->next;
	temp->next = h;

}
void make_tree::make_node(char a)
{
	hold_tree* temp = first;
	while(temp->next)
	{
		if(temp->next->node->simble==a)
		{
			temp->next->node->num++;
			break;
		}
		temp=temp->next;
	}
	if(temp->next==NULL)
	{
		hold_tree* hold = new hold_tree(a);
		hold->next = temp->next;
		temp->next = hold;
	}
}
void make_tree::out_sort()
{
	hold_tree* temp = first;
	while(temp->next)
	{
		temp = temp->next;
	}
}
void make_tree::sort_hold()
{
	hold_tree* temp = first;
	hold_tree* mov  = first->next;
	hold_tree* second = mov;
	first->next = NULL;
	while(second)
	{
		mov = second->next;
		temp = first;
		while(temp)
		{
			if(temp->next == NULL||second->node->num<temp->next->node->num)
			{
				second->next = temp->next;
				temp->next = second;
				break;
			}
			temp = temp->next;
		}
		second = mov;
	}
}
void make_tree::bianli(tree_node* ro,int a)
{
	if(ro)
	{
		if(ro->left==NULL)
		{
			push(ro->simble,ro->num,a);
		}
		bianli(ro->left,a*2);
		bianli(ro->right,a*2+1);
	}
}

int main()
{
	make_tree huf;
	int n;
	int i;
	char sim;

	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>sim;
		huf.make_node(sim);
	}

	huf.sort_hold();
	huf.out_sort();
	huf.make_huff();
	huf.output();
	return 0;
}
