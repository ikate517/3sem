#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * FIXIT: В коде не должны быть никаких магических чисел вроде 10000 и 30.
 * Нужно завести константу, из названия которой ясно, зачем это число нужно:
 * #define MAX_TOKEN_SIZE 10000
 * #define MAX_TOKENS_COUNT 30
 * или неким схожим образом ...
 */

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
/*
 * FIXIT: названия крайте непонятные: что кроется за переменными s,d, mas!!! (мы говорили, что транслит лучше избегать)
 * видимо это должны быть string, delimeters и tokens
 */
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

