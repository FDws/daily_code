#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include"jcb.h"
#include"sjf.h"
/*
**开始运行时刻
**完成时刻
**周转时间
**带权周转时间
**
**平均周转时间
**带权平均周转时间
*/
using namespace std;

//class SJF{
//	private:
//		JCB* head;
//		Time* groupTime;
//		int JCBNum;
//	public:
//		SJF(JCB* h);
//		JCB* create(JCB* old);
//		int run();
//		int sort();
//		int calcWaitTime(JCB* nowRun);
//		int over(JCB* nowRun);
//		int print(JCB* nowRun);
//		~SJF();
//};
SJF::SJF(JCB* h){
	//cout<<"SJF begin"<<endl;
	head = new JCB();
	JCBNum = 0;
	JCB* temp = h;
	JCB* move = head;
	int i=0;

	while(temp!=NULL){
		JCBNum++;
		move->next = create(temp);
		move->next->commitTime = i;
		//cout<<"Committime "<<move->next->commitTime<<endl;
		temp = temp->next;
		move = move -> next;
		i++;
	}
	sort();
	run();
	//cout<<"SJF done"<<endl;
}
int SJF::run(){
	//cout<<"Run begin"<<endl;
	groupTime = new Time();
	while(head->next){
		JCB* nowRun = head->next;
		calcWaitTime(nowRun);

		nowRun->state=RUN;
		usleep(nowRun->needTime*1000);
		nowRun->state=FINISH;
		print(nowRun);

		head->next = nowRun->next;
		over(nowRun);
	}
//	groupTime->groupFinish = clock();
	//cout<<"Run done"<<endl;

	return 0;
}
JCB* SJF::create(JCB* old){
	JCB* New = new  JCB(old);
	return New;
}
int SJF::over(JCB* nowRun){
	delete [] nowRun->name;
	delete nowRun;

	return 0;
}
int SJF::calcWaitTime(JCB* nowRun){
	nowRun->waitTime = clock()-groupTime->groupStart-nowRun->commitTime;
	//cout<<"Calc begin"<<endl;
//	JCB* nextRun = head->next;
//	JCB* move = nextRun->next;
//
//	while(move){
//		move->waitTime = move->waitTime + nextRun->needTime;
//		move->responseRatio = (move->waitTime+move->needTime)/move->needTime;
//		move = move->next;
//	}
//	//cout<<"Calc done"<<endl;
	return 0;
}
int SJF::sort(){
	//cout<<"Sort begin"<<endl;
//	if(head->next == NULL || head->next->next == NULL){
//		return 0;
//	}

	JCB* begin = head;
	JCB* minTime = begin;
	JCB* move = minTime;

	while(begin->next!=NULL){
		move = begin;
		minTime = move;
		while(move->next!=NULL){
			if(move->next->needTime<minTime->next->needTime){
				minTime = move;
			}
			move = move->next;
		}

		if(begin!=minTime){
			JCB* maxNext = minTime->next;
			minTime->next = maxNext->next;

			maxNext->next = begin->next;
			begin->next = maxNext;
		}
		begin = begin->next;
	}
	//cout<<"Sort done"<<endl;

	return 0;
}
int SJF::print(JCB* nowRun){
	//cout<<"Print begin"<<endl;
	clock_t beginTime = nowRun->commitTime+nowRun->waitTime;
	clock_t finishTime = beginTime+nowRun->needTime;
	clock_t turnaroundTime = finishTime-nowRun->commitTime;
	double weightTurnaroundTime = (double)(turnaroundTime)/nowRun->needTime;
	
	cout<<"-----------------The info of the Finished JCB-----------------"<<endl;
	cout<<"ID                      : "<<nowRun->id<<endl;
	cout<<"BeginRunTime            : "<<beginTime<<endl;
	cout<<"needTime                : "<<nowRun->needTime<<endl;
	cout<<"FinishTime              : "<<finishTime<<endl;
	cout<<"turnaroundTime          : "<<turnaroundTime<<endl;
	cout<<"weightedTurnaroundTime  : "<<weightTurnaroundTime<<endl;
	cout<<endl;
//	cout<<"needTime "<<nowRun->needTime<<endl;
//	cout<<"waitTime "<<nowRun->waitTime<<endl;
	//cout<<"Print done"<<endl;
	
	groupTime->groupWeightTurnaroundTime = groupTime->groupWeightTurnaroundTime + weightTurnaroundTime;
	groupTime->groupTurnaroundTime = groupTime->groupTurnaroundTime + turnaroundTime;
	if(nowRun->next==NULL){
		groupTime->groupFinish = finishTime;
	}

	return 0;
}
SJF::~SJF(){
	cout<<"\n\n---------------The SJF groupTime---------------\n "<<endl;
	cout<<"The average time of group turnaround  is       :  "<<(double)groupTime->groupTurnaroundTime/JCBNum<<endl;
	cout<<"The average time of group weight turnaround is :  "<<(double)groupTime->groupWeightTurnaroundTime/JCBNum<<endl;
	cout<<"ALL time is                                    :  "<<groupTime->groupFinish<<endl;
	cout<<"\n\n"<<endl;

	delete groupTime;
	JCB* temp = head;
	while(temp){
		head = head->next;
		delete [] temp->name;
		delete temp;
		temp = head;
	}
}
//JCB* initHome(int n){
//	//cout<<"Init begin"<<endl;
//	n--;
//	srand(time(NULL));
//	JCB* head = new JCB(rand()%50 + 3);
//	JCB* tem = head;
//	while(n){
//		tem->next = new JCB(rand()%50 + 3);
//		tem = tem -> next;
//		n--;
//	}
//	//cout<<"Init done"<<endl;
//	return head;
//}
//int over(JCB* head){
//	JCB* temp = head;
//	while(temp){
//		head = head->next;
//		delete [] temp->name;
//		delete temp;
//		temp = head;
//	}
//	return 0;
//}
//int main(){
//	int n=10;
//	cout<<"Input the number of JCB : ";
//	cin>>n;
//
//	JCB* head = initHome(n);
//	SJF* ff = new SJF(head);
//	ff->sort();
//
//	delete ff;
//	over(head);
//	return 0;
//}
