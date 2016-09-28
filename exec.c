#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_STRING_SIZE 1000
#define MAX_TOKEN_SIZE 100

void Split(char* string, char* delimiters, char*** tokens, int* count)
{
	char* tmp = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
	int i;
	tmp = strtok(string, delimiters);
	strcpy((*tokens)[0], tmp);
	i = 1;
	while (tmp != NULL) 
	{
		tmp = strtok(NULL, delimiters);
		if (tmp != NULL)
			strcpy((*tokens)[i], tmp);
		i++;
	}
	*count = i - 1;
	free(tmp);
}

int main()
{
	int i = 0;
	int count;
	int N;
	char delimitres[2] = {' ', '\n'};
	char* string = malloc(MAX_STRING_SIZE * sizeof(char));
	FILE* file;
	file = fopen("file.txt", "r");
	fscanf(file, "%d", &N);
	N = N + 1;
	char **tokens = malloc(N * sizeof(char*));

	for (i = 0; i < N; i++) 
	{
		tokens[i] = malloc(MAX_TOKEN_SIZE * sizeof(char));
	}
	
	for (i = 0; i < N; i++)
	{
		fgets(string, MAX_STRING_SIZE,file);
		pid_t pid = fork();
		if (pid == 0)
		{
			Split(string, delimitres, &tokens, &count);
			sleep(atoi(tokens[0]));
			tokens[count] = NULL;
			execvp(tokens[1], tokens + 1);
			exit(0);
		}
	}
	
	for (i = 0; i < N; i++) 
	{
		free(tokens[i]);
	}
	free(tokens);
	free(string);
	fclose(file);
	return 0;
}
