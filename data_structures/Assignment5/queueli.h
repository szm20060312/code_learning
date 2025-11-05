#ifndef QUEUELI_H
#define QUEUELI_H

#include <stdbool.h>

// Queue node structure
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Queue structure
typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

void initQueue(Queue *q);
bool isEmpty(Queue *q);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
void printQueue(Queue *q);
void freeQueue(Queue *q);

#endif
