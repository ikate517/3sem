#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LEN 1000
#define MAX_NAME 100
#define MAX_USERS_NUM 100

struct User
{
	int port;
	int ip;
	char* name;
}; 

char message[MAX_LEN];
char *line;
struct User users[MAX_USERS_NUM];
int sockfd;
struct sockaddr_in servaddr, cliaddr;
int clilen;

void sendMessage(int currentUser, int i)
{
	strcat(message, users[currentUser].name);
	strcat(message, ": ");
	strcat(message, line);
	printf("sending message %s to user with ip %d and  port %d\n", line, users[i].ip, users[i].port);
	bzero(&cliaddr, sizeof(cliaddr));
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = users[i].port;
	cliaddr.sin_addr.s_addr = users[i].ip;
	if (sendto(sockfd, message, strlen(message) + 1, 0, (struct sockaddr*)&cliaddr, clilen) < 0)
	{
		perror(NULL);
		close(sockfd);
		exit(1);
	}
	bzero(&message, strlen(message));
}

int main()
{
	char* private_name = malloc(MAX_NAME * sizeof(char));
	line = malloc(MAX_LEN * sizeof(char));
	int n, i = 0, j = 0;

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(51000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror(NULL);
		exit(1);
	} else
	{
		printf("Sock fd:%d\n", sockfd);
	}

	if (bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
	{
		perror(NULL);
		close(sockfd);
		exit(1);
	}

	int usersCount = 0;
	int currentUser;
	clilen = sizeof(cliaddr);
	while (1)
	{
		bzero(line, MAX_LEN);
		if ((n = recvfrom(sockfd, line, 999, 0, (struct sockaddr*)&cliaddr, &clilen)) < 0)
		{
			perror(NULL);
			close(sockfd);
			exit(1);
		}
		currentUser = -1;
		
		for(i = 0; i < usersCount; i++)
		{
			if((cliaddr.sin_port == users[i].port) && (cliaddr.sin_addr.s_addr == users[i].ip))
				currentUser = i;
		}
		if(currentUser < 0)
		{
			users[usersCount].name = malloc(MAX_NAME * sizeof(char));
			strcpy(users[usersCount].name, line);
			users[usersCount].port = cliaddr.sin_port; 
			users[usersCount].ip = cliaddr.sin_addr.s_addr;
			printf("%s with ip %d, port %d connected\n" ,users[usersCount].name, users[usersCount].ip, users[usersCount].port);
			usersCount++;
		}
		else if (line[0] == '!')
		{
			private_name = strtok(line, "!");
			line = strtok(NULL, "!");
			for (j = 0; j < usersCount; j++)
			{
				if (!strcmp(private_name, users[j].name))
				{
					sendMessage(currentUser, j);
				}
			}
		}
		else 
		{
			for(i = 0; i < usersCount; i++)
			{
				if(i != currentUser)
				{
					sendMessage(currentUser, i);
				}
			}
		}
	}
	return 0;
}
