// bst_static.h
#ifndef BST_STATIC_H
#define BST_STATIC_H

#include <stddef.h>

struct value {
    int val;
};

struct bst {
    size_t capacity;
    size_t size;
    struct value **data;
};

struct bst *init(size_t capacity);
void add(struct bst *tree, int value);
int search(struct bst *tree, int value);
void bst_free(struct bst *tree);

#endif  // BST_STATIC_H

// bst_static.c
#include "bst_static.h"
#include <stdlib.h>

struct bst *init(size_t capacity) {
    struct bst *tree = (struct bst *)malloc(sizeof(struct bst));
    if (tree != NULL) {
        tree->capacity = capacity;
        tree->size = 0;
        tree->data = (struct value **)malloc(capacity * sizeof(struct value *));
    }
    return tree;
}

static void resize(struct bst *tree) {
    size_t new_capacity = tree->capacity * 2;
    tree->data = (struct value **)realloc(tree->data, new_capacity * sizeof(struct value *));
    tree->capacity = new_capacity;
}

void add(struct bst *tree, int value) {
    if (tree->size == tree->capacity) {
        resize(tree);
    }

    size_t index = tree->size;
    tree->size++;

    tree->data[index] = (struct value *)malloc(sizeof(struct value));
    tree->data[index]->val = value;

    // Adjust the position in the array to maintain BST property
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (tree->data[index]->val < tree->data[parent]->val) {
            // Swap values
            struct value *temp = tree->data[index];
            tree->data[index] = tree->data[parent];
            tree->data[parent] = temp;

            // Move up in the tree
            index = parent;
        } else {
            break;
        }
    }
}

int search(struct bst *tree, int value) {
    for (size_t i = 0; i < tree->size; i++) {
        if (tree->data[i]->val == value) {
            return i;
        }
    }
    return -1;
}

static void free_values(struct value **data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        free(data[i]);
    }
}

void bst_free(struct bst *tree) {
    free_values(tree->data, tree->size);
    free(tree->data);
    free(tree);
}
