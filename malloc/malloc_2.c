#include <stdio.h>
#include <stdlib.h>

int main() {
    int N = 5;
    int M = 10;

    // Выделение памяти для массива указателей на строки
    int **arr = (int **)malloc(N * sizeof(int *));
    if (arr == NULL) {
        printf("Ошибка выделения памяти\n");
        return 1;
    }

    // Выделение памяти для каждого ряда
    for (int i = 0; i < N; i++) {
        arr[i] = (int *)malloc(M * sizeof(int));

        // Проверка на успешное выделение памяти
        if (arr[i] == NULL) {
            printf("Ошибка выделения памяти для строки %d\n", i);
            // Освобождение ранее выделенной памяти
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            return 1;
        }
    }

    // Использование двумерного массива
    // Например, заполним массив числами и напечатаем его
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            arr[i][j] = i * M + j;
            // arr[i][j] = i + j;
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    // Освобождение памяти
    for (int i = 0; i < N; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
