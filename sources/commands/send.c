/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "commands.h"

void RES(send)(UNUSED int sfd, teams_res_t *res)
{
    switch (CODE_SWITCH(res->code)) {
        case (COMPLETE_POSITIVE):
            client_event_private_message_received(
                unparse_uuid(res->content.message.user), res->content.message.body);
            break;
        case (TRANSIENT_ERROR):
            client_error_unknown_user(unparse_uuid(res->content.uuid));
            break;
    }
}

void REQ(send)(teams_req_t *req, UNUSED context_t *ctx)
{
    ATTR_FREE_ARR char **args = get_all_args();

    req->type = TREQ_SEND;
    if (!args[0] || !args[1])
        return;
    MEMCPY_REQ(req->content.send.user, args[0]);
    MEMCPY_REQ(req->content.send.body, args[1]);
}
