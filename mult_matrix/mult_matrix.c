// Умножение квадратных матриц ([n][n])матриц
//
// вход:
//      n - число(размерность матрицы)
//      первая и вторая матрицы
//
// пример-1:
// 2
// 1 2
// 3 4
// 5 6
// 7 8
// 19 22
// 43 50
//
// пример-2:
// 3
// 1 2 3
// 4 5 6
// 7 8 9
// 10
// 11 12
// 13 14 15
// 16 17 18
// 84 90 96
// 201 216 231
// 318 342 366
/////////////////////////////////

#include <stdio.h>

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("n/a");
        return 1;
    }

    int M[n][n];
    int N[n][n];

    // input matrix M
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &M[i][j]) != 1) {
                printf("n/a");
                return 1;
            }
        }
    }

    // input matrix N
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &N[i][j]) != 1) {
                printf("n/a");
                return 1;
            }
        }
    }

    int C[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int c = 0;
            for (int k = 0; k < n; k++) {
                c = c + (M[i][k] * N[k][j]);
            }
            C[i][j] = c;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }

        printf("\n");
    }

    return 0;
}