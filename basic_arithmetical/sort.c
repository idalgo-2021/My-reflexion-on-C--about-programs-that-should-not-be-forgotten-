// Программа ожидает на вход в stdin массив длиной 10 из целых чисел и
// выводит этот же массив, но уже отсортированный по возрастанию.
// Необходимо выделить функции чтения, сортировки и вывода массива отдельно.
// Алгоритм сортировки можно использовать любой.
// Использовать stdlib.h нельзя. Передача массива в функцию только по указателю.
// В случае ошибки выводить "n/a"

#include <stdio.h>

#define SIZE 10

int readArray(int *array);
void sortArray(int *array);
void printArray(int *array);

int main() {
    int array[SIZE];
    if (readArray(array) != 0) {
        printf("n/a");
    } else {
        sortArray(array);
        printArray(array);
    }
    return 0;
}

int readArray(int *a) {
    for (int *p = a; p - a < SIZE; p++) {
        if (scanf("%d", p) != 1) {
            return -1;
        }
    }

    if (getchar() != '\n') {
        return -1;
    }
    return 0;
}

void sortArray(int *array) {
    int i, j, temp;
    for (i = 0; i < SIZE - 1; i++) {
        for (j = 0; j < SIZE - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void printArray(int *array) {
    int i;
    for (i = 0; i < SIZE; i++) {
        printf("%d ", array[i]);
    }
}
