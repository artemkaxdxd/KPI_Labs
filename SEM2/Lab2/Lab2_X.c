#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct nodeList {
    int key;
    struct nodeList* next;
} node;
struct nodeList* head = NULL;

void push(node** head, int v) 
{
    node* temp = malloc(sizeof(node));
    temp->key = v;
    temp->next = *head;
    *head = temp;
}

void addLast(struct node** head, int val)
{
    node* newNode = malloc(sizeof(node));
    newNode->key = val;
    newNode->next = NULL;
    if (*head == NULL) {      //if head is NULL, it is an empty list
        *head = newNode;
    } else {     //Otherwise, find the last node and add the newNode
        struct nodeList* lastNode = *head;
        while (lastNode->next != NULL) {        //last node's next address will be NULL.
            lastNode = lastNode->next;
        }
        lastNode->next = newNode; //add the newNode at the end of the linked list
    }
}

int main() {
    node* list = NULL;
    int N;
    char listStr[] = "169sw32mg7r85pmte4xp3rvrdrr72u55l18q5936584sqe913qcj589ta7mpp20jb7zalw856cm6riowhp8gfdsv0c0k3pm8dok";
    printf("Input length of the list (under 100): ");
    scanf_s("%d", &N);
    printf("\nSorted list of numbers and letters:\n");
    for (int i = 0; i < N; ++i) {
        if (isdigit((char)listStr[i])) {
            push(&list, listStr[i]);
        }
        else { 
            addLast(&list, listStr[i]);
        }
    }
    for (node* l = list; l != NULL; l = l->next) { // Displaying the list
        printf("%c ", (char)l->key);
    }
    printf("\n");
    return 0;
}