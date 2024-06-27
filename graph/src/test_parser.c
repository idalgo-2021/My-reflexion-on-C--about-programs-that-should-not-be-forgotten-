///////////////////////////////////////////////////////////////////////////////////////////////////////
// Сборка и запуск: $ gcc -Wall -Werror -Wextra  -o test_parser parser.c test_parser.c && ./test_parser
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

void print_tokens(Token *tokens) {
    printf("Tokens:\n");
    for (int i = 0; strcmp(tokens[i].type, "END") != 0; ++i) {
        printf("Token %d: Type=%s, Value=%s\n", i, tokens[i].type, tokens[i].value);
    }
}

////

int _isCorrectTokens(Token *tokens) {
    int result = 1;
    int open_parens = 0;  // Счетчик открывающих скобок
    int exist_var = 0;

    for (int i = 0; strcmp(tokens[i].type, "END") != 0; ++i) {
        if (strcmp(tokens[i].type, "VARIABLE") == 0 && strcmp(tokens[i].value, "x") != 0) {
            result = 0;
            printf("    Token %d - token is erroneous\n", i);
        }

        if (strcmp(tokens[i].type, "LEFT_PAREN") == 0) {
            open_parens++;
        } else if (strcmp(tokens[i].type, "RIGHT_PAREN") == 0) {
            open_parens--;
            if (open_parens < 0) {
                result = 0;
                printf("    Token %d - mismatched parenthesis\n", i);
            }
        }

        if (exist_var == 0 && strcmp(tokens[i].type, "VARIABLE") == 0) {
            exist_var = 1;
        }
    }

    if (open_parens != 0) {
        result = 0;
        printf("    - Mismatched parentheses in expression\n");
    }

    if (exist_var == 0) {
        result = 0;
        printf("   - Variable is not exist in expression\n");
    }

    return result;
}

/////

int main() {
    system("clear");

    char *expressions[] = {"cos(0.5 * x)+ sin(x) + 2 * ln(3.14) - (-5.6)",
                           "-1/x",
                           "(-(x + 2*x)",
                           "-hjd 3/x + [{]{bbb}",
                           "fun(x+16)+sin(2*x)-cos(r*yx)",
                           "1/(2-2)",
                           "3/0"};
    // char *expressions[] = {"3/0"};

    int num_expressions = sizeof(expressions) / sizeof(expressions[0]);

    for (int i = 0; i < num_expressions; ++i) {
        printf("Testing expression: %s\n", expressions[i]);

        // Тестируем токенизацию
        Token tokens[MAX_EXPR_LEN];
        tokenize(expressions[i], tokens);
        print_tokens(tokens);

        printf("Checking validity:\n");
        // if (_isCorrectTokens(tokens)) {
        if (isCorrectTokens(tokens)) {
            printf("- tokens are correct\n");
        } else {
            printf("- tokens are not correct!\n");
            printf("- - - - - - - - - - - - - \n");
            continue;
        }

        // Строим RPN
        Token rpn_tokens[MAX_EXPR_LEN];
        shuntingYard(tokens, rpn_tokens);
        printf("RPN Expression: %s\n", get_rpn_string(rpn_tokens));

        printf("- - - - - - - - - - - - - \n");
    }

    return 0;
}
