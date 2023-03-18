/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "commands.h"

UNUSED void RES(use)(UNUSED int sfd, UNUSED teams_res_t *res)
{
}

void REQ(use)(UNUSED teams_req_t *req, context_t *ctx)
{
    ATTR_FREE_ARR char **args = get_all_args();

    memset(ctx->team, 0, sizeof(context_t) - sizeof(uuid_t));
    if (args[0]) {
        MEMCPY_REQ(ctx->team, args[0]);
    }
    if (args[1]) {
        MEMCPY_REQ(ctx->channel, args[1]);
    }
    if (args[2]) {
        MEMCPY_REQ(ctx->thread, args[2]);
    }
}
