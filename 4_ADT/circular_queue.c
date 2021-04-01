#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct {
	int data[SIZE];
	int front, rear;
	int n;	// 빈 큐와 만원 큐를 차별화하기 위해 방 한 개를 예삐하는 대신 변수 사용
}QueueType;

void init(QueueType* q)
{
	q->front = q->rear = 0;
	q->n = 0;
}

int size(QueueType* q)
{
	return q->n;
}

int is_empty(QueueType* q)
{
	return (q->n == 0);
}

int is_full(QueueType* q)
{
	return (q->n == SIZE);
}

int front(QueueType* q)
{
	return q->data[q->front];
}

void enqueue(QueueType* q, int data)
{
	if (is_full(q))
	{
		fprintf(stderr, "full!\n");
		exit(1);
	}
	q->data[q->rear] = data;
	q->rear = (q->rear + 1) % SIZE;
	q->n++;
}

int dequeue(QueueType* q)
{
	if (is_empty(q))
	{
		fprintf(stderr, "empty!\n");
		exit(1);
	}
	int data = q->data[q->front];
	q->front = (q->front + 1) % SIZE;
	q->n--;
	return data;
}

void print(QueueType* q)
{
	for (int i = q->front, cnt = q->n; cnt > 0; cnt--,i++)
		printf("%d -> ", q->data[i]);
	printf("\n");
}

int main()
{
	QueueType q;
	init(&q);
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	print(&q);

	printf("\ndequeue : %d", dequeue(&q));
	printf("\ndequeue : %d", dequeue(&q));
	printf("\ndequeue : %d", dequeue(&q));
	return 0;
}