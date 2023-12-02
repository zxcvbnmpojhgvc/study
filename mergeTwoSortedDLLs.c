#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void displayList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

struct Node* mergeLists(struct Node* list1, struct Node* list2) {
    struct Node* mergedHead = createNode(-1);
    struct Node* current = mergedHead;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data < list2->data) {
            current->next = list1;
            list1->prev = current;
            list1 = list1->next;
        } else {
            current->next = list2;
            list2->prev = current;
            list2 = list2->next;
        }
        current = current->next;
    }

    if (list1 != NULL) {
        current->next = list1;
        list1->prev = current;
    } else {
        current->next = list2;
        list2->prev = current;
    }
    struct Node* result = mergedHead->next;
    free(mergedHead);
    return result;
}

int main() {
    struct Node* list1 = createNode(1);
    list1->next = createNode(3);
    list1->next->prev = list1;
    list1->next->next = createNode(5);
    list1->next->next->prev = list1->next;

    struct Node* list2 = createNode(2);
    list2->next = createNode(4);
    list2->next->prev = list2;
    list2->next->next = createNode(6);
    list2->next->next->prev = list2->next;

    printf("List 1: ");
    displayList(list1);
    printf("List 2: ");
    displayList(list2);

    struct Node* mergedList = mergeLists(list1, list2);
    printf("Merged List: ");
    displayList(mergedList);

    return 0;
}
