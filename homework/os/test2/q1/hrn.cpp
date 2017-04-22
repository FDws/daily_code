#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include"jcb.h"
#include"hrn.h"
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

HRN::HRN(JCB* h){
	head = new JCB();
	JCBNum = 0;
	JCB* temp = h;
	JCB* move = head;
	int i=0;

	while(temp!=NULL){
		JCBNum++;
		move->next = create(temp);
		move->next->commitTime = i;
		temp = temp->next;
		move = move -> next;
		i++;
	}
	run();
}
int HRN::run(){
	groupTime = new Time();
	while(head->next){
		JCB* nowRun = head->next;

		nowRun->state=RUN;
		usleep(nowRun->needTime*1000);
		nowRun->state=FINISH;
		print(nowRun);

		calcResponseRatio();
		sort();
		head->next = nowRun->next;
		over(nowRun);
	}

	return 0;
}
JCB* HRN::create(JCB* old){
	JCB* New = new  JCB(old);
	return New;
}
int HRN::over(JCB* nowRun){
	delete [] nowRun->name;
	delete nowRun;

	return 0;
}
int HRN::calcResponseRatio(){
	JCB* nextRun = head->next;
	JCB* move = nextRun->next;

	while(move){
		move->waitTime = clock()-groupTime->groupStart-move->commitTime	+ nextRun->needTime;
		move->responseRatio = (move->waitTime+move->needTime)/move->needTime;
		move = move->next;
	}
	return 0;
}
int HRN::sort(){
	usleep(1000);
	if(head->next == NULL || head->next->next == NULL){
		return 0;
	}

	JCB* begin = head->next;
	JCB* max = begin;
	JCB* move = max;

	while(begin->next!=NULL){
		move = begin;
		max = move;
		while(move->next!=NULL){
			if(move->next->responseRatio>max->next->responseRatio){
				max = move;
			}
			move = move->next;
		}

		if(begin!=max){
			JCB* maxNext = max->next;
			max->next = maxNext->next;

			maxNext->next = begin->next;
			begin->next = maxNext;
		}
		begin = begin->next;
	}

	return 0;
}
int HRN::print(JCB* nowRun){
	clock_t beginTime = nowRun->commitTime+nowRun->waitTime;
	clock_t finishTime = beginTime + nowRun->needTime;
	clock_t turnaroundTime = finishTime-nowRun->commitTime;
	double weightTurnaroundTime = (double)turnaroundTime/nowRun->needTime;
	
	cout<<"-----------------The info of the Finished JCB-----------------"<<endl;
	cout<<"ID                      : "<<nowRun->id<<endl;
	cout<<"BeginRunTime            : "<<beginTime<<endl;
	cout<<"needTime                : "<<nowRun->needTime<<endl;
	cout<<"FinishTime              : "<<finishTime<<endl;
	cout<<"turnaroundTime          : "<<turnaroundTime<<endl;
	cout<<"weightedTurnaroundTime  : "<<weightTurnaroundTime<<endl;
	cout<<endl;
	
	groupTime->groupWeightTurnaroundTime = groupTime->groupWeightTurnaroundTime + weightTurnaroundTime;
	groupTime->groupTurnaroundTime = groupTime->groupTurnaroundTime + turnaroundTime;
	if(nowRun->next==NULL){
		groupTime->groupFinish = finishTime;
	}

	return 0;
}
HRN::~HRN(){
	cout<<"\n\n---------------The HRN groupTime---------------\n "<<endl;
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
