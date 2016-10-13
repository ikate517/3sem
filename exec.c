#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_STRING_SIZE 1000
#define MAX_TOKEN_SIZE 100

void Split(char* string, char* delimeters, char*** tokens, int* tokensCount)
{
  *tokensCount = 0;
  char* t = strtok(string, delimeters);
  while (t)
  {
    (*tokens)[*tokensCount] = t;
    (*tokensCount)++;
    t = strtok(NULL, delimeters);
  }
}


int main()
{
	int i = 0;
	int count;
	int commands_number;
	char delimitres[2] = {' ', '\n'};
	char* string = malloc(MAX_STRING_SIZE * sizeof(char));
	FILE* file;
	file = fopen("file.txt", "r");

	fscanf(file, "%d", &commands_number);
	commands_number += 1;

  char **tokens = malloc(commands_number * sizeof(char*));

	for (i = 0; i < commands_number; i++) 
	{
		tokens[i] = malloc(MAX_TOKEN_SIZE * sizeof(char));
	}
	
	for (i = 0; i < commands_number; i++)
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
	
	for (i = 0; i < commands_number; i++) 
	{
		free(tokens[i]);
	}
	free(tokens);
	free(string);
	fclose(file);
	return 0;
}
