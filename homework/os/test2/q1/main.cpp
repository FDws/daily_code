#include<iostream>
#include<ctime>
#include<unistd.h>
#include<cstring>
#include"sjf.h"
#include"hrn.h"
#include"fcfs.h"
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
//SJF::SJF(JCB* h){
//	//cout<<"SJF begin"<<endl;
//	head = new JCB();
//	JCBNum = 0;
//	JCB* temp = h;
//	JCB* move = head;
//	groupTime = new Time();
//	groupTime->groupStart = clock();
//
//	while(temp!=NULL){
//		JCBNum++;
//		move->next = create(temp);
//		move->next->commitTime = clock()-groupTime->groupStart;
////		cout<<"Committime "<<move->next->commitTime<<endl;
//		temp = temp->next;
//		move = move -> next;
//	}
//	sort();
//	run();
//	//cout<<"SJF done"<<endl;
//}
//int SJF::run(){
//	//cout<<"Run begin"<<endl;
//	while(head->next){
//		JCB* nowRun = head->next;
//		calcWaitTime(nowRun);
//
//		nowRun->state=RUN;
//		usleep(nowRun->needTime*10000);
//		nowRun->state=FINISH;
//		print(nowRun);
//
//		head->next = nowRun->next;
//		over(nowRun);
//	}
//	//cout<<"Run done"<<endl;
//
//	return 0;
//}
//JCB* SJF::create(JCB* old){
//	JCB* New = new  JCB(old);
//	return New;
//}
//int SJF::over(JCB* nowRun){
//	delete [] nowRun->name;
//	delete nowRun;
//
//	return 0;
//}
//int SJF::calcWaitTime(JCB* nowRun){
//	nowRun->waitTime = clock()-groupTime->groupStart-nowRun->commitTime;
//	//cout<<"Calc begin"<<endl;
////	JCB* nextRun = head->next;
////	JCB* move = nextRun->next;
////
////	while(move){
////		move->waitTime = move->waitTime + nextRun->needTime;
////		move->responseRatio = (move->waitTime+move->needTime)/move->needTime;
////		move = move->next;
////	}
////	//cout<<"Calc done"<<endl;
//	return 0;
//}
//int SJF::sort(){
//	//cout<<"Sort begin"<<endl;
////	if(head->next == NULL || head->next->next == NULL){
////		return 0;
////	}
//
//	JCB* begin = head;
//	JCB* minTime = begin;
//	JCB* move = minTime;
//
//	while(begin->next!=NULL){
//		move = begin;
//		minTime = move;
//		while(move->next!=NULL){
//			if(move->next->needTime<minTime->next->needTime){
//				minTime = move;
//			}
//			move = move->next;
//		}
//
//		if(begin!=minTime){
//			JCB* maxNext = minTime->next;
//			minTime->next = maxNext->next;
//
//			maxNext->next = begin->next;
//			begin->next = maxNext;
//		}
//		begin = begin->next;
//	}
//	//cout<<"Sort done"<<endl;
//
//	return 0;
//}
//int SJF::print(JCB* nowRun){
//	//cout<<"Print begin"<<endl;
//	clock_t beginTime = nowRun->commitTime+nowRun->waitTime;
//	clock_t finishTime = beginTime + nowRun->needTime;
//	clock_t turnaroundTime = finishTime-nowRun->commitTime;
//	clock_t weightTurnaroundTime = (double)(turnaroundTime)/nowRun->needTime;
//	
//	cout<<"-----------------The info of the Finished JCB-----------------"<<endl;
//	cout<<"ID                      : "<<nowRun->id<<endl;
//	cout<<"BeginRunTime            : "<<beginTime<<endl;
//	cout<<"FinishTime              : "<<finishTime<<endl;
//	cout<<"turnaroundTime          : "<<turnaroundTime<<endl;
//	cout<<"weightedTurnaroundTime  : "<<weightTurnaroundTime<<endl;
//	cout<<"needTime "<<nowRun->needTime<<endl;
//	cout<<"waitTime "<<nowRun->waitTime<<endl;
//	//cout<<"Print done"<<endl;
//	
//	groupTime->groupWeightTurnaroundTime = groupTime->groupWeightTurnaroundTime + weightTurnaroundTime;
//	groupTime->groupTurnaroundTime = groupTime->groupTurnaroundTime + turnaroundTime;
//
//	return 0;
//}
//SJF::~SJF(){
//	cout<<"\n\n---------------The SJF groupTime---------------\n "<<endl;
//	cout<<"The average time of group turnaround  is       :  "<<(double)groupTime->groupTurnaroundTime/JCBNum<<endl;
//	cout<<"The average time of group weight turnaround is :  "<<(double)groupTime->groupWeightTurnaroundTime/JCBNum<<endl;
//	cout<<"ALL time is "<<clock()-groupTime->groupStart<<endl;
//	cout<<"\n\n"<<endl;
//
//	delete groupTime;
//	JCB* temp = head;
//	while(temp){
//		head = head->next;
//		delete [] temp->name;
//		delete temp;
//		temp = head;
//	}
//}
//class HRN{
//	private:
//		JCB* head;
//		Time* groupTime;
//		int JCBNum;
//	public:
//		HRN(JCB* h);
//		JCB* create(JCB* old);
//		int run();
//		int sort();
//		int calcResponseRatio();
//		int over(JCB* nowRun);
//		int print(JCB* nowRun);
//		~HRN();
//};
//HRN::HRN(JCB* h){
//	//cout<<"HRN begin"<<endl;
//	groupTime = new Time();
//	head = new JCB();
//	JCBNum = 0;
//	JCB* temp = h;
//	JCB* move = head;
//
//	while(temp!=NULL){
//		JCBNum++;
//		move->next = create(temp);
//		move->next->commitTime = clock()-groupTime->groupStart;
//		temp = temp->next;
//		move = move -> next;
//	}
//	run();
//	//cout<<"HRN done"<<endl;
//}
//int HRN::run(){
//	//cout<<"Run begin"<<endl;
//	while(head->next){
//		JCB* nowRun = head->next;
//		calcResponseRatio();
//		sort();
//
//		nowRun->state=RUN;
//		usleep(nowRun->needTime*10000);
//		nowRun->state=FINISH;
//		print(nowRun);
//
//		head->next = nowRun->next;
//		over(nowRun);
//	}
//	//cout<<"Run done"<<endl;
//
//	return 0;
//}
//JCB* HRN::create(JCB* old){
//	JCB* New = new  JCB(old);
//	return New;
//}
//int HRN::over(JCB* nowRun){
//	delete [] nowRun->name;
//	delete nowRun;
//
//	return 0;
//}
//int HRN::calcResponseRatio(){
//	//cout<<"Calc begin"<<endl;
//	JCB* nextRun = head->next;
//	JCB* move = nextRun->next;
//
//	while(move){
//		move->waitTime = move->waitTime + nextRun->needTime;
//		move->responseRatio = (move->waitTime+move->needTime)/move->needTime;
//		move = move->next;
//	}
//	//cout<<"Calc done"<<endl;
//	return 0;
//}
//int HRN::sort(){
//	//cout<<"Sort begin"<<endl;
//	if(head->next == NULL || head->next->next == NULL){
//		return 0;
//	}
//
//	JCB* begin = head->next;
//	JCB* max = begin;
//	JCB* move = max;
//
//	while(begin->next!=NULL){
//		move = begin;
//		max = move;
//		while(move->next!=NULL){
//			if(move->next->responseRatio>max->next->responseRatio){
//				max = move;
//			}
//			move = move->next;
//		}
//
//		if(begin!=max){
//			JCB* maxNext = max->next;
//			max->next = maxNext->next;
//
//			maxNext->next = begin->next;
//			begin->next = maxNext;
//		}
//		begin = begin->next;
//	}
//	//cout<<"Sort done"<<endl;
//
//	return 0;
//}
//int HRN::print(JCB* nowRun){
//	//cout<<"Print begin"<<endl;
//	clock_t beginTime = nowRun->commitTime+nowRun->waitTime;
//	clock_t finishTime = beginTime + nowRun->needTime;
//	clock_t turnaroundTime = finishTime-nowRun->commitTime;
//	clock_t weightTurnaroundTime = (double)(turnaroundTime)/nowRun->needTime;
//	
//	cout<<"-----------------The info of the Finished JCB-----------------"<<endl;
//	cout<<"ID                      : "<<nowRun->id<<endl;
//	cout<<"BeginRunTime            : "<<beginTime<<endl;
//	cout<<"FinishTime              : "<<finishTime<<endl;
//	cout<<"turnaroundTime          : "<<turnaroundTime<<endl;
//	cout<<"weightedTurnaroundTime  : "<<weightTurnaroundTime<<endl;
//	cout<<"needTime "<<nowRun->needTime<<endl;
//	cout<<"waitTime "<<nowRun->waitTime<<endl;
//	//cout<<"Print done"<<endl;
//	
//	groupTime->groupWeightTurnaroundTime = groupTime->groupWeightTurnaroundTime + weightTurnaroundTime;
//	groupTime->groupTurnaroundTime = groupTime->groupTurnaroundTime + turnaroundTime;
//
//	return 0;
//}
//HRN::~HRN(){
//	cout<<"\n\n---------------The HRN groupTime---------------\n "<<endl;
//	cout<<"The average time of group turnaround  is       :  "<<(double)groupTime->groupTurnaroundTime/JCBNum<<endl;
//	cout<<"The average time of group weight turnaround is :  "<<(double)groupTime->groupWeightTurnaroundTime/JCBNum<<endl;
//	cout<<"ALL time is "<<clock()-groupTime->groupStart<<endl;
//	cout<<"\n\n"<<endl;
//
//	delete groupTime;
//	JCB* temp = head;
//	while(temp){
//		head = head->next;
//		delete [] temp->name;
//		delete temp;
//		temp = head;
//	}
//}
//class FCFS{
//	private:
//		JCB* head;
//		Time* groupTime;
//		int JCBNum;
//	public:
//		FCFS(JCB* h);
//		JCB* create(JCB* old);
//		int run();
////		int sort();
//		int calcWaitTime(JCB* nowRun);
//		int over(JCB* nowRun);
//		int print(JCB* nowRun);
//		~FCFS();
//};
//FCFS::FCFS(JCB* h){
//	//cout<<"FCFS begin"<<endl;
//	groupTime = new Time();
//	head = new JCB();
//	JCBNum = 0;
//	JCB* temp = h;
//	JCB* move = head;
//
//	while(temp!=NULL){
//		JCBNum++;
//		move->next = create(temp);
//		move->next->commitTime = clock()-groupTime->groupStart;
//	//	cout<<"CommitTime "<<move->next->commitTime<<endl;
//		temp = temp->next;
//		move = move -> next;
//	}
//	run();
//	//cout<<"FCFS done"<<endl;
//}
//int FCFS::run(){
//	//cout<<"Run begin"<<endl;
//	while(head->next){
//		JCB* nowRun = head->next;
//		calcWaitTime(nowRun);
////		sort();
//
//		nowRun->state=RUN;
//		usleep(nowRun->needTime*10000);
//		nowRun->state=FINISH;
//		print(nowRun);
//
//		head->next = nowRun->next;
//		over(nowRun);
//	}
//	//cout<<"Run done"<<endl;
//
//	return 0;
//}
//JCB* FCFS::create(JCB* old){
//	JCB* New = new  JCB(old);
//	return New;
//}
//int FCFS::over(JCB* nowRun){
//	delete [] nowRun->name;
//	delete nowRun;
//
//	return 0;
//}
//int FCFS::calcWaitTime(JCB* nowRun){
//	nowRun->waitTime = clock()-groupTime->groupStart-nowRun->commitTime;
//	//cout<<"Calc begin"<<endl;
////	JCB* nextRun = head->next;
////	JCB* move = nextRun->next;
////
////	while(move){
////		move->waitTime = move->waitTime + nextRun->needTime;
////		move->responseRatio = (move->waitTime+move->needTime)/move->needTime;
////		move = move->next;
////	}
//	//cout<<"Calc done"<<endl;
//	return 0;
//}
////int FCFS::sort(){
////	//cout<<"Sort begin"<<endl;
////	if(head->next == NULL || head->next->next == NULL){
////		return 0;
////	}
////
////	JCB* begin = head->next;
////	JCB* max = begin;
////	JCB* move = max;
////
////	while(begin->next!=NULL){
////		move = begin;
////		max = move;
////		while(move->next!=NULL){
////			if(move->next->responseRatio>max->next->responseRatio){
////				max = move;
////			}
////			move = move->next;
////		}
////
////		if(begin!=max){
////			JCB* maxNext = max->next;
////			max->next = maxNext->next;
////
////			maxNext->next = begin->next;
////			begin->next = maxNext;
////		}
////		begin = begin->next;
////	}
////	//cout<<"Sort done"<<endl;
////
////	return 0;
////}
//int FCFS::print(JCB* nowRun){
//	//cout<<"Print begin"<<endl;
//	clock_t beginTime = nowRun->commitTime+nowRun->waitTime;
//	clock_t finishTime = beginTime + nowRun->needTime;
//	clock_t turnaroundTime = finishTime-nowRun->commitTime;
//	clock_t weightTurnaroundTime = (double)(turnaroundTime)/nowRun->needTime;
//	
//	cout<<"-----------------The info of the Finished JCB-----------------"<<endl;
//	cout<<"ID                      : "<<nowRun->id<<endl;
//	cout<<"BeginRunTime            : "<<beginTime<<endl;
//	cout<<"FinishTime              : "<<finishTime<<endl;
//	cout<<"turnaroundTime          : "<<turnaroundTime<<endl;
//	cout<<"weightedTurnaroundTime  : "<<weightTurnaroundTime<<endl;
//	cout<<"needTime "<<nowRun->needTime<<endl;
//	cout<<"wait time "<<nowRun->waitTime<<endl;
//	
//	groupTime->groupWeightTurnaroundTime = groupTime->groupWeightTurnaroundTime + weightTurnaroundTime;
//	groupTime->groupTurnaroundTime = groupTime->groupTurnaroundTime + turnaroundTime;
//
//	return 0;
//}
//FCFS::~FCFS(){
//	cout<<"\n\n---------------The FCFS groupTime---------------\n "<<endl;
//	cout<<"The average time of group turnaround  is       :  "<<(double)groupTime->groupTurnaroundTime/JCBNum<<endl;
//	cout<<"The average time of group weight turnaround is :  "<<(double)groupTime->groupWeightTurnaroundTime/JCBNum<<endl;
//	cout<<"ALL time is "<<clock()-groupTime->groupStart<<endl;
//	cout<<"\n\n"<<endl;
//
//	delete groupTime;
//	JCB* temp = head;
//	while(temp){
//		head = head->next;
//		delete [] temp->name;
//		delete temp;
//		temp = head;
//	}
//}
JCB* initHome(int n){
	//cout<<"Init begin"<<endl;
	int i=0;
	srand(time(NULL));
	JCB* head = new JCB(i,rand()%20 + 3);
	JCB* tem = head;
	i++;
	while(i<n){
		tem->next = new JCB(i,rand()%20 + 3);
		tem = tem -> next;
		i++;
	}
	//cout<<"Init done"<<endl;
	return head;
}
int over(JCB* head){
	JCB* temp = head;
	while(temp){
		head = head->next;
		delete [] temp->name;
		delete temp;
		temp = head;
	}
	return 0;
}
int main(){
	int n=10;
	cout<<"Input the number of JCB : ";
	cin>>n;

	JCB* head = initHome(n);

	cout<<"\n********************************HRN*********************************"<<endl;
	HRN* hrn = new HRN(head);
	cout<<"\n*******************************FCFS*********************************"<<endl;
	FCFS* fcfs = new FCFS(head);
	cout<<"\n********************************SJF*********************************"<<endl;
	SJF* sjf = new SJF(head);
	
	delete hrn;
	delete fcfs;
	delete sjf;

	over(head);
	return 0;
}
