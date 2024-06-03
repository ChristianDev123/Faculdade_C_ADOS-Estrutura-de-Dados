#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grafo.h"
#include "fila.h"

int main(void) {
    int numVertices = 5; 
    Grafo* grafo = criarGrafo(numVertices);

    adicionarAresta(grafo, 0, 1, 2);
    adicionarAresta(grafo, 1, 3, 4);
    adicionarAresta(grafo, 2, 0, 12);
    adicionarAresta(grafo, 2, 4, 40);
    adicionarAresta(grafo, 3, 1, 3);
    adicionarAresta(grafo, 4, 3, 8);

    imprimirListasAdjacencia(grafo);
    printf("\n");

    // imprimirGrafo(grafo);
    // printf("\n");

    buscaEmLargura(*grafo, 2);
    
    return 0;
}
