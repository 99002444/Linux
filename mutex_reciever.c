#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include<pthread.h>
#define PERMS 0644


pthread_mutex_t lock;

pthread_t tid;

void cal_fine()
{ 
  int fine =4;
  pthread_mutex_lock(&lock); 
  int sum=0;
  
  for(int i=0; i<4;i++)
    { sum = sum + fine;
      printf("Fine for week %d: %d\n", i,sum);
    }
    pthread_mutex_unlock(&lock);
  

  return;

}



struct my_msgbuf {
 long mtype;
 char mtext[200];
};





int main(void) {
 struct my_msgbuf buf;
 int msqid;
 int toend;
 key_t key;

 int fine =4, counter=4;


 
 if ((key = ftok("msgq.txt", 'B')) == -1) {
    perror("ftok");
    exit(1);
   }
 
 msqid = msgget(key, PERMS | IPC_CREAT);

 if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) { /* connect to the queue */
    perror("msgget");
    exit(1);
   }
 
 printf("message queue: ready to receive messages.\n");
 
 for(;;) { 
  
  
  if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
      perror("msgrcv");
      exit(1);
            }

    int sum=0;

  printf("recvd: \"%s\"\n", buf.mtext);

  cal_fine();

  toend = strcmp(buf.mtext,"end");
  
  
  if (toend == 0)
  break;
 }

   

 
 printf("message queue: done receiving messages.\n");
 system("rm msgq.txt");


while (counter >0){
//int errno = pthread_create(&(tid), NULL, cal_fine, NULL);
  if ((pthread_create(&(tid), NULL, cal_fine, NULL))!= 0)
      printf("\nThread creation failed");
    counter = counter-1;
}
    pthread_join(tid, NULL);
    pthread_mutex_destroy(&lock);

    // to destroy the message queue 
	msgctl(msqid, IPC_RMID, NULL); 


 return(0);
}