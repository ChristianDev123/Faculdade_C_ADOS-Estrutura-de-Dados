#include <stdio.h>
#include <math.h>
#include <time.h>

const int MAX = 100;

typedef struct Conta *Link;
struct Conta{
  int num;
  Link next;
};
typedef struct Conta *Hash;

int hash(int n){
  double a = (n*(pow(5,0.5)-1/2));
  a = a - (int)a;
  return MAX * a;
}
void constructor(Hash *hashTab){
  for(int i = 0; i < MAX; i++)
    hashTab[i] = NULL;
}

void inserir(Hash *hashTab, int numConta){
  int indexHash = hash(numConta);
  Link accountList = hashTab[indexHash];
  Link aux = NULL;
  while(accountList != NULL && accountList->num != numConta){
    aux = accountList;
    accountList = accountList->next;
  }
  if(accountList != NULL)
    printf("Conta já existente\n");
  else{
    Link newNode = (Link)malloc(sizeof(struct Conta));
    newNode->num = numConta;
    newNode->next = NULL;
    if(aux == NULL) hashTab[indexHash] = newNode;
    else
      aux->next = newNode;
  }
}

Link search(Hash *hashTab, int numConta){
  int indexHash = hash(numConta);
  Link aux = hashTab[indexHash];
  while(aux!=NULL && aux->num != numConta)
    aux = aux->next;
  return aux;
}

void removeElement(Hash *hashTab, int numConta){
  int indexHash = hash(numConta);
  if(hashTab[indexHash] == NULL)
    return;
  Link auxNext = hashTab[indexHash];
  Link aux = NULL;
  while(auxNext != NULL && auxNext->num!= numConta){
    aux = auxNext;
    auxNext = auxNext->next;
  }
  if(auxNext == NULL){
    printf("Conta não encontrada!\n");
    return;
  }
  if(aux == NULL)
    hashTab[indexHash] = auxNext->next;
  else
    aux->next = auxNext->next;
  printf("Conta removida com sucesso!");
  free(auxNext);
}

void printHashTable(Hash *hashTab){
  for(int i = 0; i < MAX; i++){
    if(hashTab[i] != NULL){
      Link aux = hashTab[i];
      printf("[%d]: ",i);
      while(aux != NULL){
        printf("conta: %d ->", aux->num);
        aux = aux->next;
      }
      printf("NULL\n");
    }
    else
      printf("[%d]: NULL\n", i);
  }
}

int main(void) {
  Hash hashTab[MAX];
  constructor(hashTab);

  srand(time(NULL));
  int numConta;
  for(int i = 0; i < MAX; i++){
    numConta = rand() % 10000 + 1;
    inserir(hashTab, numConta);
  }
  printHashTable(hashTab);
  
  return 0;
}