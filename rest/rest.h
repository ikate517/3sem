#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define TABLE 2 
#define MAX_DISHES_NUM 10
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
