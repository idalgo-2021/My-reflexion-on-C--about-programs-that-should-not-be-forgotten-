
#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>

#define X 80
#define Y 25
#define DELAY 100000  // 100000 - 1 мк.сек(0.1 сек.)
#define SPEED_CHANGE 10000

void fill_rand(int map[][X]);
void show(int map[][X]);
void step(int map[][X], int prev[][X]);
void copy(int src[][X], int dest[][X]);
int get_y(int i);
int get_x(int j);
void handle_input(int *delay, int *exit_flag, int *paused);
void fill_from_file(int map[][X], int *fill_error, const char *filename);

int main(int argc, char *argv[]) {
    int map[Y][X];          // основной массив(игровое поле)
    int map_support[Y][X];  // вспомогательный массив
    int delay = DELAY;      // задержка
    int paused = 0;
    int fill_error = 0;

    if (argc > 1) {
        fill_from_file(map, &fill_error, argv[1]);
    } else {
        fill_rand(map);
    }
    if (fill_error) {
        return 1;
    }

    initscr();
    cbreak();  // режим прерывания
    noecho();
    nodelay(stdscr, TRUE);  // для неблокирующего чтения клавиш
    int exit_flag = 0;
    while (exit_flag == 0) {
        if (!paused) {
            show(map);
            step(map, map_support);
        }
        usleep(delay);
        handle_input(&delay, &exit_flag, &paused);
        if (!paused) {
            clear();
        }
    }
    endwin();
    return 0;
}

// Создание игрового поля(случайное заполнение)
void fill_rand(int map[][X]) {
    srand(time(NULL));
    for (int i = 0; i < Y; ++i) {
        for (int j = 0; j < X; ++j) {
            if (rand() % 10 == 0) {  // 10%

                // if (rand() % 10 < 7) {  // 70%
                map[i][j] = 1;
            } else {
                map[i][j] = 0;
            }
        }
    }
}

// Печать игрового поля
void show(int map[][X]) {
    for (int i = 0; i < Y; ++i) {
        for (int j = 0; j < X; ++j) {
            if (map[i][j] != 0) {
                mvprintw(i, j, "o");
            } else {
                mvprintw(i, j, " ");
            }
        }
    }
    refresh();
}

// Формирование следующего шага игры
void step(int map[][X], int prev[][X]) {
    copy(map, prev);

    for (int i = 0; i < Y; ++i) {
        for (int j = 0; j < X; ++j) {
            int count_neib = 0;
            count_neib += prev[get_y(i - 1)][get_x(j - 1)];
            count_neib += prev[get_y(i - 1)][get_x(j)];
            count_neib += prev[get_y(i - 1)][get_x(j + 1)];

            count_neib += prev[get_y(i)][get_x(j - 1)];
            count_neib += prev[get_y(i)][get_x(j + 1)];

            count_neib += prev[get_y(i + 1)][get_x(j - 1)];
            count_neib += prev[get_y(i + 1)][get_x(j)];
            count_neib += prev[get_y(i + 1)][get_x(j + 1)];

            if (prev[i][j] == 0 && count_neib == 3) {
                map[i][j] = 1;
            } else if (prev[i][j] == 1 && (count_neib == 2 || count_neib == 3)) {
                map[i][j] = 1;
            } else {
                map[i][j] = 0;
            }
        }
    }
}

// Копирование массива с игровым полем(вспомогательная функция)
void copy(int src[][X], int dest[][X]) {
    for (int i = 0; i < Y; ++i) {
        for (int j = 0; j < X; ++j) {
            dest[i][j] = src[i][j];
        }
    }
}

int get_y(int i) { return (Y + i) % Y; }

int get_x(int j) { return (X + j) % X; }

// Обработка нажатий клавиш клавиатуры
void handle_input(int *delay, int *exit_flag, int *paused) {
    int ch = getch();
    switch (ch) {
        case 'p':
        case 'P':
            *exit_flag = 1;
            break;
        case ' ':
            *paused = !(*paused);
            break;
        default:
            if (!(*paused)) {
                switch (ch) {
                    case 'a':
                    case 'A':
                        if (*delay > SPEED_CHANGE) {
                            *delay -= SPEED_CHANGE;
                        } else {
                            *delay = SPEED_CHANGE;
                        }
                        break;
                    case 'z':
                    case 'Z':
                        *delay += SPEED_CHANGE;
                        break;
                }
            }
    }
}

// Создание игрового поля(на основе файла, переданного в параметрах)
void fill_from_file(int map[][X], int *fill_error, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        *fill_error = 1;
        printf("Error opening file for reading.\n");
        return;
    }

    for (int i = 0; i < Y; ++i) {
        for (int j = 0; j < X; ++j) {
            if (fscanf(file, "%d", &map[i][j]) != 1) {
                *fill_error = 1;
                printf("Error reading file.\n");
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
}
