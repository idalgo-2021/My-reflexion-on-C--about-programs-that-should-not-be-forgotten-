// Программа принимает через stdin массив целых чисел, возводит их в квадрат и
// выводит в stdout. В случае некорректного ввода выводит n/a

#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == 1) {
        printf("n/a");
        return 1;
    } else {
        squaring(data, n);
        output(data, n);
    }
    return 0;
}

int input(int *a, int *n) {
    int err = 0;
    if (scanf("%d", n) != 1 || *n <= 0 || *n > NMAX)
        err = 1;
    else {
        for (int *p = a; p - a < *n; p++) {
            if (scanf("%d", p) != 1) {
                err = 1;
                break;
            }
        }

        if (err == 0) {
            char ch = getchar();
            if (ch != '\n' && ch != EOF) {
                err = 1;
            }
        }
    }
    return err;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        printf("%d", *p);

        if (p - a + 1 < n) {
            printf(" ");
        }
    }
}

void squaring(int *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] *= a[i];
    }
}
