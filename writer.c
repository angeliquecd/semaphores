#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
//#include "writer.c"
#define KEY 10001
#define KEY2 1234
#define SEG_SIZE 200

int writeit() {
  int shmd,fd,r;
 char * data;
fd=open("story.txt",O_WRONLY |O_APPEND);
   if (fd<0) printf("Error opening file.\n");
shmd=shmget(KEY2,1,0);
data=shmat(shmd,0,0);
  if (data<0) printf("Error shmatting.");

 if (!(*data)){
   printf("No data to display.\n");
 }
 else printf("Last added: %s\n",data);

 printf("Add your own: ");
 fgets(data,SEG_SIZE,stdin);//takes in input
  *strchr(data,'\n')=' ';
r=write(fd,data,SEG_SIZE);//writes to the file
  if (r<0) printf("Error writing to file.\n");
shmdt(data);//adds new line to shared mem
close(fd);
return 0;
}

int main(){
  int semd;
  semd = semget(KEY, 1, 0);
  struct sembuf sb;
  sb.sem_num = 0;
  //sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;
  semop(semd, &sb, 1);
  //sleep(2);
  writeit();
  sb.sem_op = 1;
  semop(semd, &sb, 1);
  return 0;
}
