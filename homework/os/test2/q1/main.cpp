#include<iostream>
#include<ctime>
#include<cstdlib>
#include<unistd.h>
#include<cstring>
#include"sjf.h"
#include"hrn.h"
#include"fcfs.h"
using namespace std;

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
