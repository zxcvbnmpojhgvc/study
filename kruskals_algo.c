#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Edge {
    int source, destination, weight;
};

struct DisjointSet {
    int parent[MAX_VERTICES];
    int size[MAX_VERTICES];
};

void makeSet(struct DisjointSet *ds, int vertices) {
    for (int i = 0; i < vertices; i++) {
        ds->parent[i] = i;
        ds->size[i] = 1;
    }
}

int find(struct DisjointSet *ds, int vertex) {
    if (ds->parent[vertex] != vertex) {
        ds->parent[vertex] = find(ds, ds->parent[vertex]);
    }
    return ds->parent[vertex];
}

void unionSets(struct DisjointSet *ds, int src, int dest) {
    src = find(ds, src);
    dest = find(ds, dest);

    if (src != dest) {
        if (ds->size[src] < ds->size[dest]) {
            int temp = src;
            src = dest;
            dest = temp;
        }
        ds->parent[dest] = src;
        ds->size[src] += ds->size[dest];
    }
}

int compareEdges(const void *a, const void *b) {
    return ((struct Edge *)a)->weight - ((struct Edge *)b)->weight;
}

struct Edge createEdge(int source, int destination, int weight) {
    struct Edge edge;
    edge.source = source;
    edge.destination = destination;
    edge.weight = weight;
    return edge;
}

int main() {
    int choice, vertices, edges;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    struct DisjointSet ds;
    makeSet(&ds, vertices);

    struct Edge edgeList[MAX_VERTICES * MAX_VERTICES];

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        printf("Enter source, destination, and weight of edge %d: ", i + 1);
        scanf("%d %d %d", &edgeList[i].source, &edgeList[i].destination, &edgeList[i].weight);
    }

    qsort(edgeList, edges, sizeof(struct Edge), compareEdges);

    printf("Choose representation: 1-for adjacency matrix, 2-for adjacency list: ");
    scanf("%d", &choice);

    if (choice == 1) {

        int graph[MAX_VERTICES][MAX_VERTICES];
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                graph[i][j] = 0;
            }
        }

        int edgeCount = 0;
        int minWeight = 0;

        printf("Edges in the Minimum Spanning Tree (Adjacency Matrix):\n");

        for (int i = 0; i < edges; i++) {
            int source = edgeList[i].source;
            int destination = edgeList[i].destination;
            int weight = edgeList[i].weight;

            if (find(&ds, source) != find(&ds, destination)) {
                printf("%d -- %d  (Weight: %d)\n", source, destination, weight);
                unionSets(&ds, source, destination);
                minWeight += weight;
                edgeCount++;

                if (edgeCount == vertices - 1)
                    break;
            }
        }

        printf("Minimum Spanning Tree Weight: %d\n", minWeight);
    } else if (choice == 2) {

        struct Node* adjacencyList[MAX_VERTICES];
        for (int i = 0; i < vertices; i++) {
            adjacencyList[i] = NULL;
        }

        int edgeCount = 0;
        int minWeight = 0;

        printf("Edges in the Minimum Spanning Tree (Adjacency List):\n");

        for (int i = 0; i < edges; i++) {
            int source = edgeList[i].source;
            int destination = edgeList[i].destination;
            int weight = edgeList[i].weight;

            if (find(&ds, source) != find(&ds, destination)) {
                printf("%d -- %d  (Weight: %d)\n", source, destination, weight);
                unionSets(&ds, source, destination);
                minWeight += weight;
                edgeCount++;

                if (edgeCount == vertices - 1)
                    break;
            }
        }

        printf("Minimum Spanning Tree Weight: %d\n", minWeight);
    } else {
        printf("Invalid choice.");
    }

    return 0;
}
