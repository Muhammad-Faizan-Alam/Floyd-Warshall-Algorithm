#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define vertices 1000

void floydWarshall(int **graph) {
    // Allocate dynamic memory for dist matrix
    int **dist = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++)
        dist[i] = (int *)malloc(vertices * sizeof(int));

    // Initialize the distance matrix
    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            dist[i][j] = graph[i][j];

    // Start measuring execution time
    clock_t start = clock();

    // Floyd-Warshall Algorithm
    for (int k = 0; k < vertices; k++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
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

    // Print execution time
    printf("\nExecution Time: %f seconds\n", execution_time);

    // Free dynamically allocated memory
    for (int i = 0; i < vertices; i++)
        free(dist[i]);
    free(dist);
}

int main() {
    // Allocate dynamic memory for graph matrix
    int **graph = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++)
        graph[i] = (int *)malloc(vertices * sizeof(int));

    // Initialize graph with random values
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = (rand() % 100) + 1;  // Assign random weights
        }
    }

    printf("\nSequential way\n");
    floydWarshall(graph);

    // Free dynamically allocated memory
    for (int i = 0; i < vertices; i++)
        free(graph[i]);
    free(graph);

    return 0;
}