#include <stdio.h>

int main() {
    int lower, upper;

    while (1) {
        printf("Enter lower and upper integer limits: ");
        scanf("%d %d", &lower, &upper);

        if (upper <= lower) {
            printf("Done\n");
            break;
        }

        int sum = 0;
        for (int i = lower; i <= upper; i++) {
            sum += i * i;
        }

        printf("The sums of the squares from %d to %d is %d\n", lower * lower, upper * upper, sum);
    }

    return 0;
}
