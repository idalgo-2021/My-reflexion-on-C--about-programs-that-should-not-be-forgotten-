#include "list.h"

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAIL 1

int test_add_and_remove_door() {
    // Allocate memory for three door structures
    struct door* door1 = (struct door*)malloc(sizeof(struct door));
    struct door* door2 = (struct door*)malloc(sizeof(struct door));
    struct door* door3 = (struct door*)malloc(sizeof(struct door));

    // Set door IDs
    door1->door_id = 1;
    door2->door_id = 2;
    door3->door_id = 3;

    struct node* root = init(door1);

    // Add door2 after door1
    struct node* door2_node = add_door(root, door2);

    // Remove door2 from the list
    if (door2_node != NULL) {
        root = remove_door(door2_node, root);
    } else {
        printf("Error: Door 2 not found after insertion\n");
        return FAIL;
    }

    // Add door3 at the end of the list
    struct node* door3_node = add_door(root, door3);

    // Remove door1 from the beginning of the list
    root = remove_door(root, root);

    // Remove door3 from the end of the list
    if (door3_node != NULL) {
        root = remove_door(door3_node, root);
    } else {
        printf("Error: Door 3 not found after insertion\n");
        return FAIL;
    }

    // Check if the list is empty
    if (root != NULL) {
        printf("Error: List should be empty\n");
        return FAIL;
    }

    return SUCCESS;
}

int main() {
    printf("Running unit tests 'list_test.c'\n");
    int result = test_add_and_remove_door();
    if (result == SUCCESS) {
        printf("All tests passed\n");
    } else {
        printf("Tests failed\n");
    }
    return 0;
}
