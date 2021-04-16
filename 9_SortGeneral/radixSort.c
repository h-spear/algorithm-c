#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUEUE_SIZE 15
#define BUCKETS 10
#define DIGIT 3

#define SIZE 15

typedef int element;
typedef struct {
	int data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q)
{
	return q->front == q->rear;
}

int is_full(QueueType* q)
{
	return (q->front == (q->rear + 1) % MAX_QUEUE_SIZE);
}

void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		exit(1);

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q)
{
	if (is_empty(q))
		exit(1);

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void queue_print(QueueType* q)
{
	if (!is_empty(q))
	{
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

void print_buckets(QueueType queues[])
{
	printf("=====================================\n\n");
	for (int b = 0; b < BUCKETS; b++)
	{
		printf("[%d] -> ", b);
		queue_print(&queues[b]);
	}
	printf("\n=====================================\n\n");
}

void radix_Sort(int list[], int n)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < 10; b++)
		init_queue(&queues[b]);

	for (d = 0; d < DIGIT; d++)
	{
		for (i = 0; i < n; i++)
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		print_buckets(queues);

		for (b = i = 0; b < BUCKETS; b++)
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;
	}
}

int main()
{
	int list[SIZE];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < SIZE; i++)
		list[i] = rand() % 1000;

	for (int i = 0; i < SIZE; i++)
		printf("[%d] ", list[i]);
	printf("\n\n");

	radix_Sort(list, SIZE);

	for (int i = 0; i < SIZE; i++)
		printf("[%d] ", list[i]);
	printf("\n\n");
	return 0;
}