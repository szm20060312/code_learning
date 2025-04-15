#include <stdio.h>

int main() {
    int n;
    printf("请输入一个整数 n: ");
    scanf("%d", &n);
    // 输出上半部分
    for (int i = 1; i <= n; i++) {
        for (int j = n; j > i; j--) {
            printf(" ");
        }
        for (int k = 1; k <= (2 * i - 1); k+=2) {
            printf("* ");
        }
        printf("\n");
    }

    // 下半部分
    for (int i = n - 1; i >= 1; i--) {
        for (int j = n; j > i; j--) {
            printf(" ");
        }
        for (int k = 1; k <= (2 * i - 1); k+=2) {
            printf("* ");
        }
        printf("\n");
    }
    return 0;
}
