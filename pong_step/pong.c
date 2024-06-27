#include <stdio.h>
#include <stdlib.h>

#define X 80
#define Y 25
#define WINCOUNT 21

// Начальные координаты ракеток
#define r0_1 Y / 2;
#define r0_2 Y / 2;

// Начальные координаты мяча
#define ball_pos0_x X / 2;
#define ball_pos0_y Y / 2;

void make_borders(char map[][X]);
void print_fields(char map[][X], int score_player1, int score_player2);
void mv_raket1(char key, char map[][X], int *rc);
void mv_raket2(char key, char map[][X], int *rc);

void init_elements_position(int *r1, int *r2, int *ball_pos_x, int *ball_pos_y);
void init_game_map(char map[][X], int r1, int r2, int ball_pos_x, int ball_pos_y);

int main() {
    system("clear");

    // Направление полёта мяча
    int ball_dir_x = -1;
    int ball_dir_y = 1;

    int score_player1 = 0;
    int score_player2 = 0;

    char map[Y][X];

    make_borders(map);

    int ball_pos_x, ball_pos_y;  // Координаты мяча
    int r1, r2;                  // Координаты рекеток

    init_elements_position(&r1, &r2, &ball_pos_x, &ball_pos_y);
    init_game_map(map, r1, r2, ball_pos_x, ball_pos_y);
    print_fields(map, score_player1, score_player2);

    while (1) {
        char key = getchar();

        system("clear");

        // Движение мяча
        map[ball_pos_y][ball_pos_x] = ' ';
        if (ball_pos_y == 0 || ball_pos_y == Y - 1) {
            map[ball_pos_y][ball_pos_x] = '-';
            ball_dir_y = -ball_dir_y;
        }

        ball_pos_y = ball_pos_y + ball_dir_y;
        ball_pos_x = ball_pos_x + ball_dir_x;
        map[ball_pos_y][ball_pos_x] = '*';

        // Управление ракетками
        mv_raket1(key, map, &r1);
        mv_raket2(key, map, &r2);

        // Рикошет мяча от ракеток
        if ((ball_pos_x == 2 && (ball_pos_y == r1 - 1 || ball_pos_y == r1 || ball_pos_y == r1 + 1)) ||
            (ball_pos_x == X - 3 && (ball_pos_y == r2 - 1 || ball_pos_y == r2 || ball_pos_y == r2 + 1))) {
            ball_dir_x = -ball_dir_x;
        }

        // Гол-контроль
        if (ball_pos_x <= 0) {
            score_player2++;
            make_borders(map);
            init_elements_position(&r1, &r2, &ball_pos_x, &ball_pos_y);
            init_game_map(map, r1, r2, ball_pos_x, ball_pos_y);
            ball_dir_x = -ball_dir_x;  //
        }
        if (ball_pos_x >= X - 1) {
            score_player1++;
            make_borders(map);
            init_elements_position(&r1, &r2, &ball_pos_x, &ball_pos_y);
            init_game_map(map, r1, r2, ball_pos_x, ball_pos_y);
            ball_dir_y = -ball_dir_y;  //
        }

        print_fields(map, score_player1, score_player2);

        // Прерывание игры "по кнопке"
        if (key == 'p' || key == 'P') {
            printf("The game is interrupted\n");
            break;
        }

        // Контроль завешения по очкам и печать поздравления
        if (score_player1 >= WINCOUNT) {
            printf("Player1 is WIN! Congratulations!\n");
            break;
        } else if (score_player2 >= WINCOUNT) {
            printf("Player2 is WIN! Congratulations!\n");
            break;
        }
    }

    return 0;
}

// Формирование границ игрового поля
void make_borders(char map[][X]) {
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            if (i == 0 || i == Y - 1) {
                map[i][j] = '-';
            } else {
                if (j == 0 || j == X - 1) {
                    map[i][j] = '|';
                } else {
                    map[i][j] = ' ';
                }
            }
        }
    }
}

// Печать игрового поля и результатов
void print_fields(char map[][X], int score_player1, int score_player2) {
    // Вывод игрового поля
    for (int i = 0; i < Y; i++) {
        for (int j = 0; j < X; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }

    // Вывод результов игроков
    printf("Score player-1: %d\n", score_player1);
    printf("Score player-2: %d\n", score_player2);
}

// Управление левой ракеткой
void mv_raket1(char key, char map[][X], int *rc) {
    if ((key == 'a' || key == 'A') && *rc - 2 > 0) {
        map[*rc - 2][1] = ']';
        map[*rc - 1][1] = ']';
        map[*rc][1] = ']';
        map[*rc + 1][1] = ' ';
        (*rc)--;
    }

    if ((key == 'z' || key == 'Z') && *rc + 2 < Y - 1) {
        map[*rc + 2][1] = ']';
        map[*rc + 1][1] = ']';
        map[*rc][1] = ']';
        map[*rc - 1][1] = ' ';
        (*rc)++;
    }
}

// Управление правой ракеткой
void mv_raket2(char key, char map[][X], int *rc) {
    if ((key == 'k' || key == 'K') && *rc - 2 > 0) {
        map[*rc - 2][X - 2] = '[';
        map[*rc - 1][X - 2] = '[';
        map[*rc][X - 2] = '[';
        map[*rc + 1][X - 2] = ' ';
        (*rc)--;
    }

    if ((key == 'm' || key == 'M') && *rc + 2 < Y - 1) {
        map[*rc + 2][X - 2] = '[';
        map[*rc + 1][X - 2] = '[';
        map[*rc][X - 2] = '[';
        map[*rc - 1][X - 2] = ' ';
        (*rc)++;
    }
}

// Инициализация координат ракеток и мяча(через глобальные переменные)
void init_elements_position(int *r1, int *r2, int *ball_pos_x, int *ball_pos_y) {
    *ball_pos_x = ball_pos0_x;
    *ball_pos_y = ball_pos0_y;

    *r1 = r0_1;
    *r2 = r0_2;
}

// Задание положения ракеток и мяча на игровом поле
void init_game_map(char map[][X], int r1, int r2, int ball_pos_x, int ball_pos_y) {
    // Левая ракетка
    map[r1 - 1][1] = ']';
    map[r1][1] = ']';
    map[r1 + 1][1] = ']';

    // Правая ракетка
    map[r2 - 1][X - 2] = '[';
    map[r2][X - 2] = '[';
    map[r2 + 1][X - 2] = '[';

    // Положения мяча
    map[ball_pos_y][ball_pos_x] = '*';
}
