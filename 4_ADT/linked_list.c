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

void add(LinkedListType* L, int pos, int item)
{
     ListNode* node = getNode();
     ListNode* before = L->head;
     for (int i = 0; i < pos - 1; i++)
          before = before->link;
     node->data = item;
     node->link = before->link;
     before->link = node;
}

int get(LinkedListType* L, int pos)
{
     ListNode* p = L->head;
     for (int i = 1; i < pos; i++)
          p = p->link;
     return p->data;
}

void set(LinkedListType* L, int pos, int item)
{
     ListNode* p = L->head;
     for (int i = 1; i < pos; i++)
          p = p->link;
     p->data = item;
}

void addLast(LinkedListType* L, int item)
{
     ListNode* node = getNode();
     ListNode* p = L->head;

     node->data = item;
     node->link = NULL;
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
     free(removed);
     return data;
}

int remove_(LinkedListType* L, int pos)
{
     if (L->head == NULL)
     {
          printf("emptyListException...\n");
          exit(1);
     }
     if (pos <= 0)
     {
          printf("invalidRankException...\n");
          exit(1);
     }

     int data;
     ListNode* before = NULL;
     ListNode* removed = L->head;
     for (int i = 0; i < pos - 1; i++)
     {
          before = removed;
          removed = removed->link;
          if (removed == NULL)
          {
               printf("invalidRankException...\n");
               exit(1);
          }
     }
     data = removed->data;
     if (before != NULL)
          before->link = removed->link;
     else
          L->head = removed->link;
     free(removed);
     return data;
}

int removeLast(LinkedListType* L)
{
     ListNode* before = NULL;
     ListNode* p = L->head;

     // 리스트가 비었을 때
     if (!p)
     {
          printf("emptyListException...\n");
          exit(1);
     }

     int data;
     for (; p->link != NULL; p = p->link)
          before = p;

     data = p->data;
     if (before != NULL)
          before->link = NULL;
     free(p);
     return data;
}

void print_list(LinkedListType* L)
{
     for (ListNode* p = L->head; p != NULL; p = p->link)
          printf("[%d] -> ", p->data);
     printf("NULL\n");
}
int main()
{
     LinkedListType list;
     init(&list);
     int ret, pos;

     printf("\naddFirst(10), addFirst(20), add(pos=2, 30)\n");
     addFirst(&list, 10); print_list(&list);
     addFirst(&list, 20); print_list(&list);
     add(&list, 2, 30); print_list(&list);

     printf("\naddLast 구현 : 차례대로 40, 50을 뒤에 삽입\n");
     addLast(&list, 40); print_list(&list);
     addLast(&list, 50); print_list(&list);

     printf("\nremoveFirst 구현\n");
     ret = removeFirst(&list);
     printf("%d을 제거\n", ret);
     print_list(&list);

     printf("\nremoveLast 구현\n");
     ret = removeLast(&list);
     printf("%d을 제거\n", ret);
     print_list(&list);

     printf("\nremove 구현\n몇 번 노드의 값을 제거할까요? ");
     scanf("%d", &pos);
     ret = remove_(&list, pos); print_list(&list);
     printf("%d번 노드 : %d을 제거\n", pos, ret);

     return 0;
}