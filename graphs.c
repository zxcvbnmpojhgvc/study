#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

struct List
{
    int num;
    struct node *array[100];
};

void Edge(struct List *A, int a, int b)
{
    struct node *temp1 = (struct node *)malloc(sizeof(struct node));
    temp1->data = b;
    temp1->next = NULL;

    if (A->array[a] == NULL)
    {
        A->array[a] = temp1;
    }
    else
    {
        struct node *P = A->array[a];
        while (P->next != NULL)
        {
            P = P->next;
        }
        P->next = temp1;
    }

    struct node *temp2 = (struct node *)malloc(sizeof(struct node));
    temp2->data = a;
    temp2->next = NULL;

    if (A->array[b] == NULL)
    {
        A->array[b] = temp2;
    }
    else
    {
        struct node *P = A->array[b];
        while (P->next != NULL)
        {
            P = P->next;
        }
        P->next = temp2;
    }
}

void printGraph(struct List *A)
{
    for (int i = 0; i < A->num; ++i)
    {
        struct node *currentNode = A->array[i];
        printf("Adjacency list of vertex %d: ", i + 1);
        while (currentNode)
        {
            printf("%d -> ", currentNode->data + 1);
            currentNode = currentNode->next;
        }
        printf("NULL\n");
    }
}

void L_DFS_rec(struct List *graph, int vertex, int visited[])
{
    visited[vertex] = 1;
    printf("%d ", vertex + 1);
    struct node *currentNode = graph->array[vertex];
    while (currentNode)
    {
        int adjacentVertex = currentNode->data;
        if (!visited[adjacentVertex])
        {
            L_DFS_rec(graph, adjacentVertex, visited);
        }
        currentNode = currentNode->next;
    }
}

void push(int stack[], int *top, int vertex)
{
    stack[++(*top)] = vertex;
}

int pop(int stack[], int *top)
{
    return stack[(*top)--];
}

void L_DFS(struct List *graph)
{
    int visited[100] = {0};
    int stack[100];
    int top = -1;
    int startvertex;
    printf("enter start vertex : ");
    scanf("%d", &startvertex);
    startvertex--;

    push(stack, &top, startvertex);
    visited[startvertex] = 1;

    while (top != -1)
    {
        int currentVertex = pop(stack, &top);
        printf("%d ", currentVertex + 1);

        struct node *currentNode = graph->array[currentVertex];
        while (currentNode)
        {
            int adjacentVertex = currentNode->data;
            if (!visited[adjacentVertex])
            {
                push(stack, &top, adjacentVertex);
                visited[adjacentVertex] = 1;
            }
            currentNode = currentNode->next;
        }
    }
}

void L_BSF()
{
}

int main()
{
    int n, E;
    int i;
    int choice;
    struct List *A=NULL;
    int start;
    int visited[100] = {0};

    printf("Enter the number of vertices : ");
    scanf("%d", &n);
    printf("\nvertices are :");
    for (i = 0; i < n; i++)
    {
        printf("   %d\t", i + 1);
    }
    printf("\n\nEnter the number of edges: ");
    scanf("%d", &E);

    while (1)
    {
        printf("\n\n1)Adjacency List \n");
        printf("2)Adjacency Matrix\n");
        printf("enter your choice:");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            A = (struct List *)malloc(sizeof(struct List));
            A->num = n;
            for (i = 0; i < n; ++i)
            {
                A->array[i] = NULL;
            }

            for (i = 0; i < E; ++i)
            {
                int a, b;
                do
                {
                    printf("\n\nEnter edge %d (start and end point): \n", i + 1);
                    scanf("%d", &a);
                    scanf("%d", &b);
                    if (a > n || b > n || a == 0 || b == 0 || a == b)
                    {
                        printf("Invalid vertex. Please enter valid vertices.\n");
                    }
                } while (a > n || b > n || a == 0 || b == 0 || a == b);
                Edge(A, a - 1, b - 1);
            }

            while (1)
            {
                printf("\n\n\n1) DSF with Recursion");
                printf("\n2) DSF without Recursion");
                printf("\n3) BSF without Recursion");
                printf("\n4) GO back");

                printf("\nEnter choice:");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:

                    printf("enter start vertex : ");
                    scanf("%d", &start);
                    start--;
                    L_DFS_rec(A, start, visited);
                    break;

                case 2:
                    L_DFS(A);
                    break;

                case 3:
                    L_BSF();
                    break;

                case 4:
                    return 1;
                    break;
                }
            }
            break;

        case 2:
            break;
        }
    }
    return 0;
}
