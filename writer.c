#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <errno.h>
#define KEY 10001
#define KEY2 1234
#define SEG_SIZE 200

int writeit() {
  int shmd;
 char * data;
  shmd=shmget(KEY2,1,0);
  data=shmat(shmd,0,0);
  if (data<0) printf("Error shmatting.");
//  else printf("got here %p \n",data);
 if (!(*data)){
   printf("No data to display.");
 }
 else printf("Last added: %s\n",data);
 printf("Add your own: ");
 fgets(data,SEG_SIZE,stdin);
 *strchr(data,'\n')=0;
 shmdt(data);
  return 0;
}

int main(){
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
