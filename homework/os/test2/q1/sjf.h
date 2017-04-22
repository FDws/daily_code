#ifndef _SJF_H_
#define _SJF_H_
#include"jcb.h"

class SJF{
	private:
		JCB* head;
		Time* groupTime;
		int JCBNum;
	public:
		SJF(JCB* h);
		JCB* create(JCB* old);
		int run();
		int sort();
		int calcWaitTime(JCB* nowRun);
		int over(JCB* nowRun);
		int print(JCB* nowRun);
		~SJF();
};
#endif
