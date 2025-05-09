/*
** EPITECH PROJECT, 2025
** bintre
** File description:
** free a tree
*/

#include "bintree.h"
#include <stdlib.h>

void free_bintree(bintree_t *root)
{
    if (!root)
        return;
    free_bintree(root->left);
    free_bintree(root->right);
    free(root);
}
