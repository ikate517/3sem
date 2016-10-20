#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_NUM 1
#define MAX_NUMBER 100000000

float data[MAX_NUMBER];
double part_sum[THREAD_NUM];
double part_sqrt_sum[THREAD_NUM];
unsigned int len = MAX_NUMBER / THREAD_NUM;
float average;

struct Segment
{
	int begin;
	int end;
	int index;
};

void* my_thread(void* arg) 
{
	struct Segment segment = *((struct Segment*)arg);
	int i;
	part_sum[segment.index] = 0;
	part_sqrt_sum[segment.index] = 0;
	for (i = segment.begin; i < segment.end; i++)
	{
		part_sum[segment.index] += data[i];
		part_sqrt_sum[segment.index] += data[i] * data[i];
	}
    return NULL;
}

int main() 
{
	int i;
	double sum = 0, sqrt_sum = 0;
	float dispersion = 0;
    
    for(i = 0; i < MAX_NUMBER; i++)
    {
		data[i] = (rand() % 2);
	}

	pthread_t thread_ids[THREAD_NUM];
	int num = 0;
    int result[THREAD_NUM];
    struct Segment segments[THREAD_NUM];
    for (i = 0; i < THREAD_NUM; i++)
	{
		segments[i].index = i;
		segments[i].begin = len * i;
		segments[i].end = segments[i].begin + len;
	}
	
	struct timespec start, finish;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &start);	
	for(i = 0; i < THREAD_NUM; i++) 
	{
		result[i] = pthread_create(&(thread_ids[i]), (pthread_attr_t *)NULL, my_thread, &(segments[i]));
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
	
	for (i = 0; i < THREAD_NUM; i++)
	{
		sum += part_sum[i];
		sqrt_sum += part_sqrt_sum[i];
	}
	
	average = sum / MAX_NUMBER;
	sqrt_sum /= MAX_NUMBER;
	dispersion = sqrt_sum - average * average;

	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
 
	printf("sum = %.0f   average = %.2f   dispersion = %.2f\n", sum, average, dispersion);
	printf(" %d time = %.1f\n", THREAD_NUM, elapsed);
  
    return 0;
}
