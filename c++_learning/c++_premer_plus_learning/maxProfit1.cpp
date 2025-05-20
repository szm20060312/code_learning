#include <stdio.h>
#include <limits.h>

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize == 0) return 0;

    //Define the state array
    int dp[pricesSize][5];
    // dp[i][0] represents the maximum profit when doing nothing on the i-th day.
    // dp[i][1] represents the first buy.
    // dp[i][2] represents the first sell.
    // dp[i][3] represents the second buy.
    // dp[i][4] represents the second sell.

    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    dp[0][2] = 0;
    dp[0][3] = -prices[0];
    dp[0][4] = 0;

    for (int i = 1; i < pricesSize; i++) {
        dp[i][0] = dp[i-1][0];
        dp[i][1] = (dp[i-1][1] > dp[i-1][0] - prices[i]) ? dp[i-1][1] : (dp[i-1][0] - prices[i]);
        dp[i][2] = (dp[i-1][2] > dp[i-1][1] + prices[i]) ? dp[i-1][2] : (dp[i-1][1] + prices[i]);
        dp[i][3] = (dp[i-1][3] > dp[i-1][2] - prices[i]) ? dp[i-1][3] : (dp[i-1][2] - prices[i]);
        dp[i][4] = (dp[i-1][4] > dp[i-1][3] + prices[i]) ? dp[i-1][4] : (dp[i-1][3] + prices[i]);
    }

    //The final result is the maximum profit after two transactions.
    return dp[pricesSize-1][4];
}

int main() {
    int prices[] = {3, 3, 5, 0, 0, 3, 1, 4};
    int pricesSize = sizeof(prices) / sizeof(prices[0]);
    int result = maxProfit(prices, pricesSize);
    printf("%d\n", result); // Output: 6

    return 0;
}
