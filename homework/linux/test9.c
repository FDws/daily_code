#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/file.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

void LockSet(int fd,int type);

int main(){
	char seat[3];
	int fd;
	int time=0;
	int flag=0;

	while(1){
		printf("--------------------Welcome To Use The Library Seat Booking System--------------------\n");
		printf("\t\t    1----Appointment Seat\n");
		printf("\t\t    2----Relive Seat\n");
		printf("\t\t    3----Exit\n");
		scanf("%d",&flag);

		switch(flag){
			case 1:
				printf("Please input the seat's no. (0~100) and the time(hour):\n");
				scanf("%s %d",seat,&time);
				printf("%s---",seat);
				printf("%d---",time);

				fd = open(seat, O_RDWR | O_CREAT,0777);
				if(fd<0){
					perror("Open failed");
					exit(1);
				}

				LockSet(fd,F_WRLCK);
				break;
			case 2:
				printf("Please input the seat's no. which you want to relive:");
				scanf("%s",seat);

				fd = open(seat, O_RDWR | O_CREAT,0777);
				if(fd<0){
					perror("Open failed");
					exit(1);
				}

				LockSet(fd,F_UNLCK);
				break;
			case 3:
				return 0;
				break;
			default:
				printf("Please input right number");
				break;
		}
	}


	return 0;
}
void LockSet(int fd, int type){
	struct flock lock;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;

	while(1){

		printf("begin lock\n");
		lock.l_type = type;
		if((fcntl(fd, F_SETLK, &lock))==0){
			if(lock.l_type==F_WRLCK){
				printf("\nBook succeed! Please relive when leave\n");
			} else if (lock.l_type==F_UNLCK){
				printf("\nRelive succeed! \n");
			}

			return;
		}

		printf("had lock\n");
		fcntl(fd,F_GETLK,&lock);
		if(lock.l_type!=F_UNLCK){
			if(lock.l_type==F_WRLCK){
				printf("\nThe seat was booked!\n");
				return;
			}
		}
	}
}
