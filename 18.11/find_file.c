#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LEN 512

int FindFile(char *directory, int depth, char *filename)
{
	DIR *dir;
	struct dirent *entry;
	char *path = (char *)malloc(MAX_PATH_LEN * sizeof(char));
	dir = opendir(directory);
	if (!dir) 
	{
		perror("diropen");
		exit(1);
	}
	while((entry = readdir(dir)) != NULL)
	{
	if (entry->d_type != DT_DIR)
	{
		if(strcmp(filename, entry->d_name) == 0)
		{
			printf("Path:  %s\n", directory);
			free(path);
			return 1;
		}
	}
		if((entry->d_type == DT_DIR) && (depth > 0) && (strcmp(entry -> d_name, ".") && strcmp(entry -> d_name, "..")))
		{
		strcpy(path, directory);
		strcat(path, "/");
		strcat(path, entry->d_name);
		if (FindFile(path, depth - 1, filename))
			return 1;
		}   
	}
	free(path);
	return 0;
}

int main(int argc, char* argv[])
{
	int is_find;
	is_find  = FindFile(argv[1], atoi(argv[2]), argv[3]);
	if(is_find == 0)
		printf("File not found\n");
	return 0;
}
