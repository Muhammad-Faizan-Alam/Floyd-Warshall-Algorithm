#include <stdio.h>
#include <limits.h>
#include <time.h>

#define vertices 4

void floydWarshall(int graph[vertices][vertices]) {
    int dist[vertices][vertices]; 

    // Initialize the distance matrix
    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            dist[i][j] = graph[i][j];

    // Start measuring execution time
    clock_t start = clock();

    // Floyd-Warshall Algorithm
    for (int k = 0; k < vertices; k++) {
        for (int j = 0; j < vertices; j++) {
            for (int i = 0; i < vertices; i++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Stop measuring execution time
    clock_t end = clock();
    double execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print the result
    printf("The shortest distances between all pairs are:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (dist[i][j] == INT_MAX)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }

    // Print execution time
    printf("\nExecution Time: %f seconds\n", execution_time);
}

int main() {
    int graph[vertices][vertices] = {
        {0, 3, INT_MAX, 7},
        {8, 0, 2, INT_MAX},
        {5, INT_MAX, 0, 1},
        {2, INT_MAX, INT_MAX, 0}
    };

    floydWarshall(graph);
    return 0;
}