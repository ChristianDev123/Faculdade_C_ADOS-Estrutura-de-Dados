#include "grafo.h"
#ifndef FILA_H
#define FILA_H
typedef struct Node *Link;

struct Node {
  linkGrafo data;
  Link next;
};
typedef struct {
  Link init;
  Link end;
  int count;
} Queue;

void constructor(Queue *queue);
void enqueue(Queue *queue, linkGrafo data);
void dequeue(Queue *queue, linkGrafo *copyData);

#endif