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

/*
 * Ваш split можно было бы переписать так:
 * 

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

*/

int main()
{
	int i = 0;
	int count;
	int N;
	char delimitres[2] = {' ', '\n'};
	char* string = malloc(MAX_STRING_SIZE * sizeof(char));
	FILE* file;
	file = fopen("file.txt", "r");
/*
 * Если вы что-то считаваете с некого file.txt, его тоже следует коммитить.
 * 
 * Считывание некого N выглядить очень странно. Лучше бы назвали более конкретным названием.
 * Видимо это число комманд для запуска. Почему бы это число не считать также из файла со списком задач.
 */
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
