#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAX_TOKEN_SIZE 10000
#define MAX_TOKENS_COUNT 30

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

	char* string = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
	char* delimetres = (char *)malloc(MAX_TOKENS_COUNT * sizeof(char));
	char** tokens = (char **)malloc(MAX_TOKENS_COUNT * sizeof(char*));
	int i;
	for (i = 0; i < MAX_TOKENS_COUNT; i++)
	{
		tokens[i] = (char *)malloc(MAX_TOKENS_COUNT * sizeof(char));
	}
	int count;
	gets(string);
	gets(delimetres);
	Split(string, delimetres, &tokens, &count);   
	for (i = 0; i < count; i++)
	{
		printf("%s\n", tokens[i]);
	}
	for (i = 0; i < MAX_TOKENS_COUNT; i++)
	{
		free(tokens[i]);
	}
	free(delimetres);
	free(string);
	free(tokens);
	return 0;
}

