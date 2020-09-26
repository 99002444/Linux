/* Filename: msgq_recv.c */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include<semaphore.h>
#define PERMS 0644

sem_t sem;
pthread_t tid;

void cal_fine()
{ 
  int fine =4;
  sem_wait(&sem);
  int sum=0;
  
  for(int i=0; i<4;i++)
    { sum = sum + fine;
      printf("Fine for week %d: %d\n", i,sum);
    }
  sem_post(&sem);
  

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


 sem_init(&sem,0,1);
 
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
 
 for(;;) { /* normally receiving never ends but just to make conclusion 
             /* this program ends wuth string of end */
  
  
  if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
      perror("msgrcv");
      exit(1);
            }

    int sum=0;

  printf("recvd: \"%s\"\n", buf.mtext);
  cal_fine();
  toend = strcmp(buf.mtext,"end");
  
  //void cal_fine()
  //{
    //sem_wait(&sem);
    //for(int i=0; i<4;i++)
      //{ sum = sum + fine;
      //  printf("Fine for week %d: %d\n", i,sum);
    // }
  // sem_post(&sem);

    //return;

  //}
  if (toend == 0)
  break;
 }

   

 
 printf("message queue: done receiving messages.\n");
 system("rm msgq.txt");


while(counter>0){
//int errno = pthread_create(&(tid), NULL, cal_fine, NULL);
  if ((pthread_create(&(tid), NULL, cal_fine, NULL))!= 0)
      printf("\nThread creation failed");
        counter = counter-1;}

        
    pthread_join(tid, NULL);
    sem_destroy(&sem);

    // to destroy the message queue 
	msgctl(msqid, IPC_RMID, NULL); 


 return(0);
}