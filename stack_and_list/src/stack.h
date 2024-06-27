#ifndef STACK_H
#define STACK_H

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

void init(Stack* stack);
void push(Stack* stack, int data);
int pop(Stack* stack);
void destroy(Stack* stack);

#endif /* STACK_H */
