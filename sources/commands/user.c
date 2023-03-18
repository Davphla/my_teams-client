/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "commands.h"

void RES(user)(UNUSED int sfd, teams_res_t *res)
{
    switch (CODE_SWITCH(res->code)) {
        case (COMPLETE_POSITIVE):
            client_print_user(unparse_uuid(res->content.user.uuid),
                res->content.user.name, res->content.user.status);
            break;
        case (TRANSIENT_ERROR):
            client_error_unknown_user(unparse_uuid(res->content.uuid));
            break;
    }
}

void REQ(user)(teams_req_t *req, UNUSED context_t *ctx)
{
    create_simple_req(req, TREQ_USER);
}
