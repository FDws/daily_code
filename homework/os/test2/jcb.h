#ifndef _JCB_H_
#define _JCB_H_
#include<cstring>
#include<ctime>
#define RUN 0
#define WAIT 1
#define FINISH 2
typedef struct JCB{
	char* name;
	int id;
	clock_t commitTime;
	clock_t needTime;
	clock_t waitTime;
	double responseRatio;
	int source;
	int state;
	struct JCB* next;

	JCB (){
		name = new char[3];
		commitTime = 0;
		needTime = 0;
		waitTime = 0;
		responseRatio = 0;
		source = 0;
		state = WAIT;
		next = NULL;
	}
	JCB (int id,int needTime,char* name = NULL){
		this->id = id;
		this->name = new char[3];
		if(name){
			strcpy(this->name,name);
		}
		commitTime = 0;
		this->needTime = needTime;
		waitTime = 0;
		responseRatio = 0;
		source = 0;
		state = WAIT;
		next = NULL;
	}
	JCB(JCB* h){
		id = h->id;
		name = new char[strlen(h->name)];
		strcpy(name,h->name);
		commitTime = h->commitTime;
		needTime = h->needTime;
		waitTime = h->waitTime;
		responseRatio = h->responseRatio;
		source = h->source;
		state = h->state;
		next = NULL;
	}
}JCB;

typedef struct Time{
	clock_t groupStart;
	clock_t groupFinish;
	clock_t groupTurnaroundTime;
	double groupWeightTurnaroundTime;
	Time(){
		groupStart=clock();
		groupFinish = 0;
		groupTurnaroundTime=0;
		groupWeightTurnaroundTime=0;
	}
}Time;
#endif
