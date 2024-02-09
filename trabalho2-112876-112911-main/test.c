//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Joaquim Madeira, Joao Manuel Rodrigues - June 2021, Nov 2023
//
// Graph - Using a list of adjacency lists representation
//

#include "Graph.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "SortedList.h"
#include "instrumentation.h"

struct _Vertex
{
  unsigned int id;
  unsigned int inDegree;
  unsigned int outDegree;
  List *edgesList;
};

struct _Edge
{
  unsigned int adjVertex;
  double weight;
};

struct _GraphHeader
{
  int isDigraph;
  int isComplete;
  int isWeighted;
  unsigned int numVertices;
  unsigned int numEdges;
  List *verticesList;
};

// The comparator for the VERTICES LIST

int graphVerticesComparator(const void *p1, const void *p2)
{
  unsigned int v1 = ((struct _Vertex *)p1)->id;
  unsigned int v2 = ((struct _Vertex *)p2)->id;
  int d = v1 - v2;
  return (d > 0) - (d < 0);
}

// The comparator for the EDGES LISTS

int graphEdgesComparator(const void *p1, const void *p2)
{
  unsigned int v1 = ((struct _Edge *)p1)->adjVertex;
  unsigned int v2 = ((struct _Edge *)p2)->adjVertex;
  int d = v1 - v2;
  return (d > 0) - (d < 0);
}

Graph *GraphCreate(unsigned int numVertices, int isDigraph, int isWeighted)
{
  Graph *g = (Graph *)malloc(sizeof(struct _GraphHeader));
  if (g == NULL)
    abort();

  g->isDigraph = isDigraph;
  g->isComplete = 0;
  g->isWeighted = isWeighted;

  g->numVertices = numVertices;
  g->numEdges = 0;

  g->verticesList = ListCreate(graphVerticesComparator);

  for (unsigned int i = 0; i < numVertices; i++)
  {
    struct _Vertex *v = (struct _Vertex *)malloc(sizeof(struct _Vertex));
    if (v == NULL)
      abort();

    v->id = i;
    v->inDegree = 0;
    v->outDegree = 0;

    v->edgesList = ListCreate(graphEdgesComparator);

    ListInsert(g->verticesList, v);
  }

  assert(g->numVertices == ListGetSize(g->verticesList));

  return g;
}

Graph *GraphCreateComplete(unsigned int numVertices, int isDigraph)
{
  Graph *g = GraphCreate(numVertices, isDigraph, 0);

  g->isComplete = 1;

  List *vertices = g->verticesList;
  ListMoveToHead(vertices);
  unsigned int i = 0;
  for (; i < g->numVertices; ListMoveToNext(vertices), i++)
  {
    struct _Vertex *v = ListGetCurrentItem(vertices);
    List *edges = v->edgesList;
    for (unsigned int j = 0; j < g->numVertices; j++)
    {
      if (i == j)
      {
        continue;
      }
      struct _Edge *new = (struct _Edge *)malloc(sizeof(struct _Edge));
      if (new == NULL)
        abort();
      new->adjVertex = j;
      new->weight = 1;

      ListInsert(edges, new);
    }
    if (g->isDigraph)
    {
      v->inDegree = g->numVertices - 1;
      v->outDegree = g->numVertices - 1;
    }
    else
    {
      v->outDegree = g->numVertices - 1;
    }
  }
  if (g->isDigraph)
  {
    g->numEdges = numVertices * (numVertices - 1);
  }
  else
  {
    g->numEdges = numVertices * (numVertices - 1) / 2;
  }

  return g;
}

void GraphDestroy(Graph **p)
{
  assert(*p != NULL);
  Graph *g = *p;

  List *vertices = g->verticesList;
  if (ListIsEmpty(vertices) == 0)
  {
    ListMoveToHead(vertices);
    unsigned int i = 0;
    for (; i < g->numVertices; ListMoveToNext(vertices), i++)
    {
      struct _Vertex *v = ListGetCurrentItem(vertices);

      List *edges = v->edgesList;
      if (ListIsEmpty(edges) == 0)
      {
        unsigned int i = 0;
        ListMoveToHead(edges);
        for (; i < ListGetSize(edges); ListMoveToNext(edges), i++)
        {
          struct _Edge *e = ListGetCurrentItem(edges);
          free(e);
        }
      }
      ListDestroy(&(v->edgesList));
      free(v);
    }
  }

  ListDestroy(&(g->verticesList));
  free(g);

  *p = NULL;
}

/**
 * Função responsável por criar uma cópia do grafo fornecido.
 *
 * Toma como parâmetro o ponteiro para o grafo a ser copiado. -g
 * Retorna o ponteiro para a cópia do grafo, ou NULL se a cópia não puder ser criada.
 */
Graph *GraphCopy(const Graph *g)
{
  assert(g != NULL);

  Graph *copy = GraphCreate(g->numVertices, g->isDigraph, g->isWeighted);
  if (copy == NULL)
    return NULL;

  // Copiar vértices e arestas
  List *vertices = g->verticesList;
  ListMoveToHead(vertices);
  for (unsigned int i = 0; i < g->numVertices; i++)
  {
    struct _Vertex *originalVertex = ListGetCurrentItem(vertices);
    ListMoveToNext(vertices); // Mover para o próximo vértice no grafo original

    // Copiar arestas
    List *edgesList = originalVertex->edgesList;
    ListMoveToHead(edgesList);
    for (unsigned int j = 0; j < originalVertex->outDegree; j++)
    {
      struct _Edge *originalEdge = ListGetCurrentItem(edgesList);
      ListMoveToNext(edgesList); // Mover para a próxima aresta na lista de arestas do vértice original

      // Adicionar a aresta ao grafo copiado
      if (g->isWeighted)
      {
        GraphAddWeightedEdge(copy, originalVertex->id, originalEdge->adjVertex, originalEdge->weight);
      }
      else
      {
        GraphAddEdge(copy, originalVertex->id, originalEdge->adjVertex);
      }
    }
  }

  return copy;
}

// Função responsável por criar um grafo a partir de um arquivo
// Parâmetros:
// - f: ponteiro para o arquivo contendo as informações do grafo
// Retorno:
// - Ponteiro para o grafo criado
Graph *GraphFromFile(FILE *f)
{
  assert(f != NULL);

  // Lê o tipo de grafo e se é ponderado ou não
  int isDigraph, isWeighted;
  fscanf(f, "%d", &isDigraph);
  fscanf(f, "%d", &isWeighted);

  // Lê o número de vértices e arestas
  unsigned int numVertices, numEdges;
  fscanf(f, "%u", &numVertices);
  fscanf(f, "%u", &numEdges);

  // Cria um grafo com as especificações lidas
  Graph *g = GraphCreate(numVertices, isDigraph, isWeighted);

  // Lê e adiciona as arestas
  unsigned int v1, v2;
  double weight;

  for (unsigned int i = 0; i < numEdges; i++)
  {
    if (isWeighted)
    {
      // Para grafo ponderado
      fscanf(f, "%u %u %lf", &v1, &v2, &weight);
      if (v1 != v2)
      {                               // Verifica se não é um laço
        weight = (int)(weight * 100); // Converte para inteiro
        GraphAddWeightedEdge(g, v1, v2, weight);
      }
    }
    else
    {
      // Para grafo não ponderado
      fscanf(f, "%u %u", &v1, &v2);
      if (v1 != v2)
      { // Verifica se não é um laço
        GraphAddEdge(g, v1, v2);
      }
    }
  }

  return g;
}

// Graph

int GraphIsDigraph(const Graph *g) { return g->isDigraph; }

int GraphIsComplete(const Graph *g) { return g->isComplete; }

int GraphIsWeighted(const Graph *g) { return g->isWeighted; }

unsigned int GraphGetNumVertices(const Graph *g) { return g->numVertices; }

unsigned int GraphGetNumEdges(const Graph *g) { return g->numEdges; }

//
// For a graph
//
double GraphGetAverageDegree(const Graph *g)
{
  assert(g->isDigraph == 0);
  return 2.0 * (double)g->numEdges / (double)g->numVertices;
}

static unsigned int _GetMaxDegree(const Graph *g)
{
  List *vertices = g->verticesList;
  if (ListIsEmpty(vertices))
    return 0;

  unsigned int maxDegree = 0;
  ListMoveToHead(vertices);
  unsigned int i = 0;
  for (; i < g->numVertices; ListMoveToNext(vertices), i++)
  {
    struct _Vertex *v = ListGetCurrentItem(vertices);
    if (v->outDegree > maxDegree)
    {
      maxDegree = v->outDegree;
    }
  }
  return maxDegree;
}

//
// For a graph
//
unsigned int GraphGetMaxDegree(const Graph *g)
{
  assert(g->isDigraph == 0);
  return _GetMaxDegree(g);
}

//
// For a digraph
//
unsigned int GraphGetMaxOutDegree(const Graph *g)
{
  assert(g->isDigraph == 1);
  return _GetMaxDegree(g);
}

// Vertices

//
// returns an array of size (outDegree + 1)
// element 0, stores the number of adjacent vertices
// and is followed by indices of the adjacent vertices
//
unsigned int *GraphGetAdjacentsTo(const Graph *g, unsigned int v)
{
  assert(v < g->numVertices);

  // Node in the list of vertices
  List *vertices = g->verticesList;
  ListMove(vertices, v);
  struct _Vertex *vPointer = ListGetCurrentItem(vertices);
  unsigned int numAdjVertices = vPointer->outDegree;

  unsigned int *adjacent =
      (unsigned int *)calloc(1 + numAdjVertices, sizeof(unsigned int));

  if (numAdjVertices > 0)
  {
    adjacent[0] = numAdjVertices;
    List *adjList = vPointer->edgesList;
    ListMoveToHead(adjList);
    for (unsigned int i = 0; i < numAdjVertices; ListMoveToNext(adjList), i++)
    {
      struct _Edge *ePointer = ListGetCurrentItem(adjList);
      adjacent[i + 1] = ePointer->adjVertex;
    }
  }

  return adjacent;
}

//
// returns an array of size (outDegree + 1)
// element 0, stores the number of adjacent vertices
// and is followed by the distances to the adjacent vertices
//
double *GraphGetDistancesToAdjacents(const Graph *g, unsigned int v)
{
  assert(v < g->numVertices);

  // Node in the list of vertices
  List *vertices = g->verticesList;
  ListMove(vertices, v);
  struct _Vertex *vPointer = ListGetCurrentItem(vertices);
  unsigned int numAdjVertices = vPointer->outDegree;

  double *distance = (double *)calloc(1 + numAdjVertices, sizeof(double));

  if (numAdjVertices > 0)
  {
    distance[0] = numAdjVertices;
    List *adjList = vPointer->edgesList;
    ListMoveToHead(adjList);
    for (unsigned int i = 0; i < numAdjVertices; ListMoveToNext(adjList), i++)
    {
      struct _Edge *ePointer = ListGetCurrentItem(adjList);
      distance[i + 1] = ePointer->weight;
    }
  }

  return distance;
}

//
// For a graph
//
unsigned int GraphGetVertexDegree(Graph *g, unsigned int v)
{
  assert(g->isDigraph == 0);
  assert(v < g->numVertices);

  ListMove(g->verticesList, v);
  struct _Vertex *p = ListGetCurrentItem(g->verticesList);

  return p->outDegree;
}

//
// For a digraph
//
unsigned int GraphGetVertexOutDegree(Graph *g, unsigned int v)
{
  assert(g->isDigraph == 1);
  assert(v < g->numVertices);

  ListMove(g->verticesList, v);
  struct _Vertex *p = ListGetCurrentItem(g->verticesList);

  return p->outDegree;
}

//
// For a digraph
//
unsigned int GraphGetVertexInDegree(Graph *g, unsigned int v)
{
  assert(g->isDigraph == 1);
  assert(v < g->numVertices);

  ListMove(g->verticesList, v);
  struct _Vertex *p = ListGetCurrentItem(g->verticesList);

  return p->inDegree;
}

// Edges

static int _addEdge(Graph *g, unsigned int v, unsigned int w, double weight)
{
  struct _Edge *edge = (struct _Edge *)malloc(sizeof(struct _Edge));
  edge->adjVertex = w;
  edge->weight = weight;

  ListMove(g->verticesList, v);
  struct _Vertex *vertex = ListGetCurrentItem(g->verticesList);
  int result = ListInsert(vertex->edgesList, edge);

  if (result == -1)
  {
    return 0;
  }
  else
  {
    g->numEdges++;
    vertex->outDegree++;

    ListMove(g->verticesList, w);
    struct _Vertex *destVertex = ListGetCurrentItem(g->verticesList);
    destVertex->inDegree++;
  }

  if (g->isDigraph == 0)
  {
    // Bidirectional edge
    struct _Edge *edge = (struct _Edge *)malloc(sizeof(struct _Edge));
    edge->adjVertex = v;
    edge->weight = weight;

    ListMove(g->verticesList, w);
    struct _Vertex *vertex = ListGetCurrentItem(g->verticesList);
    result = ListInsert(vertex->edgesList, edge);

    if (result == -1)
    {
      return 0;
    }
    else
    {
      // g->numEdges++; // Do not count the same edge twice on a undirected
      // graph !!
      vertex->outDegree++;
    }
  }

  return 1;
}

int GraphAddEdge(Graph *g, unsigned int v, unsigned int w)
{
  assert(g->isWeighted == 0);
  assert(v != w);
  assert(v < g->numVertices);
  assert(w < g->numVertices);

  return _addEdge(g, v, w, 1.0);
}

int GraphAddWeightedEdge(Graph *g, unsigned int v, unsigned int w,
                         double weight)
{
  assert(g->isWeighted == 1);
  assert(v != w);
  assert(v < g->numVertices);
  assert(w < g->numVertices);

  return _addEdge(g, v, w, weight);
}

// Função responsável por remover uma aresta de um grafo.
// Recebe como parâmetros um ponteiro para a estrutura do grafo (Graph *g),
// o vértice de origem da aresta (unsigned int v) e o vértice de destino da aresta (unsigned int w).
// Retorna 1 se a aresta foi removida com sucesso e 0 caso contrário.
int GraphRemoveEdge(Graph *g, unsigned int v, unsigned int w)
{
  assert(g != NULL);
  assert(v < g->numVertices);
  assert(w < g->numVertices);

  // Encontra o vértice v no grafo
  List *vertices = g->verticesList;
  ListMoveToHead(vertices);
  for (unsigned int i = 0; i < v; ListMoveToNext(vertices), i++);

  struct _Vertex *vertex = ListGetCurrentItem(vertices);

  // Encontra a aresta na lista de arestas do vértice v
  List *edgesList = vertex->edgesList;
  ListMoveToHead(edgesList);
  while (!ListIsEmpty(edgesList))
  {
    struct _Edge *edge = ListGetCurrentItem(edgesList);
    if (edge->adjVertex == w)
    {
      // Aresta encontrada, remove-a
      ListRemoveCurrent(edgesList);
      g->numEdges--;

      // Se o grafo não for direcionado, remove também a aresta reversa
      if (!GraphIsDigraph(g))
      {
        // Encontra o vértice w no grafo
        List *verticesW = g->verticesList;
        ListMoveToHead(verticesW);
        for (unsigned int i = 0; i < w; ListMoveToNext(verticesW), i++);

        struct _Vertex *vertexW = ListGetCurrentItem(verticesW);
        List *edgesListW = vertexW->edgesList;
        ListMoveToHead(edgesListW);
        while (!ListIsEmpty(edgesListW))
        {
          struct _Edge *edgeW = ListGetCurrentItem(edgesListW);
          if (edgeW->adjVertex == v)
          {
            // Aresta reversa encontrada, remove-a
            ListRemoveCurrent(edgesListW);
            vertex->outDegree--;
            vertexW->outDegree--;
            break;
          }
          ListMoveToNext(edgesListW);
        }
      }

      return 1; // Aresta removida com sucesso
    }
    ListMoveToNext(edgesList);
  }

  return 0; // Aresta não encontrada
}


// CHECKING
/**
 * Verifica as invariantes de um grafo.
 * 
 * Esta função verifica se as invariantes de um grafo são satisfeitas.
 * As invariantes verificadas são as seguintes:
 * 1. O número de arestas computadas deve ser igual ao número de arestas do grafo.
 * 2. Num grafo não orientado, o grau de entrada de um vértice deve ser zero.
 * 3. O grau de entrada de um vértice deve ser igual ao número de arestas de entrada.
 * 4. O grau de saída de um vértice deve ser igual ao número de arestas de saída.
 * 
 * Recebe como parâmetro g, o ponteiro para o grafo a ser verificado.
 * Retorna 1 se todas as invariantes são satisfeitas, 0 caso contrário.
 */
int GraphCheckInvariants(const Graph *g)
{
  assert(g != NULL);

  // Verifica se o número de arestas está correto
  unsigned int computedNumEdges = 0;
  List *vertices = g->verticesList;
  ListMoveToHead(vertices);
  for (unsigned int i = 0; i < g->numVertices; ListMoveToNext(vertices), i++)
  {
    struct _Vertex *vertex = ListGetCurrentItem(vertices);
    computedNumEdges += vertex->outDegree;
  }

  if (computedNumEdges != g->numEdges)
  {
    printf("Erro: Número incorreto de arestas\n");
    return 0;
  }

  // Verifica graus de entrada e saída
  ListMoveToHead(vertices);
  for (unsigned int i = 0; i < g->numVertices; ListMoveToNext(vertices), i++)
  {
    struct _Vertex *vertex = ListGetCurrentItem(vertices);

    if (vertex->inDegree != 0 && g->isDigraph == 0)
    {
      printf("Erro: Grau de entrada não é zero em um grafo não direcionado\n");
      return 0;
    }

    if (vertex->inDegree != ListGetSize(vertex->edgesList))
    {
      printf("Erro: Grau de entrada não corresponde ao número de arestas de entrada\n");
      return 0;
    }

    if (vertex->outDegree != ListGetSize(vertex->edgesList))
    {
      printf("Erro: Grau de saída não corresponde ao número de arestas de saída\n");
      return 0;
    }
  }

  printf("As invariantes do grafo são satisfeitas\n");
  return 1; // Todas as invariantes satisfeitas
}

// DISPLAYING on the console

void GraphDisplay(const Graph *g)
{
  printf("---\n");
  if (g->isWeighted)
  {
    printf("Weighted ");
  }
  if (g->isComplete)
  {
    printf("COMPLETE ");
  }
  if (g->isDigraph)
  {
    printf("Digraph\n");
    printf("Max Out-Degree = %d\n", GraphGetMaxOutDegree(g));
  }
  else
  {
    printf("Graph\n");
    printf("Max Degree = %d\n", GraphGetMaxDegree(g));
  }
  printf("Vertices = %2d | Edges = %2d\n", g->numVertices, g->numEdges);

  List *vertices = g->verticesList;
  ListMoveToHead(vertices);
  unsigned int i = 0;
  for (; i < g->numVertices; ListMoveToNext(vertices), i++)
  {
    printf("%2d ->", i);
    struct _Vertex *v = ListGetCurrentItem(vertices);
    if (ListIsEmpty(v->edgesList))
    {
      printf("\n");
    }
    else
    {
      List *edges = v->edgesList;
      unsigned int i = 0;
      ListMoveToHead(edges);
      for (; i < ListGetSize(edges); ListMoveToNext(edges), i++)
      {
        struct _Edge *e = ListGetCurrentItem(edges);
        if (g->isWeighted)
        {
          printf("   %2d(%4.2f)", e->adjVertex, e->weight);
        }
        else
        {
          printf("   %2d", e->adjVertex);
        }
      }
      printf("\n");
    }
  }
  printf("---\n");
}

void GraphListAdjacents(const Graph *g, unsigned int v)
{
  printf("---\n");

  unsigned int *array = GraphGetAdjacentsTo(g, v);

  printf("Vertex %d has %d adjacent vertices -> ", v, array[0]);

  for (unsigned int i = 1; i <= array[0]; i++)
  {
    printf("%d ", array[i]);
  }

  printf("\n");

  free(array);

  printf("---\n");
}