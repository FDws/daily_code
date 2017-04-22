#include<iostream>
#include<cstdlib>
#include<unistd.h>
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

SJF::SJF(JCB* h){
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
int SJF::run(){
	groupTime = new Time();
	while(head->next){
		JCB* nowRun = head->next;

		nowRun->state=RUN;
		usleep(nowRun->needTime*1000);
		nowRun->state=FINISH;
		print(nowRun);

		calcWaitTime(nowRun);
		sort();
		head->next = nowRun->next;
		over(nowRun);
	}
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
	if(nowRun->next==NULL){
		return 0;
	}
	nowRun->next->waitTime = clock()-groupTime->groupStart-nowRun->next->commitTime;
	return 0;
}
int SJF::sort(){
	JCB* begin = head->next;
	JCB* minTime = begin;
	JCB* move = minTime;
	usleep(5000);

	while(begin && begin->next){
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

	return 0;
}
int SJF::print(JCB* nowRun){
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
