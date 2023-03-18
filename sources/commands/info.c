/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "commands.h"

static void print_different_logs(const teams_res_data_t *val,
    teams_res_type_t type)
{
    switch (type) {
        case TRES_USER:
            client_print_user(unparse_uuid(val->user.uuid), val->user.name,
                val->user.status);
            break;
        case TRES_TEAMS:
            client_print_team(unparse_uuid(val->team.team_uuid),
                val->team.team_name, val->team.team_description);
            break;
        case TRES_CHANNELS:
            client_print_channel(unparse_uuid(val->channel.channel_uuid),
                val->channel.channel_name, val->channel.channel_description);
            break;
        case TRES_THREADS:
            client_print_thread(unparse_uuid(val->thread.thread_uuid),
                unparse_uuid(val->thread.user_uuid),
                val->thread.thread_timestamp, val->thread.thread_title,
                val->thread.thread_body);
            break;
        default: break;
    }
}

static void print_logs(const int sfd, const teams_res_t *res)
{
    size_t count = res->content.count;
    teams_res_data_t value[count];

    if (fill_res_struct(sfd, value, count * sizeof(teams_res_data_t)))
        return;
    for (size_t i = 0; i < count; i++) {
        print_different_logs(&value[i], res->type);
    }
}

void RES(info)(const int sfd, teams_res_t *res)
{
    switch (CODE_SWITCH(res->code)) {
        case (COMPLETE_POSITIVE): print_logs(sfd, res); break;
        case (TRANSIENT_ERROR): print_log_error(res); break;
    }
}

static void manage_options(teams_req_t *req, context_t *ctx)
{
    if (*ctx->thread) {
        MEMCPY_REQ(req->content.uuid, ctx->thread);
        return;
    }
    if (*ctx->channel) {
        MEMCPY_REQ(req->content.uuid, ctx->channel);
        return;
    }
    if (*ctx->team) {
        MEMCPY_REQ(req->content.uuid, ctx->team);
        return;
    }
}

void REQ(info)(teams_req_t *req, context_t *ctx)
{
    req->type = TREQ_INFO;
    manage_options(req, ctx);
}
