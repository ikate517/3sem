#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int x1, x2;
	x1 = rand() % 10;
	x2 = rand() % 10;
  int msqid; 

  char pathname[] = "client-server.c"; 

  key_t key; 

  int len, maxlen; 

  struct mymsgbuf
  {
    long mtype;
    struct {
		int a;
		int b;
		int pid;
	} info;
  } mybuf;

  if((key = ftok(pathname, 0)) < 0)
  {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
  {
    printf("Can\'t get msqid\n");
    exit(-1);
  }

  mybuf.mtype = 1;
  mybuf.info.a = x2;
  mybuf.info.b = x1;
  mybuf.info.pid = getpid();
  len = sizeof(mybuf.info);

  if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0)
  {
	printf("Can\'t send message to queue\n");
	msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
	exit(-1);
   }
  int pid = getpid();
  maxlen = sizeof(mybuf.info);

    if ((len = msgrcv(msqid, (struct msgbuf *)&mybuf, maxlen, pid, 0)) < 0)
    {
      printf("Can\'t receive message from queue\n");
      exit(-1);
    }
	printf("message type = %ld, info = %d a = %d b = %d\n", mybuf.mtype, mybuf.info.a, x1, x2);
  return 0;
} 

