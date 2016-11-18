#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

int main()
{
	DIR *dir;
	struct dirent *entry;
	struct stat buff; 
	dir = opendir(".");
	if (!dir) 
	{
		perror("diropen");
		exit(1);
	}
	while ((entry = readdir(dir)) != NULL) 
	{
		stat(entry -> d_name, &buff);
		if (S_ISDIR(buff.st_mode))
			printf(" directory %s size = %lld \n", entry->d_name, buff.st_size);
		else printf(" regular file %s size = %lld \n", entry->d_name, buff.st_size);
	}
	closedir(dir);
};
