#include<iostream>
#include<unistd.h>
using namespace std;

int main(){

	clock_t begin = clock();
	usleep(1000000);
	clock_t mid = clock();
	usleep(500000);
	clock_t end = clock();

	cout<<"begin : "<<begin<<endl;
	cout<<"mid   : "<<mid<<endl;
	cout<<"end   : "<<end<<endl;
	cout<<"CL    : "<<CLOCKS_PER_SEC<<endl;
	int i=0;
	for(i=0;i<10;i++){
		usleep(100000);
		cout<<clock()<<" ";
	}
	cout<<endl;
	return 0;
}
