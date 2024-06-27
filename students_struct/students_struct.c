// Вывести через запятую имена студентов с максимальной оценкой
//
// Вход:
//  n - число студентов (после ввода n - ввод информации по студентам)
//  имя студента
//  оценка студента
//
//
//
/////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

typedef struct student {
    char name[20];
    int val;
} student;

int main() {
    // максимальный балл
    int max = 0;

    // ввод количества студентов
    int n;
    if (scanf("%d", &n) != 1) {
        printf("n/a");
        return 1;
    }
    if (n <= 0) {
        printf("n/a");
        return 1;
    }

    student *studs = malloc(n * sizeof(student));
    if (studs == NULL) {
        printf("n/a");
        return 1;
    }

    // ввод данных студентов
    int res = 1;
    for (int i = 0; i < n; i++) {
        if (scanf("%s", &*studs[i].name) != 1 || scanf("%d", &studs[i].val) != 1) {
            res = 0;
            break;
        }
    }

    if (res != 1) {
        printf("n/a");
    } else {
        // определяем максимальный балл
        max = studs[0].val;
        for (int i = 0; i < n; i++) {
            if (max < studs[i].val) {
                max = studs[i].val;
            }
        }

        // выводим имена студентов с максимальным баллом
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            if (max == studs[i].val) {
                if (cnt == 0) {
                    printf("%s", studs[i].name);
                } else {
                    printf(", %s", studs[i].name);
                }
                cnt++;
            }
        }
    }

    free(studs);

    return 0;
}