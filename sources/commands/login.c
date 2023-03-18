/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "commands.h"

void RES(login)(UNUSED int sfd, teams_res_t *res)
{
    switch (CODE_SWITCH(res->code)) {
        case (COMPLETE_POSITIVE):
            client_event_logged_in(unparse_uuid(res->content.user.uuid),
                res->content.user.name);
            break;
    }
}

void REQ(login)(teams_req_t *req, UNUSED context_t *ctx)
{
    char *name = next_arg();

    req->type = TREQ_LOGIN;
    if (name) {
        MEMCPY_REQ(req->content.login.user, name);
    }
}
