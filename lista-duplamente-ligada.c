#include <stdio.h>
#include <stdlib.h>

typedef struct Node *Link;
struct Node
{
    int data;
    Link next, previous;
};

void insert(Link *list, int data)
{
    Link newNode = (Link)malloc(sizeof(struct Node));
    newNode->data = data;

    (*list)->next->previous = newNode;
    newNode->next = (*list)->next;
    newNode->previous = *list;
    (*list)->next = newNode;
}

void constructorList(Link *list)
{
    (*list)->next = *list;
    (*list)->previous = *list;
}

void print(Link list)
{
    Link aux = list->next;
    do
    {
        printf("%d ", aux->data);
        aux = aux->next;
    } while (aux != list);
}

Link *find(Link *list, int data)
{
    Link *aux = &(*list)->next;
    do
    {
        if ((*aux)->data == data)
            return aux;
        aux = &(*aux)->next;
    } while (aux != list);
    return NULL;
}

void removeElement(Link *list, int data)
{
    Link elementToRemove = *find(list, data);
    elementToRemove->next->previous = elementToRemove->previous;
    elementToRemove->previous->next = elementToRemove->next;
    free(elementToRemove);
}

int main(void)
{
    Link list = (Link)malloc(sizeof(struct Node));
    constructorList(&list);
    insert(&list, 3);
    insert(&list, 2);
    insert(&list, 1);
    print(list);
    printf("\n\nnúmero %d encontrado!\n\n", (*find(&list, 2))->data);
    removeElement(&list, 2);
    print(list);
    return 0;
}