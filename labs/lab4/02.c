#include <stdio.h>

int main() {
    int b, a;
    
    printf("This program computes moduli.\n");
    printf("Enter an integer to serve as the second operand: ");
    scanf("%d", &b);
    
    if (b <= 0) {
        printf("The second operand must be greater than zero.\n");
        return 1;
    }
    
    printf("Now enter the first operand: ");
    scanf("%d", &a);
    
    while (a > 0) {
        printf("%d %% %d is %d\n", a, b, a % b);
        
        printf("Enter next number for first operand (<= 0 to quit): ");
        scanf("%d", &a);
    }
  
    printf("Done\n");
    return 0;
}
