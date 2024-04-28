#include <stdio.h>
#include <stdbool.h>

#define MAX 100 //tamanho mÃ¡ximo do heap/vetor

int pai(int i) {
    return i/2;
}

int esq(int i) {
    return 2*i;
}

int dir(int i) {
    return 2*i+1;
}

void subir(int *heap, int i) {
     int aux;
     int p = pai(i);
     if (p >= 1) { //se i nÃ£o Ã© a raiz pai(i) >= 1
        if (heap[i] > heap[p]) {
           //sobe no heap/vetor trocando pai e filho
           aux = heap[i];
           heap[i] = heap[p];
           heap[p] = aux;
          subir(heap, p);
        }
     }
}

void inserir(int *heap, int *n, int novoItem) {
     //aumenta o tamanho do heap/vetor
     *n = *n + 1;
     heap[*n] = novoItem;
     //sobe o Ãºltimo elemento do heap/vetor
     subir(heap, *n);
}

void descer(int *heap, int n, int i) {
     int aux;
     //descobrir quem Ã© o maior filho de i
     int e = esq(i); //filho esquerdo
     int d = dir(i); //filho direito
     int maior = i; //inicialmente o maior Ã© o pai
     if ((e <= n) && (heap[e] > heap[i]))
        maior = e; //filho da esquerda maior que o pai
     if ((d <= n) && (heap[d] > heap[maior]))
        maior = d; //filho da direita maior que o maior
     if (maior != i) { //se o maior nÃ£o Ã© o pai
        //desce trocando o pai com o maior filho
        aux = heap[i];
        heap[i] = heap[maior];
        heap[maior] = aux;
        descer(heap, n, maior);
      }
}

int removerMaximo(int *heap, int *n) {
    int maximo = heap[1]; //maior elemento do heap/vetor
    heap[1] = heap[*n]; //coloca o Ãºltimo elemento na raiz
    //diminui o tamanho do heap/vetor
    *n = *n - 1;
    //desce o elemento na raiz do heap/vetor
    descer(heap, *n, 1);
    //retorna o maior elemento do heap/vetor
    return maximo;
}

void imprimirHeap(int *heap, int n, int i, int b) {
     int j;
     if (i > n) {
        for (j = 0; j < b; j++) printf("-----");
        printf("NULL\n");
        return;
     }
     imprimirHeap(heap, n, dir(i), b + 1);
     for (j = 0; j < b; j++) printf("-----");
     printf("%i\n", heap[i]);
     imprimirHeap(heap, n, esq(i), b + 1);
}

void constroiHeapDescendo(int *heap, int n) {
     int i;
     int j = n/2;
     for (i = j; i >= 1;i--)
         descer(heap, n, i);
} 

void constroiHeapSubindo(int *heap, int n) {
     int i;  
     for (i = 2; i <= n; i++) 
         subir(heap, i);
}

void heapSort(int *heap, int n) {
     int i;
     int aux;

     constroiHeapDescendo(heap, n); //constroiHeapSubindo(heap, n);
     for (i = n; i > 1; i--){
         //troca raiz (mÃ¡ximo) com o Ãºltimo elemento do heap
         aux = heap[i];
         heap[i] = heap[1];
         heap[1] = aux;
         //diminui o tamanho a ser considerado no heap
         n = n - 1;
         //desce com a raiz nesse novo heap de tamanho n-1
         descer(heap, n, 1);
      }
}

bool isMaxHeap(int *heap, int n){
  int left=1, right=1, father = 1;
  bool response = true;

  while(left < n){
    left = esq(father);
    right = dir(father);
    printf("pai: %d\n esq:%d\t dir:%d \n\n", heap[father], heap[left], heap[right]);
    if(heap[father] < heap[left] && heap[father] < heap[right])
      response = false;
    father = left;
  }
  
  father = 1, right = 1;
  
  while(right < n){
    left = esq(father);
    right = dir(father);
    printf("pai: %d\n esq:%d\t dir:%d \n\n", heap[father], heap[left], heap[right]);
    if(heap[father] < heap[left] && heap[father] < heap[right])
      response = false;
    father = right;
  }
  return response;
}

int main(void) {
    int heap[MAX]; //vamos considerar um heap/vetor de inteiros
    int chave;
    int n = 0; //heap/vetor inicia com 0 elementos

    inserir(heap, &n, 17);
    inserir(heap, &n, 15);
    inserir(heap, &n, 12);
    inserir(heap, &n, 9);
    inserir(heap, &n, 10);
    inserir(heap, &n, 4);
    inserir(heap, &n, 1);
    inserir(heap, &n, 7);
    inserir(heap, &n, 3);
    inserir(heap, &n, 6);

    // imprimirHeap(heap, n, 1, 0);
    // printf("\nExtrair maior elemento do heap: %d\n\n", removerMaximo(heap, &n));

    imprimirHeap(heap, n, 1, 0);
    printf("\n\n %s", isMaxHeap(heap, n)?"é um heap de máximo!":"não é um heap de máximo!");
    // int vetor[11] = {100, 16, 22, 45, 99, 11, 27, 13, 34, 85, 76}; 

    // heapSort(vetor, 11); //vetor[0] nÃ£o Ã© usado

    // printf("\nVetor ordenado com Heapsort:\n");
    // for (int i = 0; i <= 10; i++) printf("%d ", vetor[i]);

  return 0;
}