#ifndef GRAFO_H
#define GRAFO_H

typedef struct node *linkGrafo;

// RepresentaÃ§Ã£o de um nÃ³ da lista de adjacÃªncia
typedef enum { PRETO, CINZA, BRANCO } Cores;

struct node {
  int destino;
  Cores cor;
  int distancia;
  linkGrafo pai;
  linkGrafo next;
};

// RepresentaÃ§Ã£o de um grafo usando lista de adjacÃªncia
typedef struct {
  int numVertices;
  linkGrafo *listaAdj; // Vetor de ponteiros/listas
} Grafo;

Grafo *criarGrafo(int numVertices);
void adicionarAresta(Grafo *grafo, int origem, int destino, int peso);
void imprimirListasAdjacencia(Grafo *grafo);
void imprimirGrafo(Grafo *grafo);
void buscaEmLargura(Grafo grafo, int init);

#endif