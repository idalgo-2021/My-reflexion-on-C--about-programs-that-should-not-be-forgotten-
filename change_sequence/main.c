// Программа должна принять на вход последовательность целых чисел A1 A2 A3 ... An и
// вывести их следующем порядке: A1 An A2 A(n-1) ... .
// Входящая последовательность завершается -1(-1 не входит в последовательность)
/////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5000000

int main() {
    // int arr[MAX_SIZE];
    int *arr = (int *)malloc(MAX_SIZE * sizeof(int));
    if (NULL == arr) {
        printf("n/a");
        return 1;
    }

    int cnt = 0;

    for (int i = 0; i < MAX_SIZE; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("n/a");
            return 1;
        }

        if (arr[i] == -1) {
            break;
        }

        cnt = cnt + 1;
    }

    int j = cnt;
    for (int i = 0; i < cnt; i++) {
        j = j - 1;

        if (i < j) {
            if (i == 0) {
                printf("%d", arr[i]);
            } else {
                printf(" %d", arr[i]);
            }

            printf(" %d", arr[j]);
        }

        if (i == j) {
            printf(" %d", arr[i]);
            break;
        }

        if (i > j) {
            break;
        }
    }

    free(arr);

    return 0;
}
