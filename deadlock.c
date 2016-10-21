#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>

struct sembuf mybuf;
int semid;
int i = 0;
void semaphore(int num, int arg) 
{
	if ( arg == -1)
	{	printf("try to lock semaphore %d %d\n", num, i);
	i++;}
	mybuf.sem_flg = 0;
    mybuf.sem_num = num;
	mybuf.sem_op = arg;
	if (semop(semid , &mybuf , 1) < 0) 
	{
		printf("Can`t wait for condition\n");
		exit(-1);
	}
	if ( arg == -1)
		printf("semaphore %d is locked\n", num);
}

void* my_thread1(void* arg) 
{
	while(1)
	{
		semaphore(0, -1);
		semaphore(1, -1);
		semaphore(0, 1);
		semaphore(1, 1);
	}
    return NULL;
}

void* my_thread2(void* arg) 
{
	while (1)
	{
		semaphore(0, -1);
		semaphore(1, -1);
		semaphore(0, 1);
		semaphore(1, 1);
	}
    return NULL;
}

int main()
{	
	const char pathname[] = "sem7.c";

    key_t key;

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
    semaphore(0, 1);
	semaphore(1, 1);
	pthread_t thread_ids[2];
	int result[2];
	int i;
	result[0] = pthread_create(&thread_ids[0], (pthread_attr_t *)NULL, my_thread1, NULL);

	if (result[0]) 
	{
		printf("Can`t create thread, returned value = %d\n" , result[0]);
		exit(-1);
	}
	result[1] = pthread_create(&thread_ids[1], (pthread_attr_t *)NULL, my_thread2, NULL);

	if (result[1]) 
	{
		printf("Can`t create thread, returned value = %d\n" , result[1]);
		exit(-1);
	}
	for(i = 0; i < 2; i++)
    {
		pthread_join(thread_ids[i], (void **) NULL);
	}
	return 0;
}

