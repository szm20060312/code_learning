#include <stdio.h>

int main() {
    double firstArray[8];
    double secondArray[8];
    double cumulativeSum = 0.0;

    printf("Enter 8 values for the first array:\n");
    for (int i = 0; i < 8; i++) {
        printf("Element %d: ", i + 1);
        scanf("%lf", &firstArray[i]);
    }

    for (int i = 0; i < 8; i++) {
        cumulativeSum += firstArray[i];
        secondArray[i] = cumulativeSum; 
    }

    printf("\nFirst Array:\n");
    for (int i = 0; i < 8; i++) {
        printf("%.2lf ", firstArray[i]);
    }
    
    printf("\n\nSecond Array (Cumulative Totals):\n");
    for (int i = 0; i < 8; i++) {
        printf("%.2lf ", secondArray[i]);
    }

    printf("\n");
    return 0;
}
