#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int checkArraySort(int *array, int size) {
  /*
    (resposta e sortAuxArr):
    1 - desordenado
    2 - ordem crescente
    3 - ordem decrescente
    4 - constante
  */
  int auxArr[size]; // array auxiliar que determina se o array principal está em ordem crescente, decrescente ou desordenado;
  int indexAuxArr = 0; // index do array auxiliar
  int response = 4;    // resposta do algoritmo
  for (int i = 1; i < size; i++) {
    if (array[i - 1] != array[i]) {
      response = array[i - 1] <= array[i] ? 2 : 3;
      auxArr[indexAuxArr] = response;
      indexAuxArr++;
    }
  }

  if (response != 4) {
    int auxResponse = auxArr[0];
    for (int i = 0; i < indexAuxArr; i++) {
      if (auxResponse != auxArr[i])
        response = 1;
    }
    if (response != 1)
      response = auxResponse;
  }

  return response;
}

int main(void) {
  // int testArray [5] = {1,2,3,4,5};  
  // int testArray [5] = {5,4,3,2,1};
  // int testArray [5] = {2,2,2,2,2};
  
  int testArray[5];
  srand(time(NULL));
  printf("[ ");
  for(int i = 0; i < 5; i++){
    testArray[i] = rand() % 10;
    printf("%d ", rand() % 10);
  }
  printf("]");
  
  printf("\n\n");
  printf("o valor de ordenação do vetor é %d", checkArraySort(testArray, 5));
  return 0;
}