/*
** EPITECH PROJECT, 2025
** minishell
** File description:
** fill binary tree
*/

#include "shell.h"
#include <stdio.h>

static int is_redirector(char *commands, int index)
{
    int len = 0;

    for (int i = 0; i < NB_REDIRECTOR; i++){
        len = my_strlen(redirectors[i].redirector);
        if (commands[index] == redirectors[i].redirector[len - 1])
            return SUCCESS;
    }
    return FAIL;
}

static char *split_command(char *commands, int index)
{
    char *second_split = malloc(sizeof(char) *
        (my_strlen(commands) - index + 1));

    if (!second_split)
        return NULL;
    for (int i = index; i < my_strlen(commands); i++){
        second_split[i - index] = commands[i];
    }
    second_split[my_strlen(commands) - index] = '\0';
    if (commands[index - 1] == '>' ||
        commands[index - 1] == '<' ||
        commands[index - 1] == '2')
        index--;
    commands[index] = '\0';
    second_split++;
    while (second_split[0] &&
        (second_split[0] == '\t' || second_split[0] == ' '))
        second_split++;
    return second_split;
}

static char *get_redirect(char *commands, int index)
{
    char *redirector = NULL;
    int len = 1;

    if (index > 0 && commands[index - 1] == commands[index])
        len++;
    if (commands[index] == '>' &&
        (index > 0 && commands[index - 1] == '2'))
        len++;
    redirector = malloc(sizeof(char) * (len + 1));
    if (!redirector)
        return NULL;
    for (int i = len - 1; i >= 0; i--){
        redirector[len - 1 - i] = commands[index - i];
    }
    redirector[len] = '\0';
    return redirector;
}

static int check_redirector(char *commands, int i, bintree_t **root)
{
    char *split = NULL;

    if (is_redirector(commands, i) == SUCCESS){
        (*root)->item = get_redirect(commands, i);
        if (!(*root)->item)
            return FAIL;
        split = split_command(commands, i);
        if (!split)
            return FAIL;
        (*root)->right = create_node_tree(split);
        (*root)->left = create_node_tree(commands);
        if (!(*root)->left || !(*root)->right)
            return FAIL;
        (*root) = (*root)->left;
    }
    return SUCCESS;
}

bintree_t *fill_tree(char *commands)
{
    bintree_t *root = create_node_tree(commands);
    int len = my_strlen(commands);
    bintree_t *tmp = root;

    if (!root)
        return NULL;
    for (int i = len - 1; i >= 0; i--){
        if (check_redirector(commands, i, &root) == FAIL){
            free_bintree(tmp);
            my_dprintf(STDERR_FD, "failed redirector.\n");
            return NULL;
        }
    }
    root = create_node_tree(commands);
    root = tmp;
    return root;
}
