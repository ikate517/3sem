#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Split(char* string, char* delimiters, char*** tokens, int* count)
{
	char* tmp = (char *)malloc(10000 * sizeof(char));
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
	char* s = (char *)malloc(10000 * sizeof(char));
	char* d = (char *)malloc(30 * sizeof(char));
	char** mas = (char **)malloc(30 * sizeof(char*));
	int i;
	for (i = 0; i < 30; i++)
	{
		mas[i] = (char *)malloc(30 * sizeof(char));
	}
	int count;
	gets(s);
	gets(d);
	Split(s, d, &mas, &count);   
	for (i = 0; i < count; i++)
	{
		printf("%s\n", mas[i]);
	}
	for (i = 0; i < 30; i++)
	{
		free(mas[i]);
	}
	free(d);
	free(s);
	free(mas);
	return 0;
}

