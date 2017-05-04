#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

typedef struct pageTable{
	int pageNum;
	int blockNum;
	struct pageTable* next;
	pageTable(int pn=-1,int bn=-1,pageTable* n=NULL){
		pageNum=pn;
		blockNum=bn;
		next=n;
	}
}pageTable;

class storage{

	private:
		int pageTableLength;
		int mainStorageBlockNum;
		int listLength;
		int sizeOfOnePage;
		int* randNumList;
		pageTable* table;
	public:
		storage(int listLength=100);
		void init();
		void findAddress();
		int inPageTable(int address);
		void importPage(int address);
		void printPageTable(int orderAddress);
		~storage();
};
storage::storage(int listLength){
	pageTableLength=10;
	mainStorageBlockNum=1024;
	sizeOfOnePage=1024;
	this->listLength=listLength;
	init();
}
void storage::init(){

	table=new pageTable[pageTableLength];

	int i;
	srand(time(NULL));
	randNumList = new int[listLength];
	for(i=0;i<listLength;i++){
		randNumList[i]=rand()%(mainStorageBlockNum*sizeOfOnePage);
	}
}
void storage::printPageTable(int orderAddress){
	cout<<"The orderAddress is : "<<orderAddress<<endl;
	cout<<"The pageTableNum is : "<<orderAddress/sizeOfOnePage<<endl;
	cout<<"The pageTable's information is : "<<endl;
	cout<<"PageNnum     "<<"BlockNum"<<endl;
	int i;
	for(i=0;i<pageTableLength;i++){
		printf("%4d         %7d\n",table[i].pageNum,table[i].blockNum);
	}
	cout<<endl;
}
void storage::findAddress(){
	int i;
	int fistImport=0;
	for(i=0;i<listLength;i++){
		int address=randNumList[i];
		if(!inPageTable(address)){
			table[fistImport].pageNum=address/sizeOfOnePage;
			table[fistImport].blockNum=rand()%mainStorageBlockNum;
			fistImport++;
			fistImport=fistImport%pageTableLength;
		}
		printPageTable(address);
	}
}
int storage::inPageTable(int address){
	int i;
	for(i=0;i<pageTableLength;i++){
		if(table[i].pageNum==address%sizeOfOnePage){
			return 1;
		}
	}
	return 0;
}
storage::~storage(){
	delete [] randNumList;
	delete [] table;
}
int main(){
	int orderNum;
	cout<<"Input the order's number:"<<endl;
	cin>>orderNum;
	
	storage* sto=new storage(orderNum);
	sto->findAddress();

	return 0;
}
