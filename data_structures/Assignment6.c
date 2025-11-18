#include <stdio.h>

int sum(int n) {
    if (n == 1) {
        return 1;
    }
    return n + sum(n - 1);
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("n must be a positive integer.\n");
        return 0;
    }

    printf("Sum = %d\n", sum(n));
    return 0;
}
