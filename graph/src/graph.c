#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "rpn.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIDTH 80
#define HEIGHT 25

void plotGraph(const char *expression);

int main() {
    char expression[MAX_EXPR_LEN];

    printf("Enter the expression to plot: ");
    if (fgets(expression, sizeof(expression), stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }
    expression[strcspn(expression, "\n")] = 0;

    plotGraph(expression);

    return 0;
}

void plotGraph(const char *expression) {
    system("clear");
    printf("Expression: %s\n", expression);

    Token tokens[MAX_EXPR_LEN];
    tokenize(expression, tokens);
    if (!isCorrectTokens(tokens)) {
        printf("The expression is not correct\n");
        return;
    }

    Token rpn_tokens[MAX_EXPR_LEN];
    shuntingYard(tokens, rpn_tokens);
    printf("RPN Expression: %s\n", get_rpn_string(rpn_tokens));

    // Заполнение поля
    char map[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            map[i][j] = '.';
        }
    }

    // Вычисление результа для каждой точки(и фиксация на графике)
    for (int j = 0; j < WIDTH; j++) {
        double x = 4.0 * M_PI * j / (WIDTH - 1);
        double y = evaluateRPN(rpn_tokens, x);

        int i = HEIGHT / 2 + (int)(y * (HEIGHT / 2));

        if (i >= 0 && i < HEIGHT) {
            map[i][j] = '*';
        }
    }

    // Вывод результата
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}
