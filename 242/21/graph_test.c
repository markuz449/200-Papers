#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

/**
 * Creates a graph with single directional links depending on the values
 * given from a file.
 * Uses depth first search to go through the graph to
 * connect all of the nodes in the corect order.
 * Prints out the graph with the correct link data.
 *
 * @return EXIT_SUCCESS
 */
int main(void){
    graph g = NULL;
    int input, count = 0, v, size;

    while (1 == scanf("%d", &input)){
        if(count == 0){
            size = input;
            g = graph_new(size);
        }
        else if(count % 2 == 1){
            v = input;
        } else{
            if (v < size && input < size){
                graph_add_edge(g, v, input);
            }
        }
        count++;
    }

    g = graph_dfs(g);
    graph_print(g);
    graph_free(g);

    return EXIT_SUCCESS;
}
