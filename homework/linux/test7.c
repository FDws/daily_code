#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
	char ls1[]="ls1";
	char ls2[]="ls2";	

	int flag1 = symlink("/home/wshuo/.vimrc",ls1);
	int flag2 =	link("/home/wshuo/.vimrc",ls2);
	
	return 0;
}
