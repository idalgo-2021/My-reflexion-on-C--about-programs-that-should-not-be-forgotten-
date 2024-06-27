#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

void init(Stack* stack) { stack->top = NULL; }

void push(Stack* stack, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack* stack) {
    if (stack->top == NULL) {
        // fprintf(stderr, "ERROR: Stack is empty\n");
        return -1;  // Возвращаем -1 при попытке извлечения из пустого стека
    }
    int data = stack->top->data;
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

void destroy(Stack* stack) {
    while (stack->top != NULL) {
        Node* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
    }
}
