#include<iostream>
#include<string>
#include<list>
using namespace std;

typedef struct file{
	string filename;
	string rwx;
	string content;
	file(string fn,string r){
		filename=fn;
		rwx=r;
	}
}file;

typedef struct dir{
	string name;
	list<file*> fileList;
	dir(string name){
		this->name=name;
	}
}dir;

class fileSys{
	private:
		list<dir*> home;
		dir* position;
		file* nowFile;
		string bufFilename;
	public:
		fileSys();
		void loop();
		void inSys(string name);
		void showCmd();
		void showFile();
		void openFile();
		void createFile();
		void readFile();
		void writeFile();
		void renameFile();
		void closeFile();
		void deleteFile();
		void changePermission();
		~fileSys();
};
fileSys::fileSys(){
	position=NULL;
	nowFile=NULL;
	loop();
}
void fileSys::loop(){
	string username;
	int exit=0;
	int changeUser=0;
	int flag;
	while(!exit){
		position=NULL;
		changeUser=0;
		cout<<"1-I'm old user    2-I'm new user  0-exit"<<endl;
		cin>>flag;
		if(flag==0){
			break;
		} else if(flag!=1 && flag!=2){
			cout<<"Illegal parameter!!"<<endl;
			continue;
		}
		cout<<"Input the username:";
		cin>>username;

		if (flag==2){
			home.push_back(new dir(username));
			cout<<"Create user "<< username<<" succeed!"<<endl;
		}

		inSys(username);
		if(!position){
			cout<<"No such user!"<<endl;
			continue;
		}
		while(!changeUser){
			showCmd();
			cin>>flag;
			if(!flag){
				exit=1;
				break;
			}
			switch(flag){
				case 1:
					openFile();
					createFile();
					break;
				case 2:
					openFile();
					readFile();
					break;
				case 3:
					openFile();
					writeFile();
					break;
				case 4:
					deleteFile();
					break;
				case 5:
					openFile();
					changePermission();
					break;
				case 6:
					changeUser=1;
					break;
				case 7:
					showFile();
					break;
				case 8:
					openFile();
					renameFile();
					break;
				default:
					cout<<"Illegal parameter!!"<<endl;
					continue;
			}
		}
	}
	cout<<"Bye  "<<endl;
}
void fileSys::inSys(string name){
	list<dir*>::iterator it=home.begin();
	for(;it!=home.end();it++){
		if((*it)->name==name){
			position=(*it);
		}
	}
}

void fileSys::showCmd(){
	cout<<"\n------------------------------------------"<<endl;
	cout<<"1-create  new   file       2-read   file "<<endl;
	cout<<"3-write   to    file       4-delete file"<<endl;
	cout<<"5-change  permission       6-change user"<<endl;
	cout<<"7-show    all   file       8-rename file"<<endl;
	cout<<"0-exit"<<endl;
}
void fileSys::showFile(){
	list<file*>::iterator it=position->fileList.begin();
	for(;it!=position->fileList.end();it++){
		cout<<"Name:"<<(*it)->filename<<"  (rwx)"<<(*it)->rwx<<"   Length:"<<(*it)->content.length()<<endl;
	}
}
void fileSys::openFile(){
	nowFile=NULL;
	cout<<"Input the file name:";
	cin>>bufFilename;
	file* f;

	list<file*>::iterator it=position->fileList.begin();
	for(;it!=position->fileList.end();it++){
		if((*it)->filename==bufFilename){
			nowFile=*it;
			break;
		}
	}
}
void fileSys::createFile(){
	string rwx="110";
	if(nowFile){
		cout<<"The file already exists!"<<endl;
		return;
	}
	file* f=new file(bufFilename,rwx);
	position->fileList.push_back(f);
	cout<<"Create "<<bufFilename<<" succeed!"<<endl;
}
void fileSys::readFile(){
   	if (nowFile){
		if(nowFile->rwx[0]=='0'){
			cout<<"You don't have the read permission!"<<endl;
		} else {
			cout<<"\n"<<nowFile->content<<"\n"<<endl;
		} 
	} else {
		cout<<"No such file!"<<endl;
	}
}
void fileSys::writeFile(){
	if (nowFile){
		if(nowFile->rwx[1]=='0'){
			cout<<"You don't have the write permission!"<<endl;
		}  else {
			string newContent;
			cout<<"Input the content:";
			cin>>newContent;
			nowFile->content=nowFile->content+newContent;
			cout<<"\nWrite succeed!"<<endl;
		}	
	} else {
		cout<<"No such file!"<<endl;
	}
}
void fileSys::deleteFile(){
	nowFile=NULL;
	cout<<"Input the file name:";
	cin>>bufFilename;
	file* f;
	int flag=0;

	list<file*>::iterator it=position->fileList.begin();
	for(;it!=position->fileList.end();it++){
		if((*it)->filename==bufFilename){
			position->fileList.erase(it);
			flag=1;
			break;
		}
	}
	if(flag){
		cout<<"Delete succeed!"<<endl;
	} else {
		cout<<"No such file!"<<endl;
	}
}
void fileSys::changePermission(){

	if(nowFile){
		string newp;
		cout<<"Input the new permission:";
		cin>>newp;
		nowFile->rwx=newp;
	} else {
		cout<<"No such file!"<<endl;
	}
}
void fileSys::renameFile(){
	if(nowFile){
		string newName;
		cout<<"Input the new file name:";
		cin>>newName;
		nowFile->filename=newName;
		cout<<bufFilename<<" --> "<<newName<<endl;
		cout<<"Rename succeed!"<<endl;
	} else {
		cout<<"No such file!"<<endl;
	}
}
fileSys::~fileSys(){
	list<dir*>::iterator it=home.begin();
	for(;it!=home.end();it++){
		(*it)->fileList.clear();
	}
}
int main(){
	fileSys* fs = new fileSys();

	return 0;
}
