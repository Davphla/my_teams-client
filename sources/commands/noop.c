/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "commands.h"

void RES(noop)(UNUSED int sfd, teams_res_t *res)
{
    switch (CODE_SWITCH(res->code)) {
        case (COMPLETE_POSITIVE): puts("It's working great buddy !"); break;
    }
}

void REQ(noop)(teams_req_t *req, UNUSED context_t *ctx)
{
    req->type = TREQ_NOOP;
}
