#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct graphrec *graph;
typedef struct vertex *vertices;

extern graph graph_new(int size);
extern void graph_print(graph g);
extern graph graph_add_edge(graph g, int u, int v);
extern graph graph_dfs(graph g);
extern void graph_free(graph g);


#endif
