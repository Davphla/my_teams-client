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
        client_print_users(unparse_uuid(value[i].user.uuid), value[i].user.name,
            value[i].user.status);
    }
}

void RES(users)(const int sfd, teams_res_t *res)
{
    switch (CODE_SWITCH(res->code)) {
        case (COMPLETE_POSITIVE): print_logs(sfd, res); break;
    }
}

void REQ(users)(teams_req_t *req, UNUSED context_t *ctx)
{
    req->type = TREQ_USERS;
}
