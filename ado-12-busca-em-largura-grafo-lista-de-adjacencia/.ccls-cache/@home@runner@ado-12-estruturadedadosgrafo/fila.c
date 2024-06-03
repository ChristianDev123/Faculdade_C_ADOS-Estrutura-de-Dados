#include "fila.h"
#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

void constructor(Queue *queue) {
  queue->init = NULL;
  queue->end = NULL;
  queue->count = 0;
}

void enqueue(Queue *queue, linkGrafo data) {
  Link newNode = (Link)malloc(sizeof(struct Node));
  newNode->data = data;
  newNode->next = NULL;
  if (queue->init == NULL)
    queue->init = newNode;
  else
    queue->end->next = newNode;
  queue->end = newNode;
  queue->count++;
}

void dequeue(Queue *queue, linkGrafo *copyData) {
  if (queue->init != NULL) {
    *copyData = queue->init->data;
    Link aux = queue->init;
    queue->init = queue->init->next;
    if (queue->init == NULL)
      queue->end = NULL;
    free(aux);
    queue->count--;
  }
}