#include<iostream>
#include<cstdlib>
#include<ctime>
#define WORK 1
#define FREE 0
#define PAGESIZE 4096//B
#define MAINLENGTH 1024

using namespace std;

typedef struct Page{
	int id;
	int status;
	int blockNum;
	int innerAddress;
	Page(){
		id=-1;
		status=FREE;
		blockNum=-1;
	}
}Page;
typedef struct Para{
	int id;
	int status;
	int pageTableSize;
	Page* pageTable;
	Para(){
		id=-1;
		status=FREE;
		pageTableSize=-1;
		pageTable=NULL;
	}
}Para;

class storage{
	private:
		int* randBlock;
		int paraTableSize;
		int orderListLength;
		int* orderList;
		Para* paraTable;
	public:
		storage(int orderListLength);
		~storage();
		void init();
		void findAddress();
		void print(int para,int page,int inner);
		int createBlockNum();
};
storage::storage(int orderListLength){
	this->orderListLength=orderListLength;
	paraTableSize=10;
	init();	
}
void storage::findAddress(){
	int i;
	for(i=0;i<orderListLength*3;){
		int para=orderList[i];
		i++;
		int page=orderList[i];
		i++;
		int inner=orderList[i];
		i++;
		print(para,page,inner);
	}
}
void storage::print(int para,int page,int inner){
	cout<<"The information is :"<<endl;
	cout<<"The old address is(Paranum Pagenum innerAddress):"<<para<<" "<<page<<" "<<inner<<endl;
	cout<<"The paragraph table info(id status pageTableSize):"<<paraTable[para].id<<" "<<paraTable[para].status<<" "<<paraTable[para].pageTableSize<<endl;
	cout<<"The pageTable info(id status blockNum):"<<paraTable[para].pageTable[page].id<<" "<<paraTable[para].pageTable[page].status<<" "<<paraTable[para].pageTable[page].blockNum<<endl;
	cout<<"The new address is :"<<paraTable[para].pageTable[page].blockNum*PAGESIZE+inner<<endl;
	cout<<endl;
}
void storage::init(){
	int i;
	randBlock=new int[MAINLENGTH];
	for(i=0;i<MAINLENGTH;i++){
		randBlock[i]=i;
	}

	paraTable = new Para[paraTableSize];
	srand(time(NULL));
	for(i=0;i<paraTableSize;i++){
		paraTable[i].id=i;
		paraTable[i].status=WORK;
		paraTable[i].pageTableSize=rand()%19+1;
		paraTable[i].pageTable=new Page[paraTable[i].pageTableSize];
	}

	int j;
	for(i=0;i<paraTableSize;i++){
		for(j=0;j<paraTable[i].pageTableSize;j++){
			paraTable[i].pageTable[j].id=j;
			paraTable[i].pageTable[j].status=WORK;
			paraTable[i].pageTable[j].blockNum=createBlockNum();
		}
	}

	orderList=new int[orderListLength*3];
	for(i=0;i<orderListLength*3;){
		orderList[i]=rand()%paraTableSize;
		i++;
		orderList[i]=rand()%paraTable[orderList[i-1]].pageTableSize;
		i++;
		orderList[i]=rand()%PAGESIZE;
		i++;
	}
}
int storage::createBlockNum(){
	int num;
	int index;
	srand(time(NULL));
	while(1){
		index=rand()%MAINLENGTH;
		num=randBlock[index];
		if(num!=-1){
			randBlock[index]=-1;
			break;
		}
	}

	return num;
}
storage::~storage(){
	delete [] randBlock;
	delete [] orderList;
	int i;
	for(i=0;i<paraTableSize;i++){
		delete [] paraTable[i].pageTable;
	}
	delete [] paraTable;
}
int main(){
	int orderListLength;
	cout<<"Input the order's length:"<<endl;
	cin>>orderListLength;

	storage* sto = new storage(orderListLength);
	sto->findAddress();
	return 0;
}
