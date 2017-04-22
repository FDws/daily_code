#include"jcb.h"
#include<iostream>
#include<unistd.h>
#include<cstdlib>
using namespace std;

class fcfs_multi{
	private:
		JCB* backHead;
		JCB* runHead;
		Time* groupTime;
		int resource;
		int allNum;
	public:
		fcfs_multi(int num, int resourceNum);
		void create();
		void run();
		void select();
		void destory(JCB* jcb);
		void disp(JCB* head);
		~fcfs_multi();
};
fcfs_multi::fcfs_multi(int num, int resourceNum){
	this->allNum = num;
	this->resource = resourceNum;

	backHead = new JCB();
	runHead = new JCB();
	runHead->next = runHead;
	create();
}
void fcfs_multi::create(){
	JCB* move = backHead;
	srand(time(NULL));
	int i;
	int stepLen = resource/4*3 + 1;

	for(i=0;i<allNum;i++){
		move->next = new JCB(i,rand()%50+2,rand()%stepLen+1);
		move = move->next;
	}
}
void fcfs_multi::disp(JCB* head){
	JCB* move = head->next;
	while(move && head!=move){
		cout<<" ID                           : "<<move->id<<endl;
		cout<<" Number of resources required : "<<move->resource<<endl;
		cout<<" Number of time required      : "<<move->needTime<<endl;
		cout<<" Number of system resources   : "<<resource<<endl;
		cout<<endl;
		move = move->next;
	}
}
void fcfs_multi::select(){
	int usingResource = 0;
	JCB* temp = runHead->next;
	while(temp!=runHead){
		usingResource = usingResource + temp->resource;
		temp = temp->next;
	}

	temp = backHead;
	while(usingResource<=resource && temp->next){
		if(usingResource+temp->next->resource<=resource){
			JCB* insert = temp->next;
			temp->next = insert->next;
			insert->next = runHead->next;
			runHead->next = insert;
			usingResource = usingResource + insert->resource;
		} else {
			temp = temp->next;
		}
	}
}
void fcfs_multi::run(){
	JCB* move = runHead;
	int done = 0;
	while(backHead->next ||  runHead->next!=runHead){
		select();
		cout<<"*************** Running Queue ***************"<<endl;
		disp(runHead);
		cout<<"*************** Backup  Queue ***************"<<endl;
		disp(backHead);
		done = 0;

		while(runHead->next!=runHead && !done){
			if(move->next==runHead){
				move = runHead;
			} else {
				move = move->next;
			}

			move->next->needTime--;
			if(move->next->needTime==0){
				done = 1;
			}
		}
		JCB* des = move->next;
		move->next = des->next;
		des->next = NULL;
		destory(des);
	}
}
void fcfs_multi::destory(JCB* jcb){
	cout<<"Finished Homework"<<endl;
	cout<<"  ID    : "<<jcb->id<<endl;
	cout<<endl;
	delete jcb;
	jcb = NULL;
}
fcfs_multi::~fcfs_multi(){
	delete runHead;
	delete backHead;
	runHead = NULL;
	backHead = NULL;
}

int main(){
	int num;
	int resource;
	cout<<"Input the number of homework:";
	cin>>num;
	cout<<"Input the number of system resource:";
	cin>>resource;
	fcfs_multi* homework = new fcfs_multi(num,resource);
	homework->run();

	return 0;
}
