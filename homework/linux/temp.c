#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(){

	pid_t pid;
	int n;

	pid=fork();
	if(pid<0){
		perror("Fork failed\n");
		exit(1);
	}  
	if (pid==0){
		printf("The pid is : %d\n",getpid());
		printf("The ppid is: %d\n",getppid());
	} else {
		sleep(20);
	}	

	return 0;
}
