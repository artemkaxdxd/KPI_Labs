#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef struct nodeList {
    int key;
    struct nodeList* next;
} node;
struct nodeList* head = NULL;

void printList(node** list) {
    for (node* l = list; l != NULL; l = l->next) {
        printf("%c ", (char)l->key);
    }
    printf("\n");
}

void addList(struct node** head, int val) {
    node* newNode = malloc(sizeof(node));
    newNode->key = val;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct nodeList* lastNode = *head;
        while (lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }
}

node* getNodeByIndex(node* list, int idx) {
    int counter = 0;
    while (list->next != NULL) {
        if (counter == idx) return list;
        list = list->next;
        counter++;
    }
}

void deleteList(node** list) {
    node* current = *list;
    node* next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *list = NULL;
}

struct node* move(struct nodeList* list, node* element) {
    struct nodeList* head = list;
    struct nodeList* prev = NULL;
    struct nodeList* curr = head;
    if (list == NULL || list->next == NULL) return head;
    while (curr) {
        if (curr == element) {
            if (curr == head) {
                head = curr->next;
            }
            else {
                prev->next = curr->next;
            }
            curr = curr->next;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
    prev->next = element;
    element->next = NULL;
    return head;
}

int main() {
    node* list = NULL;
    int N, flag = 0;
    char listStr[] = "16s9w32mg7r85pmte4xp3rvrdrr72u55l18q5936584sqe913qcj589ta7mpp20jb7zalw856cm6riowhp8gfdsv0c0k3pm8dok";

    printf("Input length of the list (N <= 100): ");
    scanf_s("%d", &N);
    if (N > sizeof(listStr)) {
        printf("\nInvalid length\n");
        return 0;
    }
    for(int i = 0; i < N; ++i) {
        addList(&list, listStr[i]);
    }

    printf("\nList before sorting: \n");
    printList(list);

    node* first = NULL;
    for (int i = 0; i < N; ++i) {
        node* curNode = getNodeByIndex(list, i);
        if (!isdigit((char)(curNode->key))) {
            if (flag == 0) {
                first = curNode;
                flag = -1;
            }
            else if (curNode == first) break;
            //printf("%d: %c\n",i , curNode->key);
            move(list, curNode);
            i--;
        }
    }
    printf("\nSorted list of numbers and letters:\n");
    printList(list);

    deleteList(&list);
    printf("List after clearing: ");
    printList(list);
    return 0;
}