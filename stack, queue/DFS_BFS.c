#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

#define N 8

int graph[N][N] = {
{0, 1, 1, 1, 0, 0, 0, 0},
{1, 0, 0, 0, 1, 1, 0, 0},
{1, 0, 0, 0, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 0 ,0},
{0, 1, 0, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 0, 1, 1},
{0, 0, 0, 0, 0, 1, 0, 0},
{0, 0, 0, 0, 0, 1, 0, 0}
};

#define no -666

typedef struct _Stack 
{
	int count;
	int allocatedMemory;
	double *arr;
} Stack;

typedef struct _QueueNode
{
    int data;
    struct _QueueNode *next;
} QueueNode;
 
typedef struct _Queue
{
    QueueNode *head;
    QueueNode *tail;
} Queue;
  
void Init_Queue(Queue *queue)
{
   queue->head = (QueueNode *)malloc(sizeof(QueueNode));
   queue->tail = (QueueNode *)malloc(sizeof(QueueNode));
 
    queue->head->next = queue->tail;
    queue->tail->next = NULL;
 
    queue->head->data = 0;
    queue->tail->data = 0;
}
 
 QueueNode *Begin_Queue(Queue *queue)
{
    return queue->head->next;
}
 
QueueNode *End_Queue(Queue *queue)
{
    return queue->tail;
}
 
int IsEmpty_Queue(Queue *queue)
{
    return Begin_Queue(queue) == End_Queue(queue) ? 1 : 0;
}
 
void Push_Queue(Queue *queue, int data)
{
QueueNode *new_elem = (QueueNode*)malloc(sizeof(QueueNode));
    QueueNode *i = queue->head;
 
    new_elem->data = data;
 
    while (i->next != End_Queue(queue))
        i++;
 
    i->next = new_elem;
    new_elem->next = End_Queue(queue);
}
 
int Pop_Queue(Queue *queue)
{
    QueueNode *del_elem = Begin_Queue(queue);
    int data = 0;
 
    if (IsEmpty_Queue(queue) != 1)
    {
        data = del_elem->data;
 
        queue->head->next = del_elem->next;
 
        free(del_elem);
    }
 
    return data;
}

void BFS(Queue *queue)
{
	int dir;
	int i;
	while (!IsEmpty_Queue(queue))
	{
		dir = Pop_Queue(queue);
		printf("%d ", dir + 1);
		for (i = dir; i < N; i++)
		{
			if (graph[dir][i]) 
			{
				Push_Queue(queue, i);
			}
		}
	}
		printf("\n");
}

void Init_Stack(Stack *stack)
{
	stack -> count = 0;
	stack -> allocatedMemory = 0;
	stack -> arr = NULL;
}

void End_Stack(Stack *stack)
{
	free(stack -> arr);
	stack -> allocatedMemory = 0;
}

bool Push_Stack(Stack *stack, int x)
{
	if (stack -> allocatedMemory == 0)
	{
		stack -> arr = realloc (stack -> arr, 1 * sizeof (int));
		stack -> allocatedMemory ++;
	}
	if (stack -> allocatedMemory == stack -> count)
	{
		stack -> arr = realloc (stack -> arr, 2 * stack -> allocatedMemory * sizeof (int));
		stack -> allocatedMemory *= 2;
	}
	if ( stack -> allocatedMemory < 0) return false;
	stack -> arr[stack -> count] = x;
	stack -> count ++;
	return true;
}

double Pop_Stack(Stack *stack) 
{ 
	if (stack -> count > 0)
	{
		stack -> count --;	
		int res = stack -> arr[stack -> count];
		return res;
	}	
	return no;
}

bool IsEmpty_Stack(Stack *stack)
{
	if (stack -> count == 0)
	return true;
	else return false;
}	

double Top_Stack(Stack *stack) 
{ 
	int res = Pop_Stack(stack);
	Push_Stack(stack, res);
	return res;
}


void DFS(Stack *stack)
{
	int dir;
	int i;
	while (!IsEmpty_Stack(stack))
	{
		dir = Pop_Stack(stack);
		printf("%d ", dir + 1);
		for (i = N - 1; i >= dir; i--)
		{
			if (graph[dir][i]) 
			{
				Push_Stack(stack, i);
			}
		}
	}
	printf("\n");
}

int main()
{ 
	Queue q;
	Init_Queue(&q);
    Push_Queue(&q, 0);
	BFS(&q);
	Stack s = {};
	Init_Stack(&s);
	Push_Stack(&s, 0);
	DFS(&s);
	return 0;
}
