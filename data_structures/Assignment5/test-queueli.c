#include <stdio.h>
#include "queueli.h"

int main() {
    Queue q;
    initQueue(&q);

    int values[] = {0, 3, 99, 100, 106, 58, 9, 365};
    int n = sizeof(values) / sizeof(values[0]);

    printf("Enqueuing elements:\n");
    for (int i = 0; i < n; i++) {
        enqueue(&q, values[i]);
    }

    printQueue(&q);

    printf("\nDequeuing three elements...\n");
    for (int i = 0; i < 3; i++) {
        int val = dequeue(&q);
        printf("Dequeued: %d\n", val);
    }

    printf("\nQueue after dequeuing:\n");
    printQueue(&q);

    freeQueue(&q);
    return 0;
}
