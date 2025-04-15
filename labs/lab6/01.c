#include <stdio.h>

void sort(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main() {
    int N;
    printf("Input number of elements: ");
    scanf("%d", &N);

    int array[N];
    printf("Enter %d numbers:\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }

    sort(array, N);

    printf("Sorted:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}