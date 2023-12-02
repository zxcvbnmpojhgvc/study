#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int vertex, weight;
    struct Node* next;
};

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V;
    struct Node** adjacencyList;
};

struct Node* createNode(int vertex, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->adjacencyList = (struct Node**)malloc(V * sizeof(struct Node*));
    for (int i = 0; i < V; i++) {
        graph->adjacencyList[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
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

void primList(struct Graph* graph) {
    int V = graph->V;
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

        struct Node* temp = graph->adjacencyList[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;
            if (!mstSet[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
            temp = temp->next;
        }
    }

    struct Edge resultMST[V - 1];
    for (int i = 1; i < V; i++) {
        resultMST[i - 1].src = parent[i];
        resultMST[i - 1].dest = i;
        resultMST[i - 1].weight = key[i];
    }

    printMST(resultMST, V);
}

int main() {
    int V, E;

    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    struct Graph* graph = createGraph(V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    printf("Enter edge end-points and weights (src dest weight):\n");
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    primList(graph);

    return 0;
}
