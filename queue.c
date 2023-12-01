#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

struct Queue {
    int front, rear, size;
    int array[MAX_QUEUE_SIZE];
};

typedef struct Queue Queue;

void init_queue(Queue* queue) {
    queue->front = queue->rear = -1;
    queue->size = 0;
}

int is_empty(Queue* queue) {
    return (queue->size == 0);
}

int is_full(Queue* queue) {
    return (queue->size == MAX_QUEUE_SIZE);
}

void enqueue(Queue* queue, int data) {
    if (is_full(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }

    if (is_empty(queue)) {
        queue->front = queue->rear = 0;
    } else {
        queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
    }

    queue->array[queue->rear] = data;
    queue->size++;

    printf("Enqueued: %d\n", data);
}

void dequeue(Queue* queue) {
    if (is_empty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return;
    }

    int data = queue->array[queue->front];

    if (queue->front == queue->rear) {
        // Last element in the queue
        init_queue(queue);
    } else {
        queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
    }

    queue->size--;

    printf("Dequeued: %d\n", data);
}

void display(Queue* queue) {
    if (is_empty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    int i = queue->front;
    printf("Queue: ");
    while (1) {
        printf("%d ", queue->array[i]);
        if (i == queue->rear)
            break;
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    printf("\n");
}

int main() {
    Queue queues[10]; // Array of 10 queues
    int queueIndex = -1; // Index to keep track of the current active queue

    while (1) {
        printf("\nOptions:\n");
        printf("A. Add Queue\n");
        printf("B. Delete Queue\n");
        printf("C. Enqueue Element\n");
        printf("D. Dequeue Element\n");
        printf("E. Display Queue\n");
        printf("X. Exit\n");

        char choice;
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'A':
            case 'a':
                if (queueIndex < 9) {
                    queueIndex++;
                    init_queue(&queues[queueIndex]);
                    printf("Queue added at index %d.\n", queueIndex);
                } else {
                    printf("Cannot add more queues. Maximum limit reached.\n");
                }
                break;

            case 'B':
            case 'b':
                if (queueIndex >= 0) {
                    printf("Queue at index %d deleted.\n", queueIndex);
                    init_queue(&queues[queueIndex]);
                    queueIndex--;
                } else {
                    printf("No queues to delete.\n");
                }
                break;

            case 'C':
            case 'c':
                if (queueIndex >= 0) {
                    int data;
                    printf("Enter the element to enqueue: ");
                    scanf("%d", &data);
                    enqueue(&queues[queueIndex], data);
                } else {
                    printf("No queues available. Add a queue first.\n");
                }
                break;

            case 'D':
            case 'd':
                if (queueIndex >= 0) {
                    dequeue(&queues[queueIndex]);
                } else {
                    printf("No queues available. Add a queue first.\n");
                }
                break;

            case 'E':
            case 'e':
                if (queueIndex >= 0) {
                    display(&queues[queueIndex]);
                } else {
                    printf("No queues to display.\n");
                }
                break;

            case 'X':
            case 'x':
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
