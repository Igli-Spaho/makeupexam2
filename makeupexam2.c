#include <stdio.h>
#include <stdlib.h>

static int countsAllocated = 0;

struct Node
{
    int value;
    struct Node* next;
};

void printList(struct Node* head)
{
    struct Node* tmp = head;
    while (tmp != NULL)
    {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

struct Node* allocateNode(int value)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->value = value;
    node->next = NULL;
    countsAllocated++;
    return node;
}

struct Node* mergeLists(struct Node* pNumbers1, struct Node* pNumbers2)
{
    struct Node* result = NULL;
    struct Node** tail = &result;

    while (pNumbers1 != NULL && pNumbers2 != NULL)
    {
        if (pNumbers1->value == pNumbers2->value)
        {
            *tail = pNumbers1;
            pNumbers1 = pNumbers1->next;
            pNumbers2 = pNumbers2->next;
            (*tail)->next = NULL;
            tail = &((*tail)->next);
        }
        else if (pNumbers1->value < pNumbers2->value)
        {
            pNumbers1 = pNumbers1->next;
        }
        else
        {
            pNumbers2 = pNumbers2->next;
        }
    }

    return result;
}

void insert(struct Node** pHead, int value)
{
    struct Node* newNode = allocateNode(value);
    newNode->next = *pHead;
    *pHead = newNode;
}

void freeList(struct Node** pHead)
{
    struct Node* tmp;
    while (*pHead != NULL)
    {
        tmp = *pHead;
        *pHead = tmp->next;
        free(tmp);
        countsAllocated--;
    }

    // Reset the memory allocation count to 0 after freeing all nodes
    countsAllocated = 0;
}

int main(void)
{
    int i, numInputs;
    int countOfNums1, countOfNums2;
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    struct Node* head3 = NULL;
    FILE* inFile = fopen("input.txt", "r");
    
    fscanf(inFile, "%d", &numInputs);
    while (numInputs-- > 0)
    {
        fscanf(inFile, "%d %d", &countOfNums1, &countOfNums2);

        // Free the memory from the previous iteration, if any
        freeList(&head1);
        freeList(&head2);
        freeList(&head3);
        
        for (i = 0; i < countOfNums1; i++)
        {
            int value;
            fscanf(inFile, "%d", &value);
            insert(&head1, value);
        }

        for (i = 0; i < countOfNums2; i++)
        {
            int value;
            fscanf(inFile, "%d", &value);
            insert(&head2, value);
        }

        printf("List 1:\n");
        printList(head1);
        printf("List 2:\n");
        printList(head2);
        printf("Memory Allocated before merge: %d\n", countsAllocated);

        head3 = mergeLists(head1, head2);

        printf("List 3 (Intersection List):\n");
        printList(head3);
        freeList(&head3);

        printf("Memory Allocated after free: %d\n", countsAllocated);
    }

    fclose(inFile);

    return 0;
}
