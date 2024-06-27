#include "rpn.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Вычисление RPN
double evaluateRPN(Token *rpn_tokens, double x) {
    double stack[MAX_EXPR_LEN];
    int top = -1;

    for (int i = 0; strcmp(rpn_tokens[i].type, "END") != 0; ++i) {
        if (strcmp(rpn_tokens[i].type, "NUMBER") == 0) {
            stack[++top] = atof(rpn_tokens[i].value);
        } else if (strcmp(rpn_tokens[i].type, "VARIABLE") == 0) {
            stack[++top] = x;
        } else if (strcmp(rpn_tokens[i].type, "OPERATOR") == 0) {
            double op2 = stack[top--];
            double op1 = stack[top--];
            double result = 0.0;

            switch (rpn_tokens[i].value[0]) {
                case '+':
                    result = op1 + op2;
                    break;
                case '-':
                    result = op1 - op2;
                    break;
                case '*':
                    result = op1 * op2;
                    break;
                case '/':
                    result = op1 / op2;
                    break;
                default:
                    printf("Unknown operator: %s\n", rpn_tokens[i].value);
                    exit(EXIT_FAILURE);
            }
            stack[++top] = result;
        } else if (strcmp(rpn_tokens[i].type, "UNARY_MINUS") == 0) {
            double op = stack[top];
            stack[top] = -op;
        } else if (strcmp(rpn_tokens[i].type, "FUNCTION") == 0) {
            double op = stack[top--];
            double result = 0.0;

            if (strcmp(rpn_tokens[i].value, "sin") == 0) {
                result = sin(op);
            } else if (strcmp(rpn_tokens[i].value, "cos") == 0) {
                result = cos(op);
            } else if (strcmp(rpn_tokens[i].value, "tan") == 0) {
                result = tan(op);
            } else if (strcmp(rpn_tokens[i].value, "ctg") == 0) {
                result = 1.0 / tan(op);
            } else if (strcmp(rpn_tokens[i].value, "sqrt") == 0) {
                result = sqrt(op);
            } else if (strcmp(rpn_tokens[i].value, "ln") == 0) {
                result = log(op);
            } else {
                printf("Unknown function: %s\n", rpn_tokens[i].value);
                exit(EXIT_FAILURE);
            }
            stack[++top] = result;
        } else {
            printf("Unknown token type: %s\n", rpn_tokens[i].type);
            exit(EXIT_FAILURE);
        }
    }

    return stack[top];
}
