#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>

#define N 2

struct sembuf mybuf;
int semid;

void semaphore(int arg) 
{
	mybuf.sem_flg = 0;
    mybuf.sem_num = 0;
	mybuf.sem_op = arg;
	if (semop(semid , &mybuf , 1) < 0) 
	{
		printf("Can`t wait for condition\n");
		exit(-1);
	}
}

int main()
{
	int msqid;
	int pid; 
	pid_t p;
	char pathname[] = "client-server.c"; 

	key_t key; 

	int len, maxlen; 
	int answer;

	struct mymsgbuf
	{
		long mtype;
		struct
		 {
			int a;
			int b;
			int pid;
		} info;
	} mybuf;


	if ( (key = ftok(pathname , 0)) < 0 ) 
    {
        printf("Can`t generate key\n");
        exit(-1);
    }

    if ((semid = semget(key , 2 , 0666 | IPC_CREAT)) < 0)
    {
        printf("Can`t get semid\n");
        exit(-1);
    }

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
	semaphore(N);
	while (1)
	{
		maxlen = sizeof(mybuf.info);

		if ((len = msgrcv(msqid, (struct msgbuf *)&mybuf, maxlen, 1, 0)) < 0)
		{
		printf("Can\'t receive message from queue\n");
		exit(-1);
		}
		semaphore(-1);
		p = fork();
		if (p == 0)
		{
			answer = mybuf.info.a * mybuf.info.b;
			sleep(10);
			pid = mybuf.info.pid;
			mybuf.info.a = answer;
			mybuf.mtype = pid;
			len = sizeof(mybuf.info);

			if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0)
			{
				printf("Can\'t send message to queue\n");
				msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
				exit(-1);
			}
			semaphore(1);
			exit(0);
		}
	}

  return 0;
} 
