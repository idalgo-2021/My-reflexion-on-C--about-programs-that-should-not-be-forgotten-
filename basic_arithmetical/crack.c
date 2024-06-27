// На вход принимает два числа с плавающей точкой, а на выходе
// выдает «GOTCHA», если координаты точки находятся внутри окружности,
// и «MISS» иначе. Предусмотреть ввод только чисел — в случае
// ошибки вывести n/a

#include <stdio.h>

int main() {
    float x;
    float y;
    if (scanf("%f %f", &x, &y) != 2) {
        printf("You need input two float argument\n");
        printf("n/a\n");
        return 0;
    }

    if ((x * x + y * y) < 25) {
        printf("GOTCHA\n");
    } else {
        printf("MISS\n");
    }

    return 0;
}