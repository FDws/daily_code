#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#define RUN 0
#define END 1
#define WAT 2

typedef struct pcb{
	int id;
	int state;
	int needTime;
	int runTime;
	struct pcb *next;
}PCB;
int print(PCB* p){
	
	printf("The info of the process:");
	printf("ID : %-4d ",p->id);
	printf("NeedTime : %-4d ",p->needTime);
	printf("RunTime : %-4d \n",p->runTime);
	return 0;
}
int over(PCB* p){
	free(p);
	p=NULL;
	return 0;
}
int run(PCB* p){

	PCB* temp;
	while(1){
		p->next->state=RUN;
		usleep(50000);
		p->next->runTime++;
		print(p->next);

		if(p->next->needTime==p->next->runTime){
			p->next->state=END;
			if(p->next==p){
				over(p);
				return 0;
			}else{
				temp=p->next;
				p->next=temp->next;
				over(temp);
			}
		} else {
			p->next->state=WAT;
		}

		p=p->next;
	}
}

PCB* create(int id,int needTime){
	PCB* p = (PCB*)malloc(sizeof(PCB));
	p->id=id;
	p->needTime=needTime;
	p->next=NULL;
	return p;
}
PCB* init(int num){

	int i;
	srand(time(NULL));
	PCB* head=(PCB*)malloc(sizeof(PCB));
	PCB* move;
	PCB* link=head;
	for(i=0;i<num;i++){
		move=create(i,rand()%20+1);
		link->next=move;
		link=move;
		print(move);
	}
	printf("\n\n");
	move->next=head->next;
	over(head);
	return move;
}
int main(){
	int num;
	printf("Please input the num of process:");
	scanf("%d",&num);

	PCB* process=init(num);
	printf("Begin Run......\n");
	run(process);

	printf("Done\n");

	return 0;
}
