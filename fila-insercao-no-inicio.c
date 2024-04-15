#include <stdio.h>

const int MAX = 42;
typedef struct {
  int A[MAX];
  int init;
  int qttElements;
} Queue;

void constructor(Queue *queue) {
  queue->init = -1;
  queue->qttElements = 0;
}

void enqueue(Queue *queue, int data) {
  int position;
  if (queue->qttElements == MAX) {
    printf("Fila Cheia\n");
    return;
  }
  if (queue->init == -1)
    position = ++(queue->init);
  else
    position = (queue->init + queue->qttElements) % MAX;
  queue->A[position] = data;
  queue->qttElements++;
}

void dequeue(Queue *queue, int *copy) {
  if (queue->qttElements == 0) {
    printf("Fila Vazia!\n");
    return;
  }
  *copy = queue->A[queue->init];
  queue->init = (queue->init + 1) % MAX;
  queue->qttElements--;
}

void print(Queue queue) {
  int i = queue.init;
  int j;
  for (j = 0; j < queue.qttElements; j++) {
    printf("%d ", queue.A[j]);
    i = (i + 1) % MAX;
  }
  printf("\n\n");
}

void jumpQueue(Queue *queue, int data){
  int position;
  if (queue->init == -1)
    position = ++(queue->init);
  else
    position = (queue->init + queue->qttElements) % MAX;
  queue->A[position] = data;
  queue->init = position;
  queue->qttElements++;
}

int main(void) {
  Queue queue;
  constructor(&queue);
  enqueue(&queue,2);
  enqueue(&queue,3);
  enqueue(&queue,5);
  jumpQueue(&queue,7);
  int data;
  dequeue(&queue,&data);
  print(queue);
  return 0;
}