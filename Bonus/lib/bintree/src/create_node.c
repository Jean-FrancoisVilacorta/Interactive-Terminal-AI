/*
** EPITECH PROJECT, 2025
** bintree
** File description:
** create node
*/

#include "bintree.h"
#include "stdlib.h"

bintree_t *create_node_tree(void *item)
{
    bintree_t *node = malloc(sizeof(struct bintree_s));

    if (!node)
        return NULL;
    node->item = item;
    node->left = NULL;
    node->right = NULL;
    return node;
}
