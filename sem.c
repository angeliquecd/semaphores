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
#define STORY "story.txt"
union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
                              (Linux-specific) */
};

int main(int argc, char *argsv[]){
  int semd,v,r,q,shmd,fd;
  char * data;
if (argsv[1]){

if (strcmp(argsv[1],"-c")==0){
  printf("Creating the semaphore.\n");
  semd=semget(KEY,1, IPC_CREAT | IPC_EXCL | 0644);

  printf("Creating the shared memory.\n");
  shmd=shmget(KEY2,SEG_SIZE, IPC_CREAT | 0644);
  data=shmat(shmd,0,0);

  printf("Creating the file.\n");
  fd=open(STORY,O_CREAT | O_TRUNC, 0644);

  if (fd<0) printf("Error opening file.\n");
  if (shmd<0) printf("Error opening shared memory.\n");
  if (semd<0) {
    printf("There was an error. %d\n",semd);
    semd=semget(KEY,1,0);
    v=semctl(semd,0,GETVAL,0);
  //  printf("semctl returned: %d\n",v);
}
else{
  union semun us;
  us.val=1;
  r=semctl(semd,0,SETVAL,us);
//  printf("Semctl returned: %d\n",r);
}
close(fd);
  }

if (strcmp(argsv[1],"-r")==0){
printf("Printing the entire story: \n");
fd=open(STORY,O_RDONLY);
  if (fd<0) printf("Error opening file.\n");
char buff[SEG_SIZE];
while(read(fd,buff,SEG_SIZE)>=SEG_SIZE){
  printf("%s",buff);
}
printf("\n");

semd=semget(KEY,1,0);
q=semctl(semd, IPC_RMID, 0);
printf("Semaphore released.\n");
if (q<0) printf ("Error removing semaphore\n");

shmd=shmget(KEY2,1,0);
q=shmctl(shmd,IPC_RMID,0);
printf("Shared memory released.\n");
if (q<0) printf ("Error removing shared memory.\n");

close(fd);
printf("File closed.\n");
if (fd<0) printf("Error closing the file.\n");

  }

if (strcmp(argsv[1],"-v")==0){
printf("The story so far: ");
fd=open(STORY,O_RDONLY);
  if (fd<0) printf("Error opening file.\n");
char buff[SEG_SIZE];
while(read(fd,buff,SEG_SIZE)>=SEG_SIZE){
  printf("%s",buff);
}
printf("\n");
  //if (r<0) printf("Error reading from the file.\n");
close(fd);
  }

}
return 0;
}
