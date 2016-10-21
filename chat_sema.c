#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>

struct sembuf mybuf;
int semid;

void semaphore(int arg, int num) 
{
	mybuf.sem_flg = 0;
    mybuf.sem_num = num;
	mybuf.sem_op = arg;
	if (semop(semid , &mybuf , 1) < 0) 
	{
		printf("Can`t wait for condition\n");
		exit(-1);
	}
}
int main()
{
	const char pathname[] = "sem6-7.c";

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
	int fd[2], result;
	int answer = 0, x, y;
    ssize_t size;
    
    if (pipe(fd) < 0) 
    {
        printf("Can`t create pipe");
        exit(-1);
    }
     semaphore(1, 1);
    result = fork();
    if (result > 0)
		{
			while(1)
			{
				x = rand() % 10;
				y = rand() % 10;
				write(fd[1], &x, sizeof(x));
				write(fd[1], &y, sizeof(y));
				semaphore(-1, 0);
				read(fd[0], &answer, sizeof(answer));
				printf("ans = %d\n", answer);
				sleep(1);
				semaphore(1, 1);
			}
		}
		else
		{
			while(1)
			{
				int a, b;
				semaphore(-1, 1);
				read(fd[0], &a, sizeof(a));
				read(fd[0], &b, sizeof(b));
				printf("x = %d   y = %d   \n", a, b);
				answer = a + b;
				write(fd[1], &answer, sizeof(answer));
				semaphore(1, 0);
			}
		}
		
	return 0;
}
