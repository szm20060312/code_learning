#include <stdio.h>
#include <time.h>

void test1(int n) {
    long long sum = 0;
    for (int i=0; i<n; i++) sum++;
}

void test2(int n) {
    long long sum = 0;
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            sum++;
}

void test3(int n) {
    long long sum = 0;
    for (int i=0; i<n; i++)
        for (int j=0; j<n*n; j++)
            sum++;
}

void test4(int n) {
    long long sum = 0;
    for (int i=0; i<n; i++)
        for (int j=0; j<i; j++)
            sum++;
}

void test5(int n) {
    long long sum = 0;
    for (int i=0; i<n; i++)
        for (int j=0; j<i*i; j++)
            for (int k=0; k<j; k++)
                sum++;
}

void test6(int n) {
    long long sum = 0;
    for (int i=1; i<n; i++)
        for (int j=1; j<i*i; j++)
            if (j % 1 == 0)
                for (int k=0; k<j; k++)
                    sum++;
}

void run(void (*f)(int), int n, int id) {
    clock_t start = clock();
    f(n);
    clock_t end = clock();
    double t = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Test %d, n=%d, time=%.6f s\n", id, n, t);
}

int main() {
    int ns[] = {100, 200, 300}; // 可以根据实际情况修改
    int size = sizeof(ns)/sizeof(ns[0]);

    for (int i=0; i<size; i++) {
        int n = ns[i];
        run(test1, n, 1);
        run(test2, n, 2);
        run(test3, n, 3);
        run(test4, n, 4);
        run(test5, n, 5);
        run(test6, n, 6);
        printf("------------\n");
    }
    return 0;
}