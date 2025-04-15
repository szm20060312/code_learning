#include <stdio.h>

// Function to compute the cube of a double
double cube(double num) {
    return num * num * num;
}

int main() {
    double number;

    // Request user input
    printf("Enter a double number: ");
    scanf("%lf", &number);

    // Call the cube function and print the result
    double cubedValue = cube(number);
    printf("The cube of %.2lf is %.2lf\n", number, cubedValue);

    return 0;
}
