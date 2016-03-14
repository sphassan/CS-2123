#include <stdlib.h>
#include <stdio.h>

struct cnode
{
        int info;
        struct cnode *next;
        struct cnode *previous;
};
typedef struct cnode cnode;

cnode *insertTail(cnode *head, cnode *tail, int a);
void freeDoublyLinkedList(cnode *head, cnode *tail);
cnode *toBinaryTree(cnode *head, cnode *tail);
void printBinaryTree(cnode *root);
void freeBinaryTree(cnode *root);

int main()
{
        printf("Enter numbers for doubly linked list in sorted order\n");
        int holding = 0;
        char junk = '.';
        junk = getchar();

        if (atoi(&junk) == 0 && junk != '0')
        {
                printf("Null list added, binary tree is null.\n");
                exit(1);
        }

        int x = 1;
        char *build = malloc(sizeof(char) * x);
        char *tmp = '\0';
        build[0] = '\0';
        while (atoi(&junk) != 0 || junk == '0')
        {
                build[x-1] = junk;
                junk = getchar();
                x++;
                tmp = realloc(build, sizeof(char) * x);
                if (tmp != NULL)
                        build = tmp;
                else
                {
                        printf("Out of memory, program exit.");
                        free(build);
                        exit(3);
                }
                build[x-1] = '\0';
        }
        holding = atoi(build);
        free(build);

        cnode *head = malloc(sizeof(cnode));
        head -> info = holding;
        head -> previous = NULL;
        head -> next = NULL;
        cnode *tail = head;

        while (junk == ' ')
        {
                scanf("%d", &holding);
                if (holding < tail -> info)
                {
                        printf("List is out of order, program exit.\n");
                        freeDoublyLinkedList(head, tail);
                        exit(2);
                }
                tail = insertTail(head, tail, holding);
                junk = getchar();
        }

        printf("Doubly Linked List Contents:\n");
        cnode *ptr = head;
        while (ptr != NULL)
        {
                printf("%d ", ptr -> info);
                ptr = ptr -> next;
        }
        printf("\n");

        cnode *root = toBinaryTree(head, tail);

        printf("Binary Search Tree Contents:\n");
        printBinaryTree(root);
        printf("\n");

        freeBinaryTree(root);

        return 0;
}

cnode *insertTail(cnode *head, cnode *tail, int a)
{
        cnode *ptr = malloc(sizeof(cnode));
        if (ptr == NULL)
        {
                printf("Out of memory, program exit.");
                freeDoublyLinkedList(head, tail);
                exit(3);
        }
        ptr -> info = a;
        ptr -> next = NULL;
        ptr -> previous = tail;
        tail -> next = ptr;
        tail = ptr;
        return(tail);
}

void freeDoublyLinkedList(cnode *head, cnode *tail)
{
        cnode *ptr = head;
        cnode *del;

        while (ptr != tail)
        {
                del = ptr;
                ptr = ptr -> next;
                free(del);
        }
        free(tail);
}

cnode *toBinaryTree(cnode *head, cnode *tail)
{
        cnode *root;
        cnode *slow = head;
        cnode *fast = head;

        while (head != tail && fast != tail -> next && fast -> next != tail -> next)
        {
                slow = slow -> next;
                fast = fast -> next -> next;
        }
        root = slow;

        if (head -> info > tail -> info)
                return NULL;
        if (root -> previous != NULL)
                root -> previous = toBinaryTree(head, root -> previous);
        if (root -> next != NULL)
                root -> next = toBinaryTree(root -> next, tail);

        return(root);
}

void printBinaryTree(cnode *root)
{
        if (root != NULL)
        {
                printBinaryTree(root -> previous);
                printf("%d ", root -> info);
                printBinaryTree(root -> next);
        }
}

void freeBinaryTree(cnode *root)
{
        if (root == NULL)
                return;

        freeBinaryTree(root -> previous);
        freeBinaryTree(root -> next);
        free(root);
}
