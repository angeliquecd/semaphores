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
#define KEY 10001
// union semun {
//   int              val;    /* Value for SETVAL */
//   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
//   unsigned short  *array;  /* Array for GETALL, SETALL */
//   struct seminfo  *__buf;  /* Buffer for IPC_INFO
//                               (Linux-specific) */
// };

int main(int argc, char *argsv[]){
  int semd,v,r,q;
if (argsv[1]){
if (strcmp(argsv[1],"-c")==0){
  printf("Creating the semaphore.\n");
  semd=semget(KEY,1, IPC_CREAT | IPC_EXCL | 0644);
  if (semd<0) {
    printf("There was an error. %d\n",semd);
    semd=semget(KEY,1,0);
    v=semctl(semd,0,GETVAL,0);
    printf("semctl returned: %d\n",v);
}
else{
  union semun us;
  us.val=1;
  r=semctl(semd,0,SETVAL,us);
  printf("semctl returned: %d\n",r);
}
  }

if (strcmp(argsv[1],"-r")==0){
  semd=semget(KEY,1,0);
q=semctl(semd, IPC_RMID, 0);
printf("Removing the semaphore.\n");
if (q<0) printf ("error removing");
  }

if (strcmp(argsv[1],"-v")==0){
printf("The story so far:\n");
  }

}
return 0;
}
