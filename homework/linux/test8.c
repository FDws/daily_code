#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>

void mode_to_letter(int mode, char* str){
	str[0]='-';

	if(S_ISDIR(mode)) str[0]='d';
	if(S_ISCHR(mode)) str[0]='c';
	if(S_ISBLK(mode)) str[0]='b';

	if(mode & S_IRUSR) str[1]='r';
	else str[1]='-';

	if(mode & S_IWUSR) str[2]='w';
	else str[2]='-';

	if(mode & S_IXUSR) str[3]='x';
	else str[3]='-';

	if(mode & S_IRGRP) str[4]='r';
	else str[4]='-';

	if(mode & S_IWGRP) str[5]='w';
	else str[5]='-';

	if(mode & S_IXGRP) str[6]='x';
	else str[6]='-';

	if(mode & S_IROTH) str[7]='r';
	else str[7]='-';

	if(mode & S_IWOTH) str[8]='w';
	else str[8]='-';

	if(mode & S_IXOTH) str[9]='x';
	else str[9]='-';

	str[10]='\0';
}

int main(int argc, char* argv[]){
	struct stat fst;
	struct tm* mytime = (struct tm*) malloc(sizeof(struct tm));

	char str[12];

	if(argc!=2){
		fprintf(stderr,"Usage: %s <pathname>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	
	if(stat(argv[1],&fst)==-1){
		perror("stat:");
		exit(EXIT_FAILURE);
	}

	mode_to_letter(fst.st_mode,str);
	printf("%s",str);
	printf(" %lu",fst.st_nlink);
	printf(" %s",getpwuid(fst.st_uid)->pw_name);
	printf(" %s",getgrgid(fst.st_gid)->gr_name);
	printf(" %ld",fst.st_size);
	mytime = localtime(&fst.st_mtime);
	printf(" %d-%02d-%02d %02d:%02d",mytime->tm_year+1900,mytime->tm_mon+1,mytime->tm_mday,mytime->tm_hour,mytime->tm_min);

	printf(" %s",argv[1]);
	printf("\n");

	return 0;
}
