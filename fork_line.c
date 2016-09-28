#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	int i;
	int N = 7;
	pid_t child;
	for (i = 0 ; i < N; ++i)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			printf("process %d create pid = %d ppid = %d\n" , i + 1, getpid(), getppid());
		}
		else if (pid > 0)
		{
			child = wait(0);
			printf(" process %d end \n", child);
			exit(0);
		}
	}
	return 0;
}
