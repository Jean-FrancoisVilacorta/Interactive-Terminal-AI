/*
** EPITECH PROJECT, 2025
** lib
** File description:
** binary tree
*/

#ifndef TREE
    #define TREE

typedef struct bintree_s {
    void *item;
    struct bintree_s *right;
    struct bintree_s *left;
} bintree_t;

bintree_t *create_node_tree(void *item);
void btree_apply_infix(bintree_t *root, int (*applyf)(void *));
void btree_apply_prefix(bintree_t *root, int (*applyf)(void *));
void btree_apply_suffix(bintree_t *root, int (*applyf)(void *));
void free_bintree(bintree_t *root);

#endif
