#include <stdio.h>
#include "BinHeap.h"

void InitHeap(BinHeap *h) {
    h->size = 0;
}

static void HeapifyDown(BinHeap *h, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < h->size && h->data[left] < h->data[smallest])
        smallest = left;
    if (right < h->size && h->data[right] < h->data[smallest])
        smallest = right;

    if (smallest != i) {
        int temp = h->data[i];
        h->data[i] = h->data[smallest];
        h->data[smallest] = temp;
        HeapifyDown(h, smallest);
    }
}

static void HeapifyUp(BinHeap *h, int i) {
    int parent = (i - 1) / 2;
    while (i > 0 && h->data[i] < h->data[parent]) {
        int temp = h->data[i];
        h->data[i] = h->data[parent];
        h->data[parent] = temp;
        i = parent;
        parent = (i - 1) / 2;
    }
}

void BuildHeap(BinHeap *h, int arr[], int n) {
    h->size = n;
    for (int i = 0; i < n; i++)
        h->data[i] = arr[i];

    for (int i = n / 2 - 1; i >= 0; i--)
        HeapifyDown(h, i);
}

void Insert(BinHeap *h, int value) {
    if (h->size >= MAXSIZE) return;
    h->data[h->size++] = value;
    HeapifyUp(h, h->size - 1);
}

int FindMin(BinHeap *h) {
    if (h->size == 0) return -1;
    return h->data[0];
}

int DeleteMin(BinHeap *h) {
    if (h->size == 0) return -1;

    int min = h->data[0];
    h->data[0] = h->data[--h->size];
    HeapifyDown(h, 0);

    return min;
}

void PrintHeap(BinHeap *h) {
    for (int i = 0; i < h->size; i++)
        printf("%d ", h->data[i]);
    printf("\n");
}
