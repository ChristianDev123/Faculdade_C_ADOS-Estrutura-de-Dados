#include <stdio.h>

typedef struct Node *Link;
struct Node {
  int data;
  Link next
};

void push(Link *list, int data) {
  Link newNode = (Link)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->next = NULL;
  if(*list == NULL)
    *list = newNode;
  else{
    Link aux = *list;
    while(aux->next != NULL) aux = aux->next;
    aux->next = newNode;
  }
}

int findMinIteractive(Link list) {
  Link aux = list;
  int minData = aux->data;

  while (aux != NULL) {
    if (minData > aux->data)
      minData = aux->data;
    aux = aux->next;
  }
  return minData;
}

int findMinRecursive(Link list){
  if(list->next == NULL)
    return list->data;
  int lastData = findMinRecursive(list->next);
  if(list->data < lastData)
    return list->data;
  else return lastData;
}

int main(void) {
  Link list = NULL;
  push(&list,2);
  push(&list,1);  
  push(&list,3);

  Link aux = list;
  do{
    printf("%d\n", aux->data);
    aux = aux->next;
  }while(aux != NULL);

  printf("menor número encontrado (iterativo): %d\n\n", findMinIteractive(list));

  printf("menor número encontrado (recursivo): %d", findMinRecursive(list));
  
  return 0;
}