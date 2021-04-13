#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

typedef struct ListNode {
    int data;
    struct ListNode* link;
}ListNode;

typedef struct {
    ListNode* head;
    int size;
}LinkedListType;

typedef struct {
    LinkedListType L1;
    LinkedListType L2;
}Set;

void init(LinkedListType* L)
{
    L->head = NULL;
    L->size = 0;
}

void printList(LinkedListType* L)
{
    for (ListNode* p = L->head; p != NULL; p = p->link)
        printf("[%d] -> ", p->data);
    printf("NULL\n");
}

ListNode* getNode()
{
    ListNode* p;
    p = (ListNode*)malloc(sizeof(ListNode));
    if (!p)
    {
        perror("malloc");
        exit(1);
    }
    return p;
}

int is_empty(LinkedListType* L)
{
    return (L->size == 0);
}

int get(LinkedListType* L, int pos)
{
    ListNode* p = L->head;
    for (int i = 1; i < pos; i++)
        p = p->link;
    return p->data;
}

void addLast(LinkedListType* L, int item)
{
    ListNode* node = getNode();
    ListNode* p = L->head;

    node->data = item;
    node->link = NULL;
    L->size++;
    // 리스트가 비었을 때
    if (!p)
    {
        L->head = node;
        return;
    }

    for (; p->link != NULL; p = p->link)
        ;
    p->link = node;
}

int removeFirst(LinkedListType* L)
{
    if (L->head == NULL)
    {
        printf("emptyListException...\n");
        exit(1);
    }

    int data;
    ListNode* removed = L->head;
    data = removed->data;
    L->head = removed->link;
    L->size--;
    free(removed);
    return data;
}

Set partition(LinkedListType* L, int k)
{

    Set result;
    LinkedListType L1, L2;
    ListNode* p = L->head;

    L1.head = p;
    L1.size = k;
    L2.size = L->size - k;

    for (int i = 1; i < k; i++)
        p = p->link;

    L2.head = p->link;
    p->link = NULL;

    result.L1 = L1;
    result.L2 = L2;
    return result;
}

LinkedListType merge(LinkedListType L1, LinkedListType L2, int* cnt)
{
    LinkedListType L;
    init(&L);

    while (!is_empty(&L1) && !is_empty(&L2))
    {
        if (get(&L1, 1) <= get(&L2, 1))
        { 
            addLast(&L, removeFirst(&L1));
        }
        else
        {
            *cnt += L1.size;
            addLast(&L, removeFirst(&L2));
        }
    }
    while (!is_empty(&L1))
        addLast(&L, removeFirst(&L1));
    while (!is_empty(&L2))
        addLast(&L, removeFirst(&L2));
    return L;
}

void mergeSort(LinkedListType* L, int* cnt)
{
    LinkedListType L1, L2;
    Set set;

    if (L->size > 1)
    {
        set = partition(L, L->size / 2);
        L1 = set.L1;
        L2 = set.L2;
        mergeSort(&L1, cnt);
        mergeSort(&L2, cnt);
        *L = merge(L1, L2, cnt);
    }
}

int countInversion(LinkedListType* L)
{
    int cnt = 0;
    int* pointer = &cnt;
    mergeSort(L, pointer);
    return cnt;
}

int main()
{
    LinkedListType list;
    init(&list);

    srand((unsigned int)time(NULL));
    for (int i = 0; i < 10; i++)
        addLast(&list, rand() % 100);

    printList(&list);
    printf("%d\n", countInversion(&list));
    return 0;
}