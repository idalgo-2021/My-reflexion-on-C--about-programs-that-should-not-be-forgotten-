////////////////////////////////////////////////////////////////////////
// На вход принимает одно число x с плавающей точкой и выводит на
// экран результат подсчета функции (округленный до одной цифры после
// запятой). Необходимо предусмотреть проверку на ввод только чисел.
// В случае ошибки вывести n/a.
//
//
//  gcc -Wall -Werror -Wextra important_function.c -o important_function -lm
//
////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <stdio.h>

double get_result(double x);

int main() {
    double a;
    double y;
    if (scanf("%lf", &a) != 1) {
        printf("You need input one integer argument\n");
        printf("n/a\n");
        return 0;
    }

    y = get_result(a);
    printf("%.1lf\n", y);

    return 0;
}

double get_result(double x) {
    return 7e-3 * pow(x, 4) + ((22.8 * pow(x, (1 / 3)) - 1e3) * x + 3) / (x * x / 2) -
           x * pow((10 + x), (2 / x)) - 1.01;
}
