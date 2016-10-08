#include <iostream>
using namespace std;

struct loc
{
	int x;
	int y;
}

struct LinkNode
{
	int x;
	int y;
	int lv;
	LinkNode* next;
	LinkNode(int a=0, int b=0,LinkNode* p=NULL);
}
LinkNode::LinkNode(int a, int b, LinkNode* p)
{
	x = a;
	y = b;
	next = p;
}

class path
{
	private:
			int in_x;
			int in_y;
			int **maze;
			LinkNode* first;
			LInkNode* temp;
			loc add[8];
	public:
			path();
			~path();
			void input(int h, int w);
			void push(LinkNode* p);
			LinkNode* pop();
			void search();
}

path::path()
{
	first = new LinkNode();
	temp = first;
	add[0].x = 0;
	add[0].y = -1;
	add[1].x = 0;
	add[1].y = 1;
	add[2].x = 1;
	add[2].y = 0;
	add[3].x = -1;
	add[3].y = 0;
	add[4].x = -1;
	add[4].y = -1;
	add[5].x = -1;
	add[5].y = 1;
	add[6].x = 1;
	add[6].y = -1;
	add[7].x = 1;
	add[7].y = 1;
}
void path::input(int h, int w)
{
	int i;
	int j;

	maze = new int[h];
	for (i=0;i<h;i++)
	{
		maze[i] = new int[w];
	}
	
	for (i=0;i<h;i++)
	{
		for (j=0;j<w;j++)
		{
			cin>>maze[i][j];
			if (maze[i][j]==3)
			{
				in_x = j;
				in_y = i;
			}
		}
	}
}
void push(LinkNode* p)
{
	temp->next =  p;
	temp = p;
}

LinkNode*  pop()
{
	LinkNode* t = first->next;
	first ->next = t->next;
	return t;
}

void search()
{
	
	
int main()
{
	cout<<"the new cpp"<<endl;
	return 0;
}
