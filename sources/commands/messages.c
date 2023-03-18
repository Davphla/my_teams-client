/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "commands.h"

static void print_logs(const int sfd, teams_res_t *res)
{
    size_t count = res->content.count;
    teams_res_data_t value[count];

    if (fill_res_struct(sfd, value, count * sizeof(teams_res_data_t)))
        return;
    for (size_t i = 0; i < count; i++) {
        client_private_message_print_messages(unparse_uuid(value[i].message.user),
            value[i].message.message_timestamp, value[i].message.body);
    }
}

void RES(messages)(const int sfd, teams_res_t *res)
{
    switch (CODE_SWITCH(res->code)) {
        case (COMPLETE_POSITIVE): print_logs(sfd, res); break;
        case (TRANSIENT_ERROR):
            client_error_unknown_user(unparse_uuid(res->content.uuid));
            break;
    }
}

void REQ(messages)(teams_req_t *req, UNUSED context_t *ctx)
{
    create_simple_req(req, TREQ_MESSAGES);
}
