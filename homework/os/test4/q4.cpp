#include<iostream>
#include<string>
#include<list>
using namespace std;

typedef struct Major{
	string name;
	int num;
	Major(string name,int num=100){
		this->name = name;
		this->num = num;
	}
	void show(){
		cout<<" '---Major: "<<name<<endl;
	}
}Major;

typedef struct College{
	string name;
	list<Major*> l;
	College(string name){
		this->name = name;
	}
	void addMajor(){
		string na;
		cout<<"Input the major's name:";
		cin>>na;
		//cout<<"Input the num of students:";
		//int n;
		//cin>>n;
		l.push_back(new Major(na));
		cout<<"Create "<<na<<" succeed!"<<endl;
	}
	void deleteMajor(){
		string na;
		list<Major*>::iterator it = l.begin();
		cout<<"Input the major's name:";
		cin>>na;
		for(;it!=l.end();it++){
			if((*it)->name==na){
				l.erase(it);
				cout<<"Delete "<<na<<" succeed!"<<endl;
				return;
			}
		}

		cout<<"No such major!"<<endl;
	}
	void showInfo(){
		cout<<"College: "<<name<<endl;
		list<Major*>::iterator it = l.begin();
		for(;it!=l.end();it++){
			(*it)->show();
		}
	}
}College;

class nwsuaf{
	private:
		list<College*> col;
		College* now;
		string bufName;
	public:
		nwsuaf();
		void loop();
		void showCmd();
		void showInfo();
		void changeCollege(int flag);
		void addCollege();
		void addMajor();
		void deleteMajor();
		void deleteCollege();
		~nwsuaf();
};
nwsuaf::nwsuaf(){
	now=NULL;
	loop();
}
void nwsuaf::loop(){
	int exit=0;
	int flag;
	cout<<"Welcome!\n"<<endl;
	while(!exit){
		showCmd();
		cin>>flag;

		switch(flag){
			case 0:
				exit=1;
				break;
			case 1:
				addCollege();
				break;
			case 2:
				deleteCollege();
				break;
			case 3:
				addMajor();
				break;
			case 4:
				deleteMajor();
				break;
			case 5:
				showInfo();
				break;
			default:
				cout<<"Illege parameter!"<<endl;
		}
	}
}
void nwsuaf::showCmd(){
	cout<<"\n------------------------------"<<endl;
	cout<<"1-Add College        2-Delete College"<<endl;
	cout<<"3-Add Major          4-Delete Major"<<endl;
	cout<<"5-Show Info          "<<endl;
	cout<<"0-exit"<<endl;
}
void nwsuaf::showInfo(){
	list<College*>::iterator it=col.begin();
	for(;it!=col.end();it++){
		(*it)->showInfo();
	}
}
void nwsuaf::changeCollege(int flag=0){
	now=NULL;
	cout<<"Input the college name:";
	cin>>bufName;
	list<College*>::iterator it = col.begin();
	for(;it!=col.end();it++){
		if((*it)->name==bufName){
			if(flag){
				col.erase(it);
				cout<<"Delete "<<bufName<<" succeed!"<<endl;
				return;
			} else {
				now = (*it);
			}
			return;
		}
	}
	if(flag){
		cout<<"No such college"<<endl;
	}
}
void nwsuaf::addCollege(){
	changeCollege();
	if(now){
		cout<<"The college already exists!"<<endl;
	} else {
		col.push_back(new College(bufName));
		cout<<"Add "<<bufName<<" succeed!"<<endl;
	}
}
void nwsuaf::deleteCollege(){
	changeCollege(1);
}
void nwsuaf::addMajor(){
	changeCollege();

	if(now){
		now->addMajor();
	} else {
		cout<<"No such college!"<<endl;
	}
}
void nwsuaf::deleteMajor(){
	changeCollege();
	if(now){
		now->deleteMajor();
	} else {
		cout<<"No such college!"<<endl;
	}
}
nwsuaf::~nwsuaf(){
	col.clear();
}
int main(){
	nwsuaf* nw=new nwsuaf();

	return 0;
}
