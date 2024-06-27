#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct node* init(struct door* door) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->door = door;
    new_node->next = NULL;
    return new_node;
}

struct node* add_door(struct node* elem, struct door* door) {
    if (elem == NULL) {
        fprintf(stderr, "Error: Attempted to add door to a null element\n");
        exit(EXIT_FAILURE);
    }

    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->door = door;
    new_node->next = elem->next;
    elem->next = new_node;
    return new_node;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* current = root;
    while (current != NULL) {
        if (current->door->door_id == door_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;  // Door not found
}

struct node* remove_door(struct node* elem, struct node* root) {
    struct node* current = root;
    struct node* prev = NULL;

    while (current != NULL) {
        if (current == elem) {
            if (prev == NULL) {
                root = current->next;
            } else {
                prev->next = current->next;
            }
            // Проверяем, была ли уже удалена память для двери и узла списка
            if (current->door != NULL) {
                free(current->door);
            }
            free(current);
            return root;
        }
        prev = current;
        current = current->next;
    }

    // Узел для удаления не найден в списке
    printf("Error: Element to remove not found in list\n");
    return root;  // Element not found
}

void destroy(struct node* root) {
    struct node* current = root;
    while (current != NULL) {
        struct node* next = current->next;
        free(current->door);
        free(current);
        current = next;
    }
}
