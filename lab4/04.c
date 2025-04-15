#include <stdio.h>

int main() {
    char endChar;
    printf("Enter an uppercase letter: ");
    scanf("%c", &endChar);

    int rows = endChar - 'A' + 1;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            printf(" ");
        }
        for (char ch = 'A'; ch <= 'A' + i; ch++) {
            printf("%c", ch);
        }
        for (char ch = 'A' + i - 1; ch >= 'A'; ch--) {
            printf("%c", ch);
        }
        printf("\n");
    }

    return 0;
}
