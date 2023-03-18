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
        case TRES_TEAMS:
            client_print_teams(unparse_uuid(val->team.team_uuid),
                val->team.team_name, val->team.team_description);
            break;
        case TRES_CHANNELS:
            client_team_print_channels(unparse_uuid(val->channel.channel_uuid),
                val->channel.channel_name, val->channel.channel_description);
            break;
        case TRES_THREADS:
            client_channel_print_threads(unparse_uuid(val->thread.thread_uuid),
                unparse_uuid(val->thread.user_uuid),
                val->thread.thread_timestamp, val->thread.thread_title,
                val->thread.thread_body);
            break;
        case TRES_MESSAGES:
            client_thread_print_replies(unparse_uuid(val->message.thread_uuid),
                unparse_uuid(val->message.user),
                val->message.message_timestamp, val->message.body);
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

void RES(list)(const int sfd, teams_res_t *res)
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

void REQ(list)(teams_req_t *req, context_t *ctx)
{
    req->type = TREQ_LIST;
    manage_options(req, ctx);
}
