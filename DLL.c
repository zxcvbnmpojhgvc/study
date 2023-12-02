#include <stdio.h>
#include <stdlib.h>

// Structure for a node in a doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to display a doubly linked list
void displayList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to insert a node at the beginning of the doubly linked list
struct Node* insertAtBeginning(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    newNode->next = head;
    head->prev = newNode;
    return newNode;
}

// Function to insert a node at the end of the doubly linked list
struct Node* insertAtEnd(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL) {
        return newNode;
    }
    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
    return head;
}

// Function to insert a node after a given node in the doubly linked list
void insertAfterNode(struct Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL.\n");
        return;
    }
    struct Node* newNode = createNode(data);
    newNode->next = prevNode->next;
    if (prevNode->next != NULL) {
        prevNode->next->prev = newNode;
    }
    prevNode->next = newNode;
    newNode->prev = prevNode;
}

// Function to delete the first node of the doubly linked list
struct Node* deleteAtBeginning(struct Node* head) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    struct Node* temp = head;
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    }
    free(temp);
    return head;
}

// Function to delete the last node of the doubly linked list
struct Node* deleteAtEnd(struct Node* head) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    struct Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    if (current->prev != NULL) {
        current->prev->next = NULL;
    } else {
        // If the list had only one element
        free(current);
        return NULL;
    }
    free(current);
    return head;
}

// Function to delete a specified node from the doubly linked list
struct Node* deleteNode(struct Node* head, int data) {
    struct Node* current = head;

    // Search for the node to be deleted
    while (current != NULL && current->data != data) {
        current = current->next;
    }

    // If the node is not found
    if (current == NULL) {
        printf("Node with value %d not found.\n", data);
        return head;
    }

    // Adjust the pointers to delete the node
    if (current->prev != NULL) {
        current->prev->next = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    // If the node to be deleted is the head
    if (current == head) {
        head = current->next;
    }

    free(current);
    return head;
}

int main() {
    struct Node* head = NULL;

    // Insert at the beginning
    head = insertAtBeginning(head, 3);
    head = insertAtBeginning(head, 2);
    head = insertAtBeginning(head, 1);
    printf("Doubly Linked List after insertion at the beginning: ");
    displayList(head);

    // Insert at the end
    head = insertAtEnd(head, 4);
    head = insertAtEnd(head, 5);
    printf("Doubly Linked List after insertion at the end: ");
    displayList(head);

    // Insert after a given node
    insertAfterNode(head->next, 10);
    printf("Doubly Linked List after insertion after a given node: ");
    displayList(head);

    // Delete at the beginning
    head = deleteAtBeginning(head);
    printf("Doubly Linked List after deletion at the beginning: ");
    displayList(head);

    // Delete at the end
    head = deleteAtEnd(head);
    printf("Doubly Linked List after deletion at the end: ");
    displayList(head);

    // Delete a specified node
    head = deleteNode(head, 3);
    printf("Doubly Linked List after deletion of a specified node: ");
    displayList(head);

    return 0;
}
