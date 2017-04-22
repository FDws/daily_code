#ifndef _FCFS_H_
#define _FCFS_H_
#include"jcb.h"
	
class FCFS{
	private:
		JCB* head;
		Time* groupTime;
		int JCBNum;
	public:
		FCFS(JCB* h);
		JCB* create(JCB* old);
		int run();
		int calcWaitTime(JCB* nowRun);
		int over(JCB* nowRun);
		int print(JCB* nowRun);
		~FCFS();
};
#endif
