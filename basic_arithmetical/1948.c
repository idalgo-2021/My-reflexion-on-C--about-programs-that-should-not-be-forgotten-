// Находит наибольший простой делитель заданного целого числа a и печатает его на экран.
// Необходимо выделить отдельную функцию для подсчёта этого значения. Использовать
// деление и операцию взятия остатка от деления нельзя. Однако, при необходимости
// деление можно реализовать при помощи вычитания. В случае ошибки вывести «n/a»
//
// Входные данные	Выходные данные
// 3                1 4 9
// 1 2 3

#include <stdio.h>

int isDivisible(int a, int b);
int MyFunc(int num);

int isDivisible(int a, int b) {
    while (a >= b) {
        a = a - b;
    }
    return a == 0;
}

int MyFunc(int num) {
    if (num == 0 || num == 1 || num == -1) {
        return -1;
    }

    if (num == 2 || num == -2) {
        return 1;
    }

    if (num < 0) {
        num = -num;
    }

    for (int i = num; i > 0; i--) {
        if (isDivisible(num, i)) {
            int tmp = 1;
            for (int j = i - 1; j > 1; j--) {
                if (isDivisible(i, j)) {
                    tmp = 0;
                    break;
                }
            }

            if (tmp) {
                return i;
            }
        }
    }

    return -1;
}

int main() {
    int a;
    scanf("%d", &a);

    int nod = MyFunc(a);
    if (nod == -1) {
        printf("n/a");
    } else {
        printf("%d", nod);
    }

    return 0;
}