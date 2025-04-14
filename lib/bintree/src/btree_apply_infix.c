/*
** EPITECH PROJECT, 2024
** btree_apply_infixe
** File description:
** apply infixe
*/

#include "bintree.h"

void btree_apply_infix(bintree_t *root, int (*applyf)(void *))
{
    if (!root)
        return;
    if (root->left)
        btree_apply_infix(root->left, applyf);
    applyf(root->item);
    if (root->right)
        btree_apply_infix(root->right, applyf);
    return;
}
