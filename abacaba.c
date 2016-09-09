#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void GenerateString(int n, char* x)
{
	int p = 1 << (n + 1);
	char* string = malloc (p * sizeof(char));
	char* s = malloc (p * sizeof(char));
	int i;
	string = strcpy(string, x);
	char b[] = "a";
	printf("%s\n", b);
	for (i = 0; i < n; i++)
	{	
		b[0] = b[0] + 1;
		s = strcpy(s, string);
		string = strcat(string, b);
		string = strcat(string, s);
		printf("%s\n", string);
	}
	free(string);
	free(s);
}	

int main()
{
	int n;
	scanf("%d", &n);
	char* a = "a";
	GenerateString(n, a);
	return 0;
}
