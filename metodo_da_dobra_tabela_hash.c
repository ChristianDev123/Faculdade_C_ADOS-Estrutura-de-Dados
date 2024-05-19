#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aluno *link;

struct Aluno {
  char *matricula; // NÃºmero de matrÃ­cula do aluno
  float cr;        // Coeficiente de Rendimento
  link prox;
};

typedef struct Aluno
    *Hash; // Hash Ã© um vetor de ponteiros para structs do tipo Aluno

void inicializar(Hash *tab, int m) {
  int i;
  for (i = 0; i < m; i++)
    tab[i] = NULL; // tab[i] Ã© um ponteiro para um struct Aluno
}

char *somaStringIndex(char *s1, char *s2, int index, int tamDobra) {
  char response[tamDobra + 1];
  int n1 = s1[index] - '0';
  int n2 = s2[index] - '0';
  int sum = n1 + n2;
  sprintf(response, "%d", sum);
  return response;
}

int somaCharSemVaiUm(char **arrToSum, int sizeArrToSum, int tamDobra) {
  char *pv, *cv;
  char *result, *partialResult;
  pv = arrToSum[0];

  for (int i = 1; i < sizeArrToSum; i++) {
    cv = arrToSum[i];
    for (int j = tamDobra; j > 0; j--) {
      partialResult = somaStringIndex(pv, cv, j - 1, tamDobra);
      partialResult = partialResult[strlen(partialResult) > 1 ? 1 : 0];
      pv[j - 1] = partialResult;
    }
  }
  return atoi(pv);
}

int hash(char *mat, int m, int tamDobra) {
  int lengthMat = strlen(mat);
  char **arrToSum = (char **)malloc(sizeof(char *) * (lengthMat / tamDobra));

  // Quebra a chave em partes, de acordo com o tamanho da dobra

  for (int i = 0; i < (lengthMat / tamDobra); i++) {
    char valorDobra[tamDobra];
    int indexValorDobra = 0;
    for (int j = i * tamDobra; j < (i + 1) * tamDobra; j++)
      valorDobra[indexValorDobra++] = mat[j];
    arrToSum[i] = malloc((strlen(valorDobra) + 1) * sizeof(char));
    strcpy(arrToSum[i], valorDobra);
  }

  int response = somaCharSemVaiUm(arrToSum, (lengthMat / tamDobra), tamDobra);
  
  for (int i = 0; i < (lengthMat / tamDobra); i++)
    free(arrToSum[i]);
  free(arrToSum);

  return response % m;
}

void inserir(Hash *tab, int m, char *mat, int tamDobra, float cr) {
  int h = hash(mat, m, tamDobra); // calcular endereÃ§o h na tabela
  link p = tab[h]; // tab[h] Ã© o endereÃ§o do primeiro elemento da lista
  link ant = NULL; // ponteiro auxiliar
  while ((p != NULL) && (p->matricula != mat)) {
    ant = p;
    p = p->prox;
  }
  if (p != NULL) // encontrou a matrÃ­cula na lista
    printf("MatrÃ­cula jÃ¡ cadastrada!\n");
  else { // alocar um novo nÃ³ para matrÃ­cula e cr do Aluno
    link novoNode = (link)malloc(sizeof(struct Aluno));
    novoNode->matricula = mat;
    novoNode->cr = cr;
    novoNode->prox = NULL;
    if (ant == NULL) // lista de tab[h] vazia, inserÃ§Ã£o no inÃ­cio
      tab[h] = novoNode;
    else // inserÃ§Ã£o no final da lista de tab[h]
      ant->prox = novoNode;
  }
}

link buscar(Hash *tab, int m, int mat, int tamDobra) {
  char *matStr;
  sprintf(matStr, "%d", mat);
  int h =
      hash(matStr, m, tamDobra); // calcular endereÃ§o h na tabela tab[0..m-1]
  link p = tab[h]; // tab[h] Ã© o endereÃ§o do primeiro elemento da lista
  while ((p != NULL) && (p->matricula != mat))
    p = p->prox;
  return p; // endereÃ§o do nÃ³ com a matrÃ­cula ou NULL se nÃ£o encontrou
}

void remover(Hash *tab, int m, int mat, int tamDobra) {
  char *matStr;
  sprintf(matStr, "%d", mat);
  int h =
      hash(matStr, m, tamDobra); // calcular endereÃ§o h na tabela tab[0..m-1]
  if (tab[h] == NULL)            // lista de tab[h] vazia
    return;
  link p = tab[h]; // tab[h] Ã© o endereÃ§o do primeiro elemento da lista
  link ant = NULL; // ponteiro auxiliar
  while ((p != NULL) && (p->matricula != mat)) {
    ant = p;
    p = p->prox;
  }
  if (p == NULL) { // nÃ£o encontrou a matrÃ­cula na lista
    printf("MatrÃ­cula nÃ£o cadastrada!\n");
    return;
  }
  if (ant == NULL) // encontrou a matrÃ­cula no primeiro nÃ³ da lista
    tab[h] = p->prox;
  else // encontrou a matrÃ­cula no nÃ³ p diferente do primeiro nÃ³
    ant->prox = p->prox;
  printf("mat = %d , cr = %.1f foi removido!\n", p->matricula, p->cr);
  free(p);
}

void imprimir(Hash *tab, int m) {
  for (int i = 0; i < m; i++) // percorrer a tabela tab[0..m-1]
    if (tab[i] != NULL) {     // lista de tab[i] nÃ£o vazia
      link p = tab[i]; // endereÃ§o do primeiro elemento da lista em tab[i]
      printf("tab[%d]: ", i); //Ã­ndice da tabela tab[0..m-1]
      while (p != NULL) {     // imprimir a lista de tab[i]
        printf("mat = %s , cr = %.1f -> ", p->matricula, p->cr);
        p = p->prox;
      }
      printf("NULL\n"); // terminou de imprimir lista de tab[i]
    } else              // lista de tab[i] vazia
      printf("tab[%d]: NULL\n", i);
}

int main(void) {
  const int m = 50;
  const int tamDobra = 2;
  char *mat = "52936410";
  Hash tab[m];
  inicializar(tab, m);
  inserir(tab, m, mat, tamDobra, 1);
  imprimir(tab, m);
  return 0;
}
