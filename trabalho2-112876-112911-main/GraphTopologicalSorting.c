//
// Algoritmos e Estruturas de Dados --- 2023/2024
//
// Topological Sorting
//

#include "GraphTopologicalSorting.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersQueue.h"
#include "instrumentation.h"
  

struct _GraphTopoSort {
  int* marked;                     // Aux array
  unsigned int* numIncomingEdges;  // Aux array
  unsigned int* vertexSequence;    // The result
  int validResult;                 // 0 or 1
  unsigned int numVertices;        // From the graph
  Graph* graph;
};

// AUXILIARY FUNCTION
// Allocate memory for the struct
// And for its array fields
// Initialize all struct fields
//
/**
 * Cria uma estrutura GraphTopoSort a partir de um grafo fornecido.
 *
 * Toma como parâmetro g - O grafo a partir do qual a estrutura GraphTopoSort será criada.
 * Retorna um ponteiro para a estrutura GraphTopoSort criada, ou NULL em caso de falha na alocação de memória.
 */
static GraphTopoSort* _create(Graph* g) {
  assert(g != NULL);

  GraphTopoSort* p = (GraphTopoSort*)malloc(sizeof(GraphTopoSort));
  if (p == NULL) {
    printf("Erro: Falha na alocação de memória para GraphTopoSort.\n");
    return NULL;
  }

  // Inicializa os campos da estrutura
  p->numVertices = GraphGetNumVertices(g);
  p->graph = g;
  p->validResult = 0; // Inicialmente, não há um resultado válido

  // Aloca memória para os arrays
  p->marked = (int*)calloc(p->numVertices, sizeof(int));
  p->numIncomingEdges = (unsigned int*)malloc(p->numVertices * sizeof(unsigned int));
  p->vertexSequence = (unsigned int*)malloc(p->numVertices * sizeof(unsigned int));

  if (!p->marked || !p->numIncomingEdges || !p->vertexSequence) {
    free(p->marked);
    free(p->numIncomingEdges);
    free(p->vertexSequence);
    free(p);
    printf("Erro: Falha na alocação de memória para os arrays em GraphTopoSort.\n");
    return NULL;
  }

  // Inicializa numIncomingEdges
  for (unsigned int i = 0; i < p->numVertices; i++) {
    p->numIncomingEdges[i] = GraphGetVertexInDegree(g, i);
  }

  return p;
}

//
// Computing the topological sorting, if any, using the 1st algorithm:
// 1 - Create a copy of the graph
// 2 - Successively identify vertices without incoming edges and remove their
//     outgoing edges
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
/**
 * Explicação Algoritmos Ordenação Topológica:
 * As funções recebem um grafo direcionado como entrada e calculam a sua ordenação topológica. 
 * A ordenação topológica é uma ordenação linear dos vértices do grafo de tal forma que, 
 * para cada aresta (u, v), o vértice u aparece antes do vértice v na ordenação.
 *
 * Explicação Algortimo:
 * A função utiliza o algoritmo de busca em largura para realizar a ordenação topológica. 
 * O algoritmo começa por criar uma cópia do grafo original e inicializa uma estrutura de 
 * dados para armazenar a ordenação topológica. Em seguida, o algoritmo itera sobre os vértices
 * do grafo, procurando por vértices que não possuam arestas de entrada. Quando um destes vértices 
 * é encontrado, vai ser adicionado à sequência de vértices da ordenação topológica e as suas 
 * arestas de saída são removidas da cópia do grafo. Este processo é repetido até que todos os vértices
 * tenham sido adicionados à ordenação topológica ou até que não seja possível encontrar mais vértices sem arestas de entrada.
 *
 * Explicação Função:
 * Calcula a ordenação topológica de um grafo direcionado usando a versão 1 do Algoritmo das teóricas.
 * @param g O grafo direcionado de entrada.
 * @return Um ponteiro para a estrutura GraphTopoSort que contém a ordenação
 *         topológica do grafo. Se ocorrer algum erro durante a execução da função,
 *         o valor de retorno será NULL.
 */
GraphTopoSort* GraphTopoSortComputeV1(Graph* g) {
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Cria uma estrutura GraphTopoSort a partir do grafo fornecido
  GraphTopoSort* topoSort = _create(g);
  if (topoSort == NULL) {
    return NULL;
  }

  // Cria uma cópia do grafo original
  Graph* gCopy = GraphCopy(g);
  if (gCopy == NULL) {
    GraphTopoSortDestroy(&topoSort);
    return NULL;
  }

  unsigned int count = 0;
  while (count < topoSort->numVertices) {
    int found = 0;
    for (unsigned int v = 0; v < topoSort->numVertices; v++) {
      // Verifica se o vértice ainda não foi marcado e não possui arestas de entrada
      if (!topoSort->marked[v] && topoSort->numIncomingEdges[v] == 0) {
        // Adiciona o vértice à sequência de vértices da ordenação topológica
        topoSort->vertexSequence[count++] = v;
        topoSort->marked[v] = 1;
        found = 1;

        // Remove o vértice e suas arestas de saída da cópia do grafo
        unsigned int* adjacents = GraphGetAdjacentsTo(gCopy, v);
        for (unsigned int i = 1; i <= adjacents[0]; i++) {
          GraphRemoveEdge(gCopy, v, adjacents[i]);
          // Decrementa o grau de entrada dos vértices adjacentes
          topoSort->numIncomingEdges[adjacents[i]]--;
        }
        free(adjacents);
        break;
      }
    }
    if (!found) {
      topoSort->validResult = 0;
      break;
    }
  }

  GraphDestroy(&gCopy); // Garante que a cópia do grafo seja destruída
  topoSort->validResult = (count == topoSort->numVertices);
  return topoSort;
}

//
// Computing the topological sorting, if any, using the 2nd algorithm
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
/**
 * Explicação Algortimo:
 * O algoritmo de ordenação topológica V2 também utiliza o algoritmo de busca em largura para realizar a ordenação. 
 * Este começa por criar uma estrutura GraphTopoSort a partir do grafo fornecido e em seguida, vai iterar sobre 
 * os vértices do grafo, procurando aqueles que ainda não foram marcados nem possuam arestas de entrada. 
 * Quando um vértice é encontrado, este é adicionado à sequência de vértices da ordenação topológica. 
 * Além disso, o grau de entrada dos vértices adjacentes a esse vértice é atualizado, decrementando 
 * o valor do grau de entrada, sendo o processo repetido até que todos os vértices tenham sido adicionados 
 * à ordenação topológica ou até que não seja possível encontrar mais vértices sem arestas de entrada.
 * 
 * Explicação Função:
 * Calcula a ordenação topológica de um grafo direcionado usando a versão 2 do Algoritmo das teóricas.
 * @param g O grafo a ser processado.
 * @return Um ponteiro para a estrutura GraphTopoSort que contém a sequência de vértices ordenados topologicamente.
 *         Retorna NULL em caso de falha na criação da estrutura.
 */
GraphTopoSort* GraphTopoSortComputeV2(Graph* g) {
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Cria uma estrutura GraphTopoSort a partir do grafo fornecido
  GraphTopoSort* topoSort = _create(g);
  if (topoSort == NULL) {
    return NULL;
  }

  unsigned int count = 0;

  while (count < topoSort->numVertices) {
    int found = 0;
    for (unsigned int v = 0; v < topoSort->numVertices; v++) {
      
      // Verifica se o vértice ainda não foi marcado e não possui arestas de entrada
      if (!topoSort->marked[v] && topoSort->numIncomingEdges[v] == 0) {
        // Adiciona o vértice à sequência de vértices da ordenação topológica
        topoSort->vertexSequence[count++] = v;
        topoSort->marked[v] = 1;
        found = 1;
        // Atualiza o grau de entrada para os vértices adjacentes
        unsigned int* adjacents = GraphGetAdjacentsTo(g, v);
        for (unsigned int i = 1; i <= adjacents[0]; i++) {
          // Decrementa o grau de entrada dos vértices adjacentes
          topoSort->numIncomingEdges[adjacents[i]]--;
        }
        free(adjacents);
        break;
      }
    }
    if (!found) {
      topoSort->validResult = 0;
      break;
    }
  }

  topoSort->validResult = (count == topoSort->numVertices);
  return topoSort;
}


//
// Computing the topological sorting, if any, using the 3rd algorithm
// Check if a valid sorting was computed and set the isValid field
// For instance, by checking if the number of elements in the vertexSequence is
// the number of graph vertices
//
/**
 * Explicação Algortimo:
 * O algoritmo de ordenação topológica V3 também utiliza o algoritmo de busca em largura, mas 
 * com uma abordagem um pouco diferente. Este começa por criar uma estrutura GraphTopoSort a 
 * partir do grafo fornecido, e de seguida cria uma fila para armazenar os vértices sem arestas 
 * de entrada. Os vértices sem arestas de entrada são depois enfileirados, após o qual o algoritmo 
 * entra num loop enquanto a fila não estiver vazia. Em cada iteração do loop, um vértice é removido 
 * da fila e adicionado à sequência de vértices da ordenação topológica. Em seguida, o algoritmo 
 * decrementa o grau de entrada dos vértices adjacentes a esse vértice e enfileira os vértices cujo 
 * grau de entrada seja igual a zero, sendo este processo repetido até que a fila esteja vazia. 
 * Por fim, o algoritmo verifica se a ordenação topológica obtida é válida, ou seja, se o número de 
 * vértices na sequência de vértices obtida é igual ao número de vértices do grafo original.
 * 
 * Explicação Função:
 * Calcula a ordenação topológica de um grafo direcionado usando a versão 3 do Algoritmo das teóricas.
 * @param g O grafo a ser processado.
 * @return Um ponteiro para a estrutura GraphTopoSort que contém a sequência de vértices ordenados topologicamente.
 *         Retorna NULL em caso de falha na criação da estrutura ou na alocação de memória.
 */
GraphTopoSort* GraphTopoSortComputeV3(Graph* g) {
  assert(g != NULL && GraphIsDigraph(g) == 1);

  // Cria uma estrutura GraphTopoSort a partir do grafo fornecido
  GraphTopoSort* topoSort = _create(g);
  if (topoSort == NULL) {
    return NULL;
  }

  // Cria uma fila para armazenar os vértices sem arestas de entrada
  Queue* queue = QueueCreate(topoSort->numVertices);
  if (queue == NULL) {
    GraphTopoSortDestroy(&topoSort);
    return NULL;
  }

  // Enfileira os vértices sem arestas de entrada
  for (unsigned int v = 0; v < topoSort->numVertices; v++) {
    if (topoSort->numIncomingEdges[v] == 0) {
      QueueEnqueue(queue, v);
    }
  }

  unsigned int count = 0;
  while (!QueueIsEmpty(queue)) {
    // Remove um vértice da fila
    int v = QueueDequeue(queue);
    // Adiciona o vértice à sequência de vértices da ordenação topológica
    topoSort->vertexSequence[count++] = v;

    // Decrementa o grau de entrada dos vértices adjacentes e enfileira caso o grau de entrada seja igual a zero
    unsigned int* adjacents = GraphGetAdjacentsTo(g, v);
    for (unsigned int i = 1; i <= adjacents[0]; i++) {
      unsigned int w = adjacents[i];
      if (--topoSort->numIncomingEdges[w] == 0) {
        QueueEnqueue(queue, w);
      }
    }
    free(adjacents);
  }

  // Liberta a memória utilizada pela fila
  QueueDestroy(&queue);

  // Verifica se a ordenação topológica é válida
  topoSort->validResult = (count == topoSort->numVertices);
  return topoSort;
}


void GraphTopoSortDestroy(GraphTopoSort** p) {
  assert(*p != NULL);

  GraphTopoSort* aux = *p;

  free(aux->marked);
  free(aux->numIncomingEdges);
  free(aux->vertexSequence);

  free(*p);
  *p = NULL;
}

//
// A valid sorting was computed?
//
int GraphTopoSortIsValid(const GraphTopoSort* p) { return p->validResult; }

//
// Getting an array containing the topological sequence of vertex indices
// Or NULL, if no sequence could be computed
// MEMORY IS ALLOCATED FOR THE RESULTING ARRAY
//
// Função responsável por obter uma cópia da sequência topológica de índices dos vértices, se esta puder ser calculada.
// A função recebe como parâmetro um ponteiro para a estrutura GraphTopoSort e retorna um ponteiro para um array
// de unsigned int contendo a cópia da sequência topológica, ou NULL se a sequência não puder ser calculada.
unsigned int* GraphTopoSortGetSequence(const GraphTopoSort* p) {
  assert(p != NULL);

  // Verifica se a sequência topológica é válida
  if (!p->validResult) {
    return NULL;
  }

  // Aloca memória para a cópia da sequência topológica
  unsigned int* sequenceCopy = (unsigned int*)malloc(p->numVertices * sizeof(unsigned int));
  if (!sequenceCopy) {
    return NULL;
  }

  // Copia os elementos da sequência original para a cópia
  for (unsigned int i = 0; i < p->numVertices; i++) {
    sequenceCopy[i] = p->vertexSequence[i];
  }

  // Retorna a cópia da sequência topológica
  return sequenceCopy;
}

// DISPLAYING on the console

//
// The toplogical sequence of vertex indices, if it could be computed
//
void GraphTopoSortDisplaySequence(const GraphTopoSort* p) {
  assert(p != NULL);

  if (p->validResult == 0) {
    printf(" *** The topological sorting could not be computed, not a DAG Graph!! *** \n");
    return;
  }

  printf("Topological Sorting - Vertex indices:\n");
  for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++) {
    printf("%d ", p->vertexSequence[i]);
  }
  printf("\n");
}

//
// The toplogical sequence of vertex indices, if it could be computed
// Followed by the digraph displayed using the adjecency lists
// Adjacency lists are presented in topologic sorted order
//
void GraphTopoSortDisplay(const GraphTopoSort* p) {
  assert(p != NULL);

  // The topological order
  GraphTopoSortDisplaySequence(p);

  if (p->validResult == 0) {
    return;
  }

  // The Digraph
  for (unsigned int i = 0; i < GraphGetNumVertices(p->graph); i++) {
    GraphListAdjacents(p->graph, p->vertexSequence[i]);
  }
  printf("\n");
}
