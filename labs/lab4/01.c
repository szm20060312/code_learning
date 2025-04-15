#include <stdio.h>

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    for(int i = num; i <= num+10; i++){
        printf("%d\n", i);
    }

    return 0;
}