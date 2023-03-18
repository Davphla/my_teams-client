/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "commands.h"

UNUSED void RES(help)(UNUSED int sfd, UNUSED teams_res_t *res)
{
}

void REQ(help)(UNUSED teams_req_t *req, UNUSED context_t *ctx)
{
    puts("Here's an help message !");
}
