/*
** EPITECH PROJECT, 2024
** btree_apply_prefix
** File description:
** apply prefix
*/

#include "bintree.h"

void btree_apply_prefix(bintree_t *root, int (*applyf)(void *))
{
    if (!root)
        return;
    applyf(root->item);
    if (root->left)
        btree_apply_prefix(root->left, applyf);
    if (root->right)
        btree_apply_prefix(root->right, applyf);
    return;
}
