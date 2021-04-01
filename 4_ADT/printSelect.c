#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

typedef char element;
typedef struct ListNode {
    element data;
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

void addFirst(LinkedListType* L, element item)
{
    ListNode* node = getNode();
    node->data = item;
    node->link = L->head;
    L->head = node;
}

void print_list(LinkedListType* L)
{
    for (ListNode* p = L->head; p != NULL; p = p->link)
        printf("[%c] -> ", p->data);
    printf("NULL\n");
}

void printSelect(LinkedListType* L, LinkedListType* S)
{
    ListNode* l = L->head;
    ListNode* s = S->head;
    int cnt = 1;
    while (s != NULL)
    {
        int index = s->data - '0';
        for (; cnt <= index;l=l->link,cnt++)
            if(cnt==index)
                printf("%c ", l->data);
        s = s->link;
    }
    printf("\n");
}

int main()
{
    LinkedListType list1;
    LinkedListType list2;
    init(&list1);
    init(&list2);

    printf("list1 \n");
    addFirst(&list1, 'E');
    addFirst(&list1, 'G');
    addFirst(&list1, 'N');
    addFirst(&list1, 'A');
    addFirst(&list1, 'R');
    addFirst(&list1, 'O');
    print_list(&list1);

    printf("\nlist2 \n");
    addFirst(&list2, '5');
    addFirst(&list2, '4');
    addFirst(&list2, '1');
    print_list(&list2);

    printf("\n");
    printSelect(&list1, &list2);

    return 0;
}