#include "grafo.h"
#include "fila.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Criar um grafo com um nÃºmero especÃ­fico de vÃ©rtices
Grafo *criarGrafo(int numVertices) {
  Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
  grafo->numVertices = numVertices;

  // Alocar memÃ³ria para o vetor de listas de adjacÃªncia
  grafo->listaAdj = (linkGrafo *)malloc(numVertices * sizeof(linkGrafo));
  for (int i = 0; i < numVertices; i++) {
    grafo->listaAdj[i] = NULL; // Listas vazias, inicialmente
  }
  return grafo;
}

// Adicionar uma aresta orientada e ponderada ao grafo
void adicionarAresta(Grafo *grafo, int origem, int destino, int peso) {
  // Criar um novo nÃ³ com o destino e o peso
  linkGrafo novo = (linkGrafo)malloc(sizeof(struct node));
  novo->destino = destino;
  novo->peso = peso;
  novo->next = grafo->listaAdj[origem];

  // Atualizar a lista de adjacÃªncia da origem
  grafo->listaAdj[origem] = novo;
}

// Imprimir as listas de adjacÃªncia do grafo
void imprimirListasAdjacencia(Grafo *grafo) {
  printf("Listas de AdjacÃªncia:\n");
  for (int i = 0; i < grafo->numVertices; i++) {
    printf("VÃ©rtice %d: ", i);
    linkGrafo p = grafo->listaAdj[i];
    while (p != NULL) { // Existe aresta de i para j
      printf("(%d, %d) ", p->destino, p->peso);
      p = p->next;
    }
    printf("\n");
  }
}

// Imprimir o grafo
void imprimirGrafo(Grafo *grafo) {
  printf("Grafo orientado (VÃ©rtices adjacentes):\n");
  for (int i = 0; i < grafo->numVertices; i++) {
    printf("VÃ©rtice %d: ", i);
    bool primeiro = true;
    linkGrafo p = grafo->listaAdj[i];
    while (p != NULL) { // Existe aresta de i para j
      if (primeiro == false)
        printf(", ");
      printf("(%d, %d)", p->destino, p->peso);
      primeiro = false;
      p = p->next;
    }
    printf("\n");
  }
}

void iniciarlizarBusca(Grafo *grafo) {
  for (int i = 0; i < grafo->numVertices; i++) {
    grafo->listaAdj[i]->cor = BRANCO;
    grafo->listaAdj[i]->pai = NULL;
    grafo->listaAdj[i]->distancia = -1;
  }
}

void imprimirArvoreBFS(Grafo grafo) {
  linkGrafo aux;
  for (int i = 0; i < grafo.numVertices; i++) {
    aux = grafo.listaAdj[i];
    if (aux->pai != NULL)
      printf("%d possui pai\n", i);
    else
      printf("%d não possui pai\n", i);
  }
}

void empilharAdjacentes(Queue *queue, linkGrafo *node, linkGrafo pai) {
  enqueue(queue, *node);
  (*node)->cor = CINZA;
  (*node)->distancia = pai->distancia + 1;
  (*node)->pai = pai;
}

void buscaEmLargura(Grafo grafo, int init) {
  Queue queue;
  constructor(&queue);
  iniciarlizarBusca(&grafo);
  linkGrafo aux, copyAux;
  /*configura e empilha os adjacentes do node inicial*/
  enqueue(&queue, grafo.listaAdj[init]);
  aux = grafo.listaAdj[init]->next;
  grafo.listaAdj[init]->cor = CINZA;
  grafo.listaAdj[init]->distancia = 0;
  while (aux != NULL) {
    empilharAdjacentes(&queue, &aux, grafo.listaAdj[init]);
    aux = aux->next;
  }
  /*empilha os adjacentes dos nodes adjacentes*/
  while (queue.count != 0) {
    dequeue(&queue, &copyAux);
    copyAux->cor = PRETO;
    aux = grafo.listaAdj[copyAux->destino];
    while (aux != NULL) {
      if (aux->cor == BRANCO) {
        empilharAdjacentes(&queue, &aux, copyAux);
        aux = aux->next;
      } else
        break;
    }
  }
  imprimirArvoreBFS(grafo);
}