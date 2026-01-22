#ifndef BINHEAP_H
#define BINHEAP_H

#define MAXSIZE 100

typedef struct {
    int data[MAXSIZE];
    int size;
} BinHeap;

void InitHeap(BinHeap *h);
void BuildHeap(BinHeap *h, int arr[], int n);
void Insert(BinHeap *h, int value);
int FindMin(BinHeap *h);
int DeleteMin(BinHeap *h);

void PrintHeap(BinHeap *h);

#endif
