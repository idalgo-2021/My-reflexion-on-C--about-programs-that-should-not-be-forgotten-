#include <stdio.h>
#include <stdlib.h>

int main() {
    char* arr = malloc(10);
    int* ptr = malloc(sizeof(int));
    short* ptr_shor = malloc(7 * sizeof(short));

    free(arr);
    free(ptr);
    free(ptr_shor);

    return 0;
}