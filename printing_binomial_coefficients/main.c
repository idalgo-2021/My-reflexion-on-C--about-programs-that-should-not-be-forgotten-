/////////////////////////////////////////////////////////////
// Для заданного положительного целого n вывести через пробел все коэффициенты биномиального разложения
// C(k,n), где k={0,...,n} C(k, n) = n!/((n-k)!k!)
//
// Для вычисления факториала использовать рекурсивный алгоритм
/////////////////////////////////////////////////////////////

#include <stdio.h>

int fact(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }

    return n * fact(n - 1);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("n/a");
        return 1;
    }
    if (n < 1) {
        printf("n/a");
        return 1;
    }

    int fact_n = fact(n);
    int c;
    for (int k = 0; k <= n; k++) {
        c = fact_n / (fact(n - k) * fact(k));
        if (k == 0) {
            printf("%d", c);
        } else {
            printf(" %d", c);
        }
    }

    return 0;
}