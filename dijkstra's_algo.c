#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100
#define INF 999999

void dijkstra(int graph[MAX_NODES][MAX_NODES], int numNodes, int source) {
    int dist[MAX_NODES];
    bool visited[MAX_NODES];

    for (int i = 0; i < numNodes; i++) {
        dist[i] = INF;
        visited[i] = false;
    }

    dist[source] = 0;

    for (int count = 0; count < numNodes - 1; count++) {
        int minDist = INF;
        int minIndex;

        for (int v = 0; v < numNodes; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        visited[minIndex] = true;

        for (int v = 0; v < numNodes; v++) {
            if (!visited[v] && graph[minIndex][v] && dist[minIndex] + graph[minIndex][v] < dist[v]) {
                dist[v] = dist[minIndex] + graph[minIndex][v];
            }
        }
    }

    printf("Shortest distances from source %d:\n", source);
    for (int i = 0; i < numNodes; i++) {
        printf("Node %d: %d\n", i, dist[i]);
    }
}

int main() {
    int numNodes, source;
    int graph[MAX_NODES][MAX_NODES];

    printf("Enter the number of nodes: ");
    scanf("%d", &numNodes);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the source node: ");
    scanf("%d", &source);

    dijkstra(graph, numNodes, source);

    return 0;
}
