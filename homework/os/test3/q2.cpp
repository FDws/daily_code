#include<iostream>
#include<cstdlib>
#include<ctime>
#define WORK 1
#define FREE 0
using namespace std;

typedef struct node{
	int status;
	int begin;
	int end;
	node* next;
	node(int status=FREE,int begin=0,int end=0,node* next=NULL){
		this->status=status;
		this->begin=begin;
		this->end=end;
		this->next=next;
	}
}Node;

class storage{
	private:
		int mainSize;
		int* orderList;
		int orderListNum;
		Node* head;
		Node* tail;
		Node* flag;
	public:
		storage(int orderListNum);
		~storage();
		void init();
		void findAddress();
		void insert(int size);
};
storage::storage(int orderListNum){
	this->orderListNum=orderListNum;
	mainSize=1024;

	init();
}
void storage::init(){
	orderList = new int[orderListNum];
	int i;
	srand(time(NULL));
	for(i=0;i<orderListNum;i++){
		orderList[i]=rand()%100+2;
	}
	head=new Node(FREE,0,mainSize);
	tail=head->next;
	flag=head;
}
void storage::findAddress(){
	int i;
	for(i=0;i<orderListNum;i++){
		insert(orderList[i]);
	}
}
void storage::insert(int size){
	Node* move=head;
	while(move){
		if(move->status==FREE&&move->end - move->begin >= size){
			Node* back=new Node(FREE,move->begin+size,move->end,move->next);
			move->status=WORK;
			move->end=move->begin+size;
			move->next=back;
			break;
		}
		move=move->next;
	}

	if(!move){
		if(!flag){
			flag=head;
		}
		if(!(flag->end-flag->begin>=size)){
			while(flag->end-flag->begin<size){
				Node* tem = flag->next;
				if(!tem){
					flag=head;
					continue;
				}
				flag->end=flag->next->end;
				flag->next=tem->next;
				delete tem;
			}
		}
		Node* back=new Node(FREE,flag->begin+size,flag->end,flag->next);
		flag->status=WORK;
		flag->end=flag->begin+size;
		flag->next=back;
		move=flag;
		flag=flag->next;
	}
	cout<<"Insert successed : The size is:"<<size<<"  The begin is:"<<move->begin<<"   The end is:"<<move->end<<endl;
}
int main(){
	int orderListNum;
	cout<<"Input the order's number:"<<endl;
	cin>>orderListNum;

	storage* sto = new storage(orderListNum);
	sto->findAddress();

	return 0;
}
