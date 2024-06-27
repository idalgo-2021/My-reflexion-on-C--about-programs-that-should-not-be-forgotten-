#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_digit(char c) { return (c >= '0' && c <= '9'); }

int is_alpha(char c) { return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')); }

int isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }

int isFunction(const char *str) {
    return strcmp(str, "sin") == 0 || strcmp(str, "cos") == 0 || strcmp(str, "tan") == 0 ||
           strcmp(str, "ctg") == 0 || strcmp(str, "sqrt") == 0 || strcmp(str, "ln") == 0;
}

int isUnaryOperator(char c, const char *prevToken) {
    return c == '-' && (strlen(prevToken) == 0 || isOperator(prevToken[0]) || prevToken[0] == '(');
}

// Проверка корректности токенов
int isCorrectTokens(Token *tokens) {
    int result = 1;
    int open_parens = 0;  // Счетчик открывающих скобок
    int exist_var = 0;

    for (int i = 0; strcmp(tokens[i].type, "END") != 0; ++i) {
        if (strcmp(tokens[i].type, "VARIABLE") == 0 && strcmp(tokens[i].value, "x") != 0) {
            result = 0;
            break;
        }

        if (strcmp(tokens[i].type, "LEFT_PAREN") == 0) {
            open_parens++;
        } else if (strcmp(tokens[i].type, "RIGHT_PAREN") == 0) {
            open_parens--;
            if (open_parens < 0) {
                result = 0;
                break;
            }
        }

        if (exist_var == 0 && strcmp(tokens[i].type, "VARIABLE") == 0) {
            exist_var = 1;
        }
    }

    if (open_parens != 0) {
        result = 0;
    }

    if (exist_var != 1) {
        result = 0;
    }

    return result;
}

// Получение rpn-строки
char *get_rpn_string(Token *rpn_tokens) {
    static char rpn_string[MAX_EXPR_LEN * 5];  // пусть по 5 символов на токен
    strcpy(rpn_string, "");

    for (int i = 0; strcmp(rpn_tokens[i].type, "END") != 0; ++i) {
        strcat(rpn_string, rpn_tokens[i].value);
        strcat(rpn_string, " ");
    }

    return rpn_string;
}

// Токенизация входящего выражения
void tokenize(const char *expr, Token *tokens) {
    int i = 0;
    int j = 0;
    char prevToken[MAX_EXPR_LEN] = "";

    while (expr[i] != '\0') {
        if (is_digit(expr[i]) || expr[i] == '.') {
            // Числа
            int start = i;
            while (is_digit(expr[i]) || expr[i] == '.') i++;
            strncpy(tokens[j].value, &expr[start], i - start);
            tokens[j].value[i - start] = '\0';
            strcpy(tokens[j].type, "NUMBER");
            j++;
        } else if (is_alpha(expr[i])) {
            // Функции и переменные
            int start = i;
            while (is_alpha(expr[i])) i++;
            strncpy(tokens[j].value, &expr[start], i - start);
            tokens[j].value[i - start] = '\0';
            if (isFunction(tokens[j].value)) {
                strcpy(tokens[j].type, "FUNCTION");
            } else {
                strcpy(tokens[j].type, "VARIABLE");
            }
            j++;

        } else if (isUnaryOperator(expr[i], prevToken)) {
            tokens[j].value[0] = '~';  // Используем '~' для унарного минуса
            tokens[j].value[1] = '\0';
            strcpy(tokens[j].type, "UNARY_MINUS");
            i++;
            j++;
        } else if (isOperator(expr[i]) || expr[i] == '(' || expr[i] == ')') {
            tokens[j].value[0] = expr[i];
            tokens[j].value[1] = '\0';
            if (isOperator(expr[i])) {
                strcpy(tokens[j].type, "OPERATOR");
            } else if (expr[i] == '(') {
                strcpy(tokens[j].type, "LEFT_PAREN");
            } else if (expr[i] == ')') {
                strcpy(tokens[j].type, "RIGHT_PAREN");
            }
            i++;
            j++;

        } else {
            // Игнорируем прочие символы (пробелы и т.п.)
            i++;
        }

        if (j > 0) {
            strncpy(prevToken, tokens[j - 1].value, MAX_EXPR_LEN);
        }
    }

    strcpy(tokens[j].type, "END");
}

// Получение RPN исходного выражения(Shunting Yard algorithm)
void shuntingYard(Token *tokens, Token *output) {
    Token stack[MAX_EXPR_LEN];
    int top = -1;
    int j = 0;

    for (int i = 0; strcmp(tokens[i].type, "END") != 0; ++i) {
        if (strcmp(tokens[i].type, "NUMBER") == 0 || strcmp(tokens[i].type, "VARIABLE") == 0) {
            output[j++] = tokens[i];
        } else if (strcmp(tokens[i].type, "FUNCTION") == 0) {
            stack[++top] = tokens[i];
        } else if (strcmp(tokens[i].type, "OPERATOR") == 0 || strcmp(tokens[i].type, "UNARY_MINUS") == 0) {
            while (top >= 0 && (strcmp(stack[top].type, "OPERATOR") == 0 ||
                                strcmp(stack[top].type, "UNARY_MINUS") == 0)) {
                output[j++] = stack[top--];
            }
            stack[++top] = tokens[i];
        } else if (strcmp(tokens[i].type, "LEFT_PAREN") == 0) {
            stack[++top] = tokens[i];
        } else if (strcmp(tokens[i].type, "RIGHT_PAREN") == 0) {
            while (top >= 0 && strcmp(stack[top].type, "LEFT_PAREN") != 0) {
                output[j++] = stack[top--];
            }
            top--;  // Pop the left parenthesis
            if (top >= 0 && strcmp(stack[top].type, "FUNCTION") == 0) {
                output[j++] = stack[top--];
            }
        }
    }

    while (top >= 0) {
        output[j++] = stack[top--];
    }

    strcpy(output[j].type, "END");
}
