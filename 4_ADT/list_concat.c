#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode* link;
}ListNode;

typedef struct {
    ListNode* head;
}LinkedListType;

void init(LinkedListType* L)
{
    L->head = NULL;
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

void addFirst(LinkedListType* L, int item)
{
    ListNode* node = getNode();
    node->data = item;
    node->link = L->head;
    L->head = node;
}

void concat(LinkedListType* L1, LinkedListType* L2)
{
    ListNode* prev = NULL;
    if (!L1->head)
        L1->head = L2->head;
    else
    {
        for (ListNode* p = L1->head; p != NULL; prev = p, p = p->link)
            ;
        prev->link = L2->head;
    }
}

void print_list(LinkedListType* L)
{
    for (ListNode* p = L->head; p != NULL; p = p->link)
        printf("[%d] -> ", p->data);
    printf("NULL\n");
}

int main()
{
    LinkedListType list1;
    LinkedListType list2;
    init(&list1);
    init(&list2);

    addFirst(&list1, 10);
    addFirst(&list1, 20);
    addFirst(&list1, 30);
    printf("list1 \n");
    print_list(&list1);

    addFirst(&list2, 50);
    addFirst(&list2, 60);
    addFirst(&list2, 70);
    addFirst(&list2, 80);
    printf("\nlist2 \n");
    print_list(&list2);

    printf("\nconcat(list1,list2)\n");
    concat(&list1, &list2);
    print_list(&list1);

    return 0;
}