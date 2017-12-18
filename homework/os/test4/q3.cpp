#include<iostream>
#include<string>
#include<list>
using namespace std;

typedef struct dir{
	string name;
	dir* father;
	list<dir*> l;
	list<string> file;
	dir(string name,dir* f=NULL){
		this->name=name;
		father=f;
	}
}dir;

class fileSys{
	private:
		dir* root;
		dir* position;
	public:
		fileSys();
		void loop();
		void showCmd();
		void showPath();
		void createDir();
		void createFile();
		void enterDir();
		void showSys();
		void deleteDir();
		void deleteFile();
		~fileSys();
};
fileSys::fileSys(){
	root = new dir("root");
	position=root;
	loop();
}
void fileSys::loop(){
	cout<<"Welcome!"<<endl;
	int flag;
	int exit=0;

	while(!exit){
		showCmd();
		cin>>flag;

		switch(flag){
			case 0:
				exit=1;
				break;
			case 1:
				createDir();
				break;
			case 2:
				createFile();
				break;
			case 3:
				if(position!=root){
					position=position->father;
					showPath();
				}
				break;
			case 4:
				enterDir();
				break;
			case 5:
				showSys();
				break;
			case 6:
				deleteDir();
				break;
			case 7:
				deleteFile();
				break;
			default:
				cout<<"Illegal parameter!"<<endl;
		}
	}
}
void fileSys::showCmd(){
	cout<<"\n--------------------------"<<endl;
	cout<<"1-create  new   dir     2-create new file"<<endl;
	cout<<"3-return parent dir     4-enter child dir"<<endl;
	cout<<"5-show    dir  info"<<endl;
	cout<<"6-delete        dir     7-delete     file"<<endl; 
	cout<<"0-exit"<<endl;
}
void fileSys::showPath(){
	list<string> pa;
	dir* move=position;
	pa.push_front("/"+move->name);
	while(move!=root){
		move=move->father;
		pa.push_front("/"+move->name);
	}
	list<string>::iterator it=pa.begin();
	for(;it!=pa.end();it++){
		cout<<(*it);
	}
	cout<<endl;
}
void fileSys::createDir(){
	string name;
	cout<<"Input the dir name:";
	cin>>name;
	position->l.push_back(new dir(name,position));
	cout<<"Create "<<name<<" succeed!\n"<<endl;
}
void fileSys::createFile(){
	string name;
	cout<<"Input the file name:";
	cin>>name;
	position->file.push_back(name);
	cout<<"Create "<<name<<" succeed!\n"<<endl;
}
void fileSys::enterDir(){
	string name;
	cout<<"Input the dir name:";
	cin>>name;
	list<dir*>::iterator it=position->l.begin();
	for(;it!=position->l.end();it++){
		if((*it)->name==name){
			position=(*it);
			showPath();
			return;
		}
	}
	cout<<"No such dir!"<<endl;
}
void fileSys::showSys(){
	list<dir*>::iterator it=position->l.begin();
	list<string>::iterator it2=position->file.begin();
	int flag=0;
	for(;it!=position->l.end();it++){
		if(flag==0){
			cout<<"Dir :";
			flag=1;
		}
		cout<<" "<<(*it)->name;
	}
	cout<<endl;
	flag=0;
	for(;it2!=position->file.end();it2++){
		if(flag==0){
			cout<<"File:";
			flag=1;
		}
		cout<<" "<<(*it2);
	}
	cout<<endl;
}
void fileSys::deleteDir(){
	string name;
	list<dir*>::iterator it=position->l.begin();
	cout<<"Input the dir name: ";
	cin>>name;
	for (;it!=position->l.end();it++){
		if((*it)->name==name){
			position->l.erase(it);
			cout<<"Delete "<<name<<" succeed!"<<endl;
			return;
		}
	}

	cout<<"No such dir!"<<endl;
}
void fileSys::deleteFile(){
	string name;
	list<string>::iterator it=position->file.begin();
	cout<<"Input the file name: ";
	cin>>name;
	for (;it!=position->file.end();it++){
		if((*it)==name){
			position->file.erase(it);
			cout<<"Delete "<<name<<" succeed!"<<endl;
			return;
		}
	}

	cout<<"No such dir!"<<endl;
}
fileSys::~fileSys(){
	root->l.clear();
	delete root;
}
int main(){
	fileSys* fs = new fileSys();

	return 0;
}
