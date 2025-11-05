#include <stdio.h>
#include <stdlib.h>
#include "queueli.h"
void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

bool isEmpty(Queue *q) {
    return q->front == NULL;
}

void enqueue(Queue *q, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty, cannot dequeue.\n");
        exit(1);
    }

    Node *temp = q->front;
    int value = temp->data;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return value;
}

void printQueue(Queue *q) {
    Node *current = q->front;
    printf("Queue: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeQueue(Queue *q) {
    Node *current = q->front;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    q->front = q->rear = NULL;
}
