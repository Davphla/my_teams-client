/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "commands.h"

#define MAX_ARGS_PARAMS 4

char **get_all_args(void)
{
    char **arr = calloc(MAX_ARGS_PARAMS, sizeof(char *));
    char *temp;
    int i = 0;

    if (!arr)
        return NULL;
    while (i < MAX_ARGS_PARAMS && (temp = next_arg())) {
        arr[i++] = strdup(temp);
    }
    arr[i] = NULL;
    return arr;
}
