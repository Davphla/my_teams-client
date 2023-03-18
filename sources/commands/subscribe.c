/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "commands.h"

void RES(subscribe)(UNUSED int sfd, teams_res_t *res)
{
    switch (CODE_SWITCH(res->code)) {
        case (COMPLETE_POSITIVE):
            client_print_subscribed(unparse_uuid(res->content.team.user),
                unparse_uuid(res->content.team.team));
            break;
        case (TRANSIENT_ERROR):
            client_error_unknown_team(unparse_uuid(res->content.uuid));
            break;
    }
}

void REQ(subscribe)(teams_req_t *req, UNUSED context_t *ctx)
{
    create_simple_req(req, TREQ_SUBSCRIBE);
}
