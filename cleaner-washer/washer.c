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
    if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
	{
		printf("Can\'t get msqid\n");
		exit(-1);
	}
	
	int i;
	
	struct mymsgbuf
	{
		long mtype;
		struct 
		{
			int type;
		} info;
	} mybuf;
	FILE *washer = fopen("washer.txt", "r");
	int *time = malloc(MAX_DISHES_NUM * sizeof(int));
	int t = 0;
	int num = 1;
	int type = 0, count = 0;
	while (num != 0)
	{
		fscanf(washer, "%d:%d", &num, &t);
		time[num - 1] = t;
	}
	fclose(washer);
	FILE *dishes = fopen("dishes.txt", "r");
	semaphore(TABLE);
	while(1)
	{
		fscanf(dishes, "%d:%d", &type, &count);
		if (type == 0)
		{
			mybuf.mtype = 1;
			mybuf.info.type = type;
			len = sizeof(mybuf.info);
	
			if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0)
			{
				printf("Can\'t send message to queue\n");
				msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
				exit(-1);
			}
			break;
		}
		for(i = 0; i < count; i++)
		{
			sleep(time[type - 1]);
			printf("OK type = %d time = %d \n", type, time[type - 1]);
			mybuf.mtype = 1;
			mybuf.info.type = type;
			len = sizeof(mybuf.info);
	
			if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0)
			{
				printf("Can\'t send message to queue\n");
				msgctl(msqid, IPC_RMID, (struct msqid_ds*)NULL);
				exit(-1);
			}
			semaphore(-1);
			
		}
	}
	fclose(dishes);
	free(time);
	return 0;
}

