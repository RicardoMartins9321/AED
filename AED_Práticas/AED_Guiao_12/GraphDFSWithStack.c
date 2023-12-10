//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Joaquim Madeira, Joao Manuel Rodrigues - June 2021, Nov 2023
//
// GraphDFS - STACK-based Depth-First Search
//

#include "GraphDFSWithStack.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersStack.h"

struct _GraphDFSWithStack {
  int* marked;       // To mark vertices when reached for the first time
  int* predecessor;  // The predecessor vertex, when a vertex was reached
  Graph* graph;
  unsigned int startVertex;
};

void DFSWithStackHelper(GraphDFSWithStack* traversal, unsigned int vertex) {
  Stack* stack = StackCreate(GraphGetNumVertices(traversal->graph));
  StackPush(stack, vertex);

  while (!StackIsEmpty(stack)) {
    unsigned int currentVertex = StackPop(stack);

    if (!traversal->marked[currentVertex]) {
      traversal->marked[currentVertex] = 1;

      // Process the current vertex (you can add your logic here)

      unsigned int* adjacents = GraphGetAdjacentsTo(traversal->graph, currentVertex);
      for (unsigned int i = 1; i <= adjacents[0]; i++) {
        unsigned int adjacentVertex = adjacents[i];
        if (!traversal->marked[adjacentVertex]) {
          StackPush(stack, adjacentVertex);
          traversal->predecessor[adjacentVertex] = currentVertex;
        }
      }

      free(adjacents);
    }
  }

  StackDestroy(&stack);
}

GraphDFSWithStack* GraphDFSWithStackExecute(Graph* g, unsigned int startVertex) {
  assert(g != NULL);
  assert(startVertex < GraphGetNumVertices(g));

  GraphDFSWithStack* traversal =
      (GraphDFSWithStack*)malloc(sizeof(struct _GraphDFSWithStack));
  assert(traversal != NULL);

  unsigned int numVertices = GraphGetNumVertices(g);

  traversal->marked = (int*)calloc(numVertices, sizeof(int));
  assert(traversal->marked != NULL);

  traversal->predecessor = (int*)malloc(numVertices * sizeof(int));
  assert(traversal->predecessor != NULL);
  for (unsigned int i = 0; i < numVertices; i++) {
    traversal->predecessor[i] = -1;
  }

  traversal->predecessor[startVertex] = 0;

  traversal->graph = g;
  traversal->startVertex = startVertex;

  DFSWithStackHelper(traversal, startVertex);

  return traversal;
}

void GraphDFSWithStackDestroy(GraphDFSWithStack** p) {
  assert(*p != NULL);

  GraphDFSWithStack* aux = *p;

  free(aux->marked);
  free(aux->predecessor);

  free(*p);
  *p = NULL;
}

// Getting the result

int GraphDFSWithStackHasPathTo(const GraphDFSWithStack* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  return p->marked[v];
}

Stack* GraphDFSWithStackPathTo(const GraphDFSWithStack* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = StackCreate(GraphGetNumVertices(p->graph));

  if (p->marked[v] == 0) {
    return s;
  }

  // Store the path
  for (unsigned int current = v; current != p->startVertex;
       current = p->predecessor[current]) {
    StackPush(s, current);
  }

  StackPush(s, p->startVertex);

  return s;
}

// DISPLAYING on the console

void GraphDFSWithStackShowPath(const GraphDFSWithStack* p, unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));

  Stack* s = GraphDFSWithStackPathTo(p, v);

  while (StackIsEmpty(s) == 0) {
    printf("%d ", StackPop(s));
  }

  StackDestroy(&s);
}

void GraphDFSWithStackDisplay(const GraphDFSWithStack* p) {
  assert(p != NULL);

  printf("DFS Result:\n");

  for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++) {
    printf("Vertex %d: ", i);
    GraphDFSWithStackShowPath(p, i);
    printf("\n");
  }
}

