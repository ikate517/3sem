#include "restaurant.h"

int main()
{
	char pathname[] = "restaurant.c"; 

	key_t key; 
	int len;
	int msqid;

	if((key = ftok(pathname, 0)) < 0)
	{
		printf("Can\'t generate key\n");
		exit(-1);
	}
	if ((semid = semget(key , 1 , 0666 | IPC_CREAT)) < 0)
    {
        printf("Can`t get semid\n");
        exit(-1);
    }
	FILE *cleaner = fopen("cleaner.txt", "r");
	int *time = malloc(MAX_DISHES_NUM * sizeof(int));
	int i = 0, num = 1;
	int maxlen;
	int t = 0;
	int type = 0, count = 0;
	while (num != 0)
	{
		fscanf(cleaner, "%d:%d", &num, &t);
		time[num - 1] = t;
	}
	fclose(cleaner);
	if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
	{
		printf("Can\'t get msqid\n");
		exit(-1);
	}
	struct mymsgbuf
	{
		long mtype;
		struct 
		{
			int type;
		} info;
	} mybuf;
	while(1)
	{
		maxlen = sizeof(mybuf.info);

		if ((len = msgrcv(msqid, (struct msgbuf *)&mybuf, maxlen, 1, 0)) < 0)
		{
			printf("Can\'t receive message from queue\n");
			exit(-1);
		}
		semaphore(1);
		type = mybuf.info.type;
		if (type == 0)
			break;
		sleep(time[type - 1]);
		printf("OK type = %d time = %d\n", type, time[type - 1]);
	}
	free(time);
	semctl(semid, 0, IPC_RMID, 0);
	msgctl(msqid, IPC_RMID, 0);
	return 0;
}

