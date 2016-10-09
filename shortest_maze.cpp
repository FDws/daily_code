#include <iostream>
using namespace std;

struct loc
{
	int x;
	int y;
};

struct LinkNode
{
	int x;
	int y;
	int lv;
	LinkNode* next;
	LinkNode(int l = 1,int a=0, int b=0,LinkNode* p=NULL);
};

LinkNode::LinkNode(int l, int a, int b, LinkNode* p)
{
	x = a;
	y = b;
	lv = l;
	next = p;
}

class path
{
	private:
			int out_x;
			int out_y;
			int **maze;
			LinkNode* first;
			LinkNode* temp;
			loc add[8];
	public:
			path();
			~path();
			void input(int h, int w);
			void push(LinkNode* p);
			LinkNode* pop();
			void search();
};

path::path()
{
	first = new LinkNode();
	temp = first;
	add[0].x = -1;
	add[0].y = 0;
	add[1].x = -1;
	add[1].y = -1;
	add[2].x = 0;
	add[2].y = -1;
	add[3].x = 1;
	add[3].y = -1;
	add[4].x = 1;
	add[4].y = 0;
	add[5].x = 1;
	add[5].y = 1;
	add[6].x = 0;
	add[6].y = 1;
	add[7].x = -1;
	add[7].y = 1;
}
void path::input(int h, int w)
{
	int i;
	int j;

	out_x = h;
	out_y = w;

	maze = new int*[h];
	for (i=0;i<h;i++)
	{
		maze[i] = new int[w];
	}
	
	for (i=0;i<h;i++)
	{
		for (j=0;j<w;j++)
		{
			cin>>maze[i][j];
		}
	}
	cout<<"Input finish"<<endl;
}
void path::push(LinkNode* p)
{
	temp->next =  p;
	temp = p;
}

LinkNode*  path::pop()
{
	LinkNode* t = first->next;
	if (first->next = temp)
	{
			temp=first;
	}

	first ->next = t->next;
	return t;
}

void path::search()
{
	int i;
	//int j;

	LinkNode* point = new LinkNode(2);
	maze[0][0]=2;
	LinkNode* son;

	//push(point);
	//point = pop();
	
	while(point->x!=out_x-1||point->y!=out_y-1)
	{
		for (i=0;i<8;i++)
		{
			if (point->x+add[i].x<0||point->y+add[i].y<0||point->x+add[i].x==out_x||point->y+add[i].y == out_y) continue;
			cout<<point->x<<" "<<point->y<<"--";
			cout<<point->x+add[i].x<<" "<<point->y+add[i].y<<endl;
			if (first->next) cout<<"==="<<first->next->x<<" "<<first->next->y<<endl;
			if (maze[point->x+add[i].x][point->y+add[i].y]==0)	
			{
				son = new LinkNode(point->lv+1,point->x+add[i].x,point->y+add[i].y);
				maze[point->x+add[i].x][point->y+add[i].y] = point->lv+1;
				push(son);
			}
		}

		delete point;
		point = pop();
	}

	int x=out_x-1;
	int y=out_y-1;
	
	cout<<"("<<x+1<<","<<y+1<<")";

	while(x||y)
	{
		for (i=0;i<8;i++)
		{
			if (x+add[i].x<0||y+add[i].y<0||x+add[i].x == out_x||y+add[i].y==out_y) continue;

			if (maze[x+add[i].x][y+add[i].y]==maze[x][y]-1)
			{
				x = x + add[i].x;
				y = y + add[i].y;
				cout<<"（"<<x<<"，"<<y<<"）";
				break;
			}
		}
	}
}
path::~path()
{
	while(first->next)
	{
		temp = first;
		first = first->next;
		delete temp;
	}
}
	
int main()
{
	int x;
	int y;
	cin>>x>>y;

	path pa;
	pa.input(x,y);
	pa.search();

	return 0;
}
