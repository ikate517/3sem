#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 384  // quantity of strings in matrix 384
#define THREAD_NUM 2

struct Segment
{
	int begin;
	int end;
	int index;
};

int A[N][N], B[N][N], C[N][N];

void* my_thread(void* arg) 
{
	struct Segment segment = *((struct Segment*)arg);
	int i, k, j; 
	for(i = segment.begin; i < segment.end; i++)
		for(k = 0; k < N; k++)
			for(j = 0; j < N; ++j)
				C[i][j] += A[i][k] * B[k][j];
    return NULL;
}

int main()
{	
	pthread_t thread_id[THREAD_NUM];
	int result[THREAD_NUM];
	int i, j, k;
	FILE *file;
	file = fopen("matr.txt", "r");
    struct Segment segments[THREAD_NUM];
    for (i = 0; i < THREAD_NUM; i++)
	{
		segments[i].index = i;
		segments[i].begin = i * N / THREAD_NUM;
		segments[i].end = segments[i].begin + N / THREAD_NUM;
	}
    for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			fscanf(file ,"%d", &A[i][j]);
		}
	}
	fclose(file);
	file = fopen("file.txt", "r");
	 for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			fscanf(file ,"%d", &B[i][j]);
		}
	}
	clock_t begin = clock();
    for (i = 0; i < THREAD_NUM - 1; i++)
    {
		result[i] = pthread_create(&thread_id[i], (pthread_attr_t *)NULL, my_thread, &(segments[i]));

		if (result[i]) 
		{
			printf("Can`t create thread, returned value = %d\n" , result[i]);
			exit(-1);
		}
	}
	for(i = segments[THREAD_NUM - 1].begin; i < segments[THREAD_NUM - 1].end; i++)
		for(k = 0; k < N; k++)
			for(j = 0; j < N; ++j)
				C[i][j] += A[i][k] * B[k][j];
	for(i = 0; i < THREAD_NUM; i++)
    {
		pthread_join(thread_id[i], (void **) NULL);
	}
	clock_t end = clock();
	/*for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}*/
	double time_spent = (double)(end - begin);
	printf(" %d time = %.1f\n", THREAD_NUM ,time_spent);
	fclose(file);
	return 0;
}

