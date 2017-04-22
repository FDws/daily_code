#ifndef _HRN_H_
#define _HRN_H_
#include"jcb.h"

class HRN{
	private:
		JCB* head;
		Time* groupTime;
		int JCBNum;
	public:
		HRN(JCB* h);
		JCB* create(JCB* old);
		int run();
		int sort();
		int calcResponseRatio();
		int over(JCB* nowRun);
		int print(JCB* nowRun);
		~HRN();
};
#endif
