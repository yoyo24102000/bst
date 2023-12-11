// bst.h
#ifndef BST_H
#define BST_H

struct bst_node {
    int value;
    struct bst_node *left;
    struct bst_node *right;
};

struct bst_node *create_node(int value);
struct bst_node *add_node(struct bst_node *tree, int value);
struct bst_node *delete_node(struct bst_node *tree, int value);
void free_bst(struct bst_node *tree);

#endif  // BST_H

// bst.c
#include "bst.h"
#include <stddef.h>
#include <stdlib.h>

struct bst_node *create_node(int value) {
    struct bst_node *node = (struct bst_node *)malloc(sizeof(struct bst_node));
    if (node != NULL) {
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

static struct bst_node *find_min(struct bst_node *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

struct bst_node *delete_node(struct bst_node *tree, int value) {
    if (tree == NULL) {
        return NULL;
    }

    if (value < tree->value) {
        tree->left = delete_node(tree->left, value);
    } else if (value > tree->value) {
        tree->right = delete_node(tree->right, value);
    } else {
        if (tree->left == NULL) {
            struct bst_node *temp = tree->right;
            free(tree);
            return temp;
        } else if (tree->right == NULL) {
            struct bst_node *temp = tree->left;
            free(tree);
            return temp;
        }

        struct bst_node *temp = find_min(tree->right);
        tree->value = temp->value;
        tree->right = delete_node(tree->right, temp->value);
    }

    return tree;
}

struct bst_node *add_node(struct bst_node *tree, int value) {
    if (tree == NULL) {
        return create_node(value);
    }

    if (value < tree->value) {
        tree->left = add_node(tree->left, value);
    } else if (value > tree->value) {
        tree->right = add_node(tree->right, value);
    }

    return tree;
}

void free_bst(struct bst_node *tree) {
    if (tree != NULL) {
        free_bst(tree->left);
        free_bst(tree->right);
        free(tree);
    }
}
