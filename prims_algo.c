#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Edge {
    int src, dest, weight;
};

struct Node {
    int vertex, weight;
    struct Node* next;
};

struct Node* createNode(int vertex, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

void addEdge(struct Node* adjacencyList[], int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = adjacencyList[src];
    adjacencyList[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = adjacencyList[dest];
    adjacencyList[dest] = newNode;
}

int minKey(int key[], int mstSet[], int V) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(struct Edge* resultMST, int V) {
    printf("Minimum Spanning Tree Edges:\n");
    for (int i = 1; i < V; i++) {
        printf("(%d, %d) - %d\n", resultMST[i].src, resultMST[i].dest, resultMST[i].weight);
    }
}

void primMatrix(int graph[][100], int V) {
    int parent[V];
    int key[V];
    int mstSet[V];

    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V);
        mstSet[u] = 1;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    struct Edge resultMST[V - 1];
    for (int i = 1; i < V; i++) {
        resultMST[i - 1].src = parent[i];
        resultMST[i - 1].dest = i;
        resultMST[i - 1].weight = graph[i][parent[i]];
    }

    printMST(resultMST, V);
}

int main() {
    int V, E;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    int graph[100][100] = {0};

    printf("Enter edge end-points and weights (src dest weight):\n");
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        graph[src][dest] = weight;
        graph[dest][src] = weight;
    }

    primMatrix(graph, V);

    return 0;
}
