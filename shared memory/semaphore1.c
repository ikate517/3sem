#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING "FIRST STRING"

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
    FILE* file;
	file = fopen("semaphore.txt", "a");
	
    const char pathname[] = "s08e01a.c";

    key_t key;

    if ( (key = ftok(pathname , 0)) < 0 ) 
    {
        printf("Can`t generate key\n");
        exit(-1);
    }

    if ((semid = semget(key , 1 , 0666 | IPC_CREAT)) < 0)
    {
        printf("Can`t get semid\n");
        exit(-1);
    }
    
    semaphore(1);
    
    while (1)
    {
		semaphore(-1);
		fprintf(file, STRING);
		semaphore(1);
	}

    
	fclose(file);
	
	return 0;
}
