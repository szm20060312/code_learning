#include <stdio.h>
#include "BinHeap.h"

int main() {
    BinHeap heap;
    InitHeap(&heap);

    int data[] = {53, 26, 97, 59, 41, 31, 58};
    int n = sizeof(data) / sizeof(data[0]);

    BuildHeap(&heap, data, n);
    printf("Heap after BuildHeap: ");
    PrintHeap(&heap);

    printf("Minimum element: %d\n", FindMin(&heap));

    int min = DeleteMin(&heap);
    printf("Deleted minimum: %d\n", min);

    printf("Heap after DeleteMin: ");
    PrintHeap(&heap);

    return 0;
}
