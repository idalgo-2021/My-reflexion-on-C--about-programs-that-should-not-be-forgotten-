#ifndef PARSER_H
#define PARSER_H

#define MAX_EXPR_LEN 100

typedef struct {
    char type[20];
    char value[MAX_EXPR_LEN];
} Token;

// проверочные функции
int isCorrectTokens(Token *tokens);
char *get_rpn_string(Token *rpn_tokens);

// главные функции
void tokenize(const char *expr, Token *tokens);
void shuntingYard(Token *tokens, Token *output);

//
int is_digit(char c);
int is_alpha(char c);
int isOperator(char c);
int isFunction(const char *str);
int isUnaryOperator(char c, const char *prevToken);

#endif  // PARSER_H