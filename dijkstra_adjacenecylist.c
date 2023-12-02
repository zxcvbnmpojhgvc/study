#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// Structure to represent a node in the adjacency list
struct Node {
    int dest;       // Destination vertex
    int weight;     // Weight of the edge
    struct Node* next;  // Pointer to the next node in the list
};

// Structure to represent the adjacency list for each vertex
struct AdjList {
    struct Node* head;  // Head of the linked list
};

// Structure to represent the graph
struct Graph {
    int V;            // Number of vertices
    struct AdjList* array;  // Array of adjacency lists
};

// Function to create a new node in the adjacency list
struct Node* createNode(int dest, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists, one for each vertex
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by setting the head to NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = createNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Function to find the vertex with the minimum distance value,
// from the set of vertices not yet included in the shortest path tree
int minDistance(int dist[], bool sptSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[], int V, int src) {
    printf("Shortest distances from source %d:\n", src);
    for (int i = 0; i < V; i++) {
        printf("Node %d: %d\n", i, dist[i]);
    }
}

// Function that implements Dijkstra's single source shortest path algorithm
void dijkstra(struct Graph* graph, int src) {
    int V = graph->V;
    int dist[V];     // The output array dist[i] holds the shortest distance from src to i

    bool sptSet[V];  // sptSet[i] is true if the vertex i is included in the shortest path tree or the shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet, V);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        struct Node* temp = graph->array[u].head;
        while (temp != NULL) {
            int v = temp->dest;

            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + temp->weight < dist[v]) {
                dist[v] = dist[u] + temp->weight;
            }

            temp = temp->next;
        }
    }

    // Print the constructed distance array
    printSolution(dist, V, src);
}

int main() {
    int V, E;

    printf("Enter the number of nodes: ");
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

    int source;
    printf("Enter the source node: ");
    scanf("%d", &source);

    dijkstra(graph, source);

    return 0;
}
