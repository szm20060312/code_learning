#include <stdio.h>

// 计算第 n 个斐波那契数
int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b; // 返回第 n 个斐波那契数
}

double sum(int n) {
    int a[101],b[101];
    double c[101];
    for(int i=1;i<=n;i++){
        a[i] = fibonacci(i+2);
    }
    for(int i=1;i<=n;i++){
        b[i] = fibonacci(i+1);
    }
    double ans = 0;
    for(int i=1;i<=n;i++){
        c[i] = (double)a[i]/b[i];
        //printf("%.5f ",c[i]);
        ans += c[i];
    }
    return ans;
}

int main() {
    int n;
    printf("Please enter the nth number: ");
    scanf("%d", &n);
    double ans = sum(n);
    printf("The sum of the first %d terms of the fractional sequence is: %.5f\n",n,ans);
    return 0;
}
