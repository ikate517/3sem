#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
pid_t pid;
pid_t ppid;

void my_handler1()
{
	printf("RT\n");
	sleep(2);
	kill(pid, SIGUSR2);
}

void my_handler2()
{
	printf("Champion\n");
	sleep(1);
	kill(ppid, SIGUSR1);
}

int main()
{
	(void)signal(SIGUSR1, my_handler1);
	ppid = getpid();
	pid = fork();
	if (pid == 0)
	{
		(void)signal(SIGUSR2, my_handler2);
	}
	else if (pid > 0)
	{
		my_handler1();
	}
	while(1)
	{
	}
	return 0;
}

