#include <stdio.h>

typedef struct NodeQueue *LinkQueue;
typedef struct NodeTree *LinkTree;
struct NodeQueue {
  LinkTree data;
  LinkQueue next;
};
struct NodeTree {
  int data;
  LinkTree left;
  LinkTree right;
};
typedef struct {
  LinkQueue init;
  LinkQueue end;
} Queue;

void initQueue(Queue *queue) {
  queue->init = NULL;
  queue->end = NULL;
}

void enqueue(Queue *queue, LinkTree data) {
  LinkQueue newNode = (LinkQueue)malloc(sizeof(struct NodeQueue));
  newNode->data = data;
  newNode->next = NULL;
  if (queue->init == NULL)
    queue->init = newNode;
  else
    queue->end->next = newNode;
  queue->end = newNode;
}

void dequeue(Queue *queue, LinkTree *copy) {
  if (queue->init == NULL)
    printf("Fila Vazia!");
  else {
    *copy = queue->init->data;
    LinkQueue aux = queue->init;
    queue->init = queue->init->next;
    if (queue->init == NULL)
      queue->end = NULL;
    free(aux);
  }
}

LinkTree insertTree(LinkTree raiz, int valor) {
  if (raiz == NULL) { // se a Ã¡rvore estiver vazia
    LinkTree novoNode =
        (LinkTree)malloc(sizeof(struct NodeTree)); // entÃ£o cria um novo nÃ³
    novoNode->data = valor;
    novoNode->left = NULL;
    novoNode->right = NULL;
    return novoNode;
  }
  if (valor < raiz->data) // se o valor for menor que a chave
    raiz->left = insertTree(raiz->left, valor); // insere na subÃ¡rvore esquerda
  else if (valor > raiz->data) // se o valor for maior que a chave
    raiz->right =
        insertTree(raiz->right, valor); // insere na subÃ¡rvore direita
  return raiz;                          // retorna a raiz atualizada
}

int main(void) {
  LinkTree tree = NULL;
  Queue queue;
  initQueue(&queue);

  tree = insertTree(tree, 50);
  tree = insertTree(tree, 40);
  tree = insertTree(tree, 60);
  tree = insertTree(tree, 35);
  tree = insertTree(tree, 45);
  tree = insertTree(tree, 55);
  tree = insertTree(tree, 65);

  enqueue(&queue, tree);

  LinkTree data;
  while (queue.init != NULL) {
    dequeue(&queue, &data);
    printf(" %d", (data)->data);
    if ((data)->left != NULL)
      enqueue(&queue, (data)->left);
    if ((data)->right)
      enqueue(&queue, (data)->right);
  }

  return 0;
}