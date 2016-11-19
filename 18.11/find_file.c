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
			exit(0);
		}
	}
		if((entry->d_type == DT_DIR) && (depth > 0) && (strcmp(entry -> d_name, ".") && strcmp(entry -> d_name, "..")))
		{
		strcpy(path, directory);
		strcat(path, "/");
		strcat(path, entry->d_name);
		FindFile(path, depth - 1, filename);
		}   
	}
	free(path);
	return 0;
}

int main(int argc, char* argv[])
{
  /*
   * FIXIT: Если вы заводите переменную is_found, то в случае успеха не нужно убивать процесс с помощью exit(0). Функция должна вернуть 1, если либо в текущей директории получилось 
   * найти этот файл, либо хотя бы один из рекурсивных вызовов FindFile нашёл во вложенной директории его.
   */
	int is_find;
	is_find  = FindFile(argv[1], atoi(argv[2]), argv[3]);
	if(is_find == 0)
		printf("File not found\n");
	return 0;
}
