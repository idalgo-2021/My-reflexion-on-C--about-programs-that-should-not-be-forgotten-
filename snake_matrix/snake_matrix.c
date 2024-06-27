// Заполнение матрицы по спирали
//
//  1  2  3  4 5
// 16 17 18 19 6
// 15 24 25 20 7
// 14 23 22 21 8
// 13 12 11 10 9
/////////////////////////////////

#include <stdio.h>

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        printf("n/a");
        return 1;
    }

    int M[n][n];

    int s = 0;
    int k = 1;
    while (k <= (n * n)) {
        // Вправо
        for (int j = s; j < n - s; j++) {
            M[s][j] = k++;
        }
        // Вниз
        for (int i = s + 1; i < n - s; i++) {
            M[i][n - s - 1] = k++;
        }
        // Влево
        for (int j = n - s - 2; j >= s; j--) {
            M[n - s - 1][j] = k++;
        }
        // Вверх
        for (int i = n - s - 2; i > s; i--) {
            M[i][s] = k++;
        }

        s++;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", M[i][j]);
            if (j < n - 1) {
                printf(" ");
            }
        }
        if (i < n - 1) {
            printf("\n");
        }
    }

    return 0;
}