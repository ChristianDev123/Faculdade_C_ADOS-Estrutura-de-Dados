#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// RepresentaÃ§Ã£o de um nÃ³ da lista de adjacÃªncia


// RepresentaÃ§Ã£o de um grafo usando listas de adjacÃªncia
typedef struct {
    int numVertices;
    int **matrizAdj; // Vetor de ponteiros/listas
} Grafo;

// Cores para a busca em profundidade
typedef enum {BRANCO, CINZA, PRETO} cores;

// VariÃ¡vel global para rastrear o tempo durante a DFS
int tempo = 0;

// Criar um grafo com um nÃºmero especÃ­fico de vÃ©rtices
Grafo *criarGrafo(int numVertices) {
    Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = numVertices;

    // Alocar memÃ³ria para a matriz de adjacÃªncia
    grafo->matrizAdj = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        grafo->matrizAdj[i] = (int*)malloc(numVertices * sizeof(int));
        for (int j = 0; j < numVertices; j++) // Inicializar a matriz com zeros
            grafo->matrizAdj[i][j] = 0; // 0 significa ausÃªncia de aresta
    }
    return grafo;
}

// Adicionar uma aresta orientada ao grafo
void adicionarAresta(Grafo *grafo, int origem, int destino) {
    grafo->matrizAdj[origem][destino] = 1;
}

// Imprimir o grafo
void imprimirMatrizAdjacencia(Grafo *grafo) {
    printf("Matriz de AdjacÃªncia:\n");
    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->numVertices; j++) {
            printf("%d\t", grafo->matrizAdj[i][j]);
        }
        printf("\n");
    }
}

void imprimeArvoreDFS(Grafo *grafo, int *pai) {
    printf("\nÃrvore DFS:\n");
    for (int i = 0; i < grafo->numVertices; i++) 
        if (pai[i] != -1) 
            printf("Pai de %d Ã© %d\n", i, pai[i]);
        else 
            printf("Pai de %d Ã© ninguÃ©m\n", i);
} 

// FunÃ§Ã£o DFS_Visit auxiliar para visita dos vÃ©rtices
void DFS_Visit(Grafo *grafo, int vertice, cores *cor, int *pai, int *d, int *f) {
    cor[vertice]= CINZA; // Marcar o vÃ©rtice como cinza (visitando)
    d[vertice] = ++tempo; // Registrar o tempo de descoberta
    printf("Visitando vÃ©rtice %d no tempo %d\n", vertice, d[vertice]);

    for(int i = 0; i < grafo->numVertices; i++)
      for(int j = 0; j < grafo->numVertices; j++){
        if(grafo->matrizAdj[i][j] != 0 && cor[j] == BRANCO){
          pai[j] = i;
          DFS_Visit(grafo, j, cor, pai, d, f);
        }
      }
  
    cor[vertice] = PRETO; // Marcar o vÃ©rtice como preto (visitado completamente)
    f[vertice] = ++tempo; // Registrar o tempo de finalizaÃ§Ã£o
    printf("** Finalizando vÃ©rtice %d no tempo %d\n", vertice, f[vertice]);
}

// Busca em profundidade (DFS) no grafo
void DFS(Grafo *grafo) {
    cores cor[grafo->numVertices];
    int pai[grafo->numVertices];
    int d[grafo->numVertices]; // Vetor de tempos de descoberta
    int f[grafo->numVertices]; // Vetor de tempos de finalizaÃ§Ã£o

    // Inicializar todos os vÃ©rtices como brancos e sem pai
    for (int i = 0; i < grafo->numVertices; i++) {
        cor[i] = BRANCO;
        pai[i] = -1; //Equivalente a NULL
        d[i] = 0;
        f[i] = 0;
    }

    // Percorrer todos os vÃ©rtices do grafo
    for (int i = 0; i < grafo->numVertices; i++) 
        if (cor[i] == BRANCO) // Chamar DFS_Visit para cada vÃ©rtice nÃ£o visitado
            DFS_Visit(grafo, i, cor, pai, d, f);    

    // Imprimir a Ã¡rvore DFS usando o vetor pai
    imprimeArvoreDFS(grafo, pai);

    // Imprimir os tempos de descoberta e finalizaÃ§Ã£o
    printf("\nTempos de Descoberta e FinalizaÃ§Ã£o:\n");
    for (int i = 0; i < grafo->numVertices; i++) 
        printf("VÃ©rtice %d: d[%d] = %d, f[%d] = %d\n", i, i, d[i], i, f[i]);
}

void imprimirGrafo(Grafo *grafo) {
    printf("Grafo orientado (VÃ©rtices adjacentes):\n");
    for (int i = 0; i < grafo->numVertices; i++) {
        printf("VÃ©rtice %d: ", i);
        bool primeiro = true;
        for (int j = 0; j < grafo->numVertices; j++) {
            if (grafo->matrizAdj[i][j] != 0) { // Existe aresta de i para j
                if (primeiro == false) printf(", ");
                printf("(%d, %d)", j, grafo->matrizAdj[i][j]);
                primeiro = false;
            }
        }
        printf("\n");
    }
}

int main(void) {
    int numVertices = 8; // NÃºmero de vÃ©rtices do grafo

    // Criar um grafo com 8 vÃ©rtices
    Grafo* grafo = criarGrafo(numVertices);

    // Adicionar arestas ao grafo (exemplo da aula)
    adicionarAresta(grafo, 0, 4);    
    adicionarAresta(grafo, 0, 3);
    adicionarAresta(grafo, 0, 1);
    adicionarAresta(grafo, 1, 3);
    adicionarAresta(grafo, 1, 2);    
    adicionarAresta(grafo, 2, 0);
    adicionarAresta(grafo, 3, 2);
    adicionarAresta(grafo, 4, 5);
    adicionarAresta(grafo, 4, 3);
    adicionarAresta(grafo, 5, 3);
    adicionarAresta(grafo, 6, 7);
    adicionarAresta(grafo, 6, 4);
    adicionarAresta(grafo, 6, 5);
    adicionarAresta(grafo, 7, 3);

    // Imprimir o grafo
    imprimirGrafo(grafo);   

    printf("\n");

    // Executar a busca em profundidade
    printf("Busca em Profundidade (DFS):\n");
    DFS(grafo);

    return 0;
}
