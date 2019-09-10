#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"
#include "graph.h"

typedef enum { UNVISITED, VISITED_SELF, VISITED_DESCENDANTS } state_t;

static int step;

/**
 * Struct vertex. The structure for each vertex.
 *
 * Contents:
 *     @li predecessor the value of the preceding vertex.
 *     @li distance the value of how far away the vertex
 *         is away from the beginning vertex..
 *     @li state the current state of the vertex.
 *     @li finish the value of when the search stops for the vertex.
 */
struct vertex{
    int predecessor;
    int distance;
    state_t state;
    int finish;
};

/**
 * Struct graphrec. The basic structure of the graph.
 *
 * Contents:
 *     @li size the maximum size of the graph.
 *     @li matrix a two-dimensional array that represents the
 *         links between vertices.
 *     @li vertices array holding vertex structs for the graph.
 */
struct graphrec{
    int size;
    int **matrix;
    struct vertex *vertices;
};

/**
 * Creates a new graph with a given input size.
 * Allocates the memory needed to store all of the data.
 *
 * @param size the size of the graph and how many vertices there will be.
 *
 * @return The new graph object.
 */
graph graph_new(int size){
    int i, j;
    graph g = emalloc(sizeof *g);
    
    g->size = size;
    g->matrix = (int **)emalloc(sizeof(int *) * size);
    g->vertices = emalloc(sizeof(struct vertex) * size);

    for (i = 0; i < size; i++){ 
        g->matrix[i] = (int *)emalloc(sizeof(int) * size);
        for (j = 0; j < size; j++){
            g->matrix[i][j] = 0;
        }
    }
    return g;
}

/**
 * Prints out the graph and the stats for the graph.
 * Prints out the adjacency list and the stats for each vertex.
 *
 * @param g the graph that is going to be printed.
 */
void graph_print(graph g){
    int i, j;
    printf("adjacency list:\n");
    for (i = 0; i < g->size; i++){
        printf("%d | ", i);
        for (j = 0; j < g->size; j++){
            if ((g->matrix[i][j]) == 1){
                printf("%d, ", j);
            }
        }
        printf("\n");
    }
    printf("\n");
    printf("vertex distance pred finish\n");
    for (i = 0; i < g->size; i++){
        printf("% 4d    % 4d % 4d  % 4d\n",
               i, g->vertices[i].distance,
               g->vertices[i].predecessor, g->vertices[i].finish);
    }
}

/**
 * Creates a single-directional link between from one vertex to another
 * by specifing it in the graph matrix.
 *
 * @param g the graph that will have the link created for.
 * @param u the value of one of the vertices to get linked.
 * @param v the other value of the vertices to get linked.
 *
 * @return the graph with the added single-directional link.
 */
graph graph_add_edge(graph g, int u, int v){
    if (u < g->size || v < g->size){
        g->matrix[u][v] = 1;
    }
    return g;
}

/**
 * Recursive function that goes to all of the vertices in a given graph.
 * Records the stats for when a particular vertex is visited and when it's
 * adjacent vertices have been searched.
 *
 * @param g the graph whos vertices are being searched.
 * @param v the value of the current vertex.
 *
 * @return the graph that has had a particular vertex serached.
 */
graph visit(graph g, int v){
    int u;
    g->vertices[v].state = VISITED_SELF;
    step++;
    g->vertices[v].distance = step;
    for (u = 0; u < g->size; u++){
        if ((g->matrix[v][u] == 1) &&  (g->vertices[u].state == UNVISITED)){
            g->vertices[u].predecessor = v;
            g = visit(g, u);
        }
    }
    step++;
    g->vertices[v].state = VISITED_DESCENDANTS;
    g->vertices[v].finish = step;
    return g;
}

/**
 * Searches through the graph using depth first search.
 *
 * @param g the graph that will be searchd using depth first search.
 *
 * @return the graph that has been sreached using depth first serach.
 */
graph graph_dfs(graph g){
    int i, v;
    for (i = 0; i < g->size; i++){
        g->vertices[i].state = UNVISITED;
        g->vertices[i].predecessor = -1;
    }
    step = 0;
    for (v = 0; v < g->size; v++){
        if (g->vertices[v].state == UNVISITED){
            g = visit(g, v);
        }
    }
    return g;
}

/**
 * Frees the memory allocated for the graph.
 *
 * @param g the graph who's memory is going to be freed.
 */
void graph_free(graph g){
    int i;
    for (i = 0; i < g->size; i++){
        free(g->matrix[i]);
    }
    free (g->matrix);
    free (g->vertices);
    free (g);
}
