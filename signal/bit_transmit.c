#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

#define MAX_LENGHT 100

int BitNumber = 0;
pid_t ppid;
char s[] = "Hello, world!";
int lenght;
char result[MAX_LENGHT];

void receiveBit(int signal)
{
	int number = BitNumber / 8;
	int position = BitNumber % 8; 
	if (signal == SIGUSR2)
		result[number] |= (1 << position);
	BitNumber++;
	kill(ppid, SIGINT);
	if (number == lenght)
	{
		printf("%s\n", result);
	}
}

void sendBit()
{
	char bit;
	int number = BitNumber / 8;
	int position = BitNumber % 8; 
	bit = s[number] & (1 << position);
	BitNumber++;
	if(bit)
	{
		kill(ppid, SIGUSR2);
	}else
	{
		kill(ppid, SIGUSR1);
	}
	if (number == lenght)
		exit(0);
}

int main()
{
	lenght = strlen(s);
	signal(SIGUSR1, receiveBit);
	signal(SIGUSR2, receiveBit);
	signal(SIGINT, sendBit);
	ppid = getpid();
	pid_t pid = fork();
	if (pid != 0) 
	{
		ppid = pid;
		sendBit();
	}
	while(1)
	{
	}
	return 0;
}
