// На вход через stdin принимает два целых числа и выводит на экран через пробел
// последовательно их сумму, разность, произведение и частное. Необходимо
// предусмотреть проверку на ввод только целых чисел. Ответ не должен
// заканчиваться пробелом. Предусмотреть обработку деления на ноль. В случае
// любой ошибки вывести n/a.

#include <stdio.h>

int sum(int a, int b);
int sub(int a, int b);
int mult(int a, int b);
int divide(int a, int b);

int main() {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2) {
        printf("You need input two integer arguments\n");
        printf("n/a");
        return 0;
    }

    if (b != 0) {
        printf("%d %d %d %d\n", sum(a, b), sub(a, b), mult(a, b), divide(a, b));
    } else {
        printf("%d %d %d %s\n", sum(a, b), sub(a, b), mult(a, b), "n/a");
    }

    return 0;
}

int sum(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mult(int a, int b) { return a * b; }
int divide(int a, int b) {
    if (b != 0) {
        return a / b;
    }
    return a / b;  // "n/a"
}