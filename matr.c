#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 384  // quantity of strings in matrix 384
#define THREAD_NUM 4

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
	pthread_t thread_ids[THREAD_NUM];
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
	struct timespec start, finish;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &start);	
    for (i = 0; i < THREAD_NUM; i++)
    {
		result[i] = pthread_create(&thread_ids[i], (pthread_attr_t *)NULL, my_thread, &(segments[i]));

		if (result[i]) 
		{
			printf("Can`t create thread, returned value = %d\n" , result[i]);
			exit(-1);
		}
	}
	for(i = 0; i < THREAD_NUM; i++)
    {
		pthread_join(thread_ids[i], (void **) NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &finish);
	/*for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}*/
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 10000000.0;
	printf(" %d time = %.1f\n", THREAD_NUM, elapsed);
	fclose(file);
	return 0;
}

