/*
** EPITECH PROJECT, 2024
** btree_apply_suffix
** File description:
** apply suffixe
*/

#include "bintree.h"

void btree_apply_suffix(bintree_t *root, int (*applyf)(void *))
{
    if (!root)
        return;
    if (root->left)
        btree_apply_suffix(root->left, applyf);
    if (root->right)
        btree_apply_suffix(root->right, applyf);
    applyf(root->item);
    return;
}
