#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define NUM 100000

int main()
{
	char *array; 
   int     shmid; 
   const char pathname[] = "s06e01a.c"; 
   key_t   key;

   if((key = ftok(pathname , 0)) < 0)
   {
     printf("Can\'t generate key\n");
     exit(-1);
   }
    if((shmid = shmget(key, NUM * sizeof(char), 0666 | IPC_CREAT | IPC_EXCL)) < 0)
    {    
        if(errno != EEXIST) 
        {         
            printf("Can't create shared memory\n");
            exit(-1);
        } else 
        {
			if((shmid = shmget(key, NUM * sizeof(char), 0)) < 0)
			{
				printf("Can't find shared memory\n");
				exit(-1);
			}
        }
    }
	if((array = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)){
      printf("Can't attach shared memory\n");
      exit(-1);
	}
	FILE *file;
	file = fopen("exes1_1.c", "r");
	int i;
		printf("%s", array);
   if(shmdt(array) < 0)
   {
      printf("Can't detach shared memory\n");
      exit(-1);
   }
   fclose(file);
   shmctl(shmid, IPC_RMID, NULL);
	return 0;
}
