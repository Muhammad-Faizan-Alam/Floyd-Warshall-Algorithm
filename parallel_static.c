#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>

#define vertices 1000

void floydWarshall(int **graph) {
    int **dist = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++)
        dist[i] = (int *)malloc(vertices * sizeof(int));

    // Initialize distance matrix
    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            dist[i][j] = graph[i][j];

    // Start measuring execution time
    double start = omp_get_wtime();

    int num_threads = omp_get_max_threads();
    printf("Running with %d threads...\n", num_threads);

    // Parallelizing only the "k" loop
    for (int k = 0; k < vertices; k++) {
        #pragma omp parallel for collapse(2) schedule(static)
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
    double end = omp_get_wtime();
    double execution_time = end - start;

    printf("\nExecution Time: %f seconds\n", execution_time);

    // Free allocated memory
    for (int i = 0; i < vertices; i++)
        free(dist[i]);
    free(dist);
}

int main() {
    omp_set_num_threads(4);
    int **graph = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++)
        graph[i] = (int *)malloc(vertices * sizeof(int));

    // Initialize graph with random values
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = (rand() % 100) + 1;  
        }
    }

    printf("\nParallel way\n");
    floydWarshall(graph);

    for (int i = 0; i < vertices; i++)
        free(graph[i]);
    free(graph);

    return 0;
}