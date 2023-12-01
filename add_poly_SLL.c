#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
};

typedef struct Node Node;

void insert_term(Node** head, int coefficient, int exponent) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->coefficient = coefficient;
    new_node->exponent = exponent;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void display(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%dx^%d ", current->coefficient, current->exponent);
        current = current->next;
    }
    printf("\n");
}

Node* add_polynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;

    while (poly1 != NULL || poly2 != NULL) {
        if (poly1 == NULL) {
            insert_term(&result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else if (poly2 == NULL) {
            insert_term(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else {
            if (poly1->exponent > poly2->exponent) {
                insert_term(&result, poly1->coefficient, poly1->exponent);
                poly1 = poly1->next;
            } else if (poly1->exponent < poly2->exponent) {
                insert_term(&result, poly2->coefficient, poly2->exponent);
                poly2 = poly2->next;
            } else {
                insert_term(&result, poly1->coefficient + poly2->coefficient, poly1->exponent);
                poly1 = poly1->next;
                poly2 = poly2->next;
            }
        }
    }

    return result;
}

int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;

    int n, coefficient, exponent;

    printf("Enter the number of terms in Polynomial 1: ");
    scanf("%d", &n);

    printf("Enter the terms for Polynomial 1 (coefficient exponent):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coefficient, &exponent);
        insert_term(&poly1, coefficient, exponent);
    }

    printf("Enter the number of terms in Polynomial 2: ");
    scanf("%d", &n);

    printf("Enter the terms for Polynomial 2 (coefficient exponent):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &coefficient, &exponent);
        insert_term(&poly2, coefficient, exponent);
    }

    printf("\nPolynomial 1: ");
    display(poly1);

    printf("Polynomial 2: ");
    display(poly2);

    Node* result = add_polynomials(poly1, poly2);

    printf("Resultant Polynomial: ");
    display(result);

    return 0;
}

