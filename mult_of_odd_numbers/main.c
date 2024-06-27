// Вывести произведение нечетных цифр числа
/////////////////////////////////

#include <stdio.h>

int main() {
    int mult = 0;

    int num;
    if (scanf("%d", &num) != 1) {
        printf("n/a");
        return 1;
    }

    if (num < 9) {
        if (num % 2 == 0) {
            printf("n/a");
        } else {
            printf("%d", num);
        }

        return 0;
    }

    int ost = 0;
    while (num > 0) {
        ost = num % 10;
        if (ost == 0) {
            num = num / 10;
        } else {
            if (ost % 2 != 0) {
                if (mult == 0) {
                    mult = 1;
                }
                mult = mult * ost;
            }
            num = num / 10;
        }
    }

    if (mult == 0) {
        printf("n/a");
    } else {
        printf("Произведение нечетных  =  %d\n", mult);
    }

    return 0;
}