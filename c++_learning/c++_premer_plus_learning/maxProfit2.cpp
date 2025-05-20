#include <stdio.h>

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize <= 1) {
        return 0;
    }

    int buy1 = -prices[0];
    int sell1 = 0;
    int buy2 = -prices[0];
    int sell2 = 0;

    for (int i = 1; i < pricesSize; i++) {
        buy1 = (buy1 > -prices[i]) ? buy1 : -prices[i];
        sell1 = (sell1 > prices[i] + buy1) ? sell1 : prices[i] + buy1;
        buy2 = (buy2 > sell1 - prices[i]) ? buy2 : sell1 - prices[i];
        sell2 = (sell2 > prices[i] + buy2) ? sell2 : prices[i] + buy2;
    }

    return sell2;
}

int main() {
    int prices1[] = {3, 3, 5, 0, 0, 3, 1, 4};
    int n1 = sizeof(prices1) / sizeof(prices1[0]);
    printf("maximum profit: %d\n", maxProfit(prices1, n1)); //outputs: 6

    int prices2[] = {1, 2, 3, 4, 5};
    int n2 = sizeof(prices2) / sizeof(prices2[0]);
    printf("maximum profit: %d\n", maxProfit(prices2, n2)); //outputs: 4

    int prices3[] = {7, 6, 4, 3, 1};
    int n3 = sizeof(prices3) / sizeof(prices3[0]);
    printf("maximum profit: %d\n", maxProfit(prices3, n3)); //outputs: 0

    int prices4[] = {1};
    int n4 = sizeof(prices4) / sizeof(prices4[0]);
    printf("maximum profit: %d\n", maxProfit(prices4, n4)); //outputs: 0

    return 0;
}
