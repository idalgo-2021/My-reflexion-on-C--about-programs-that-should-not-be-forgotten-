#include "stack.h"

#include <stdio.h>

#define SUCCESS 0
#define FAIL 1

int test_push_pop() {
    Stack stack;
    init(&stack);

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    int popped = pop(&stack);
    if (popped != 30) {
        printf("Error: Expected value 30, got %d\n", popped);
        destroy(&stack);
        return FAIL;
    }

    popped = pop(&stack);
    if (popped != 20) {
        printf("Error: Expected value 20, got %d\n", popped);
        destroy(&stack);
        return FAIL;
    }

    popped = pop(&stack);
    if (popped != 10) {
        printf("Error: Expected value 10, got %d\n", popped);
        destroy(&stack);
        return FAIL;
    }

    // Check pop from an empty stack
    popped = pop(&stack);
    if (popped != -1) {  // -1 is returned when attempting to pop from an empty stack
        printf("Error: Expected value -1 when popping from an empty stack, got %d\n", popped);
        destroy(&stack);
        return FAIL;
    }

    destroy(&stack);
    return SUCCESS;
}

int main() {
    printf("Running unit tests 'stack_test.c'\n");
    int result = test_push_pop();
    if (result == SUCCESS) {
        printf("All tests passed\n");
    } else {
        printf("Tests failed\n");
    }
    return result;
}