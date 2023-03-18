/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "commands.h"

static void print_different_logs_evt(const teams_res_data_t *val,
    teams_res_type_t type)
{
    switch (type) {
        case TEVT_TEAMS:
            client_event_team_created(unparse_uuid(val->team.team_uuid),
                val->team.team_name, val->team.team_description);
            break;
        case TEVT_CHANNELS:
            client_event_channel_created(
                unparse_uuid(val->channel.channel_uuid),
                val->channel.channel_name, val->channel.channel_description);
            break;
        case TEVT_THREADS:
            client_event_thread_created(unparse_uuid(val->thread.thread_uuid),
                unparse_uuid(val->thread.user_uuid),
                val->thread.thread_timestamp, val->thread.thread_title,
                val->thread.thread_body);
            break;
        case TEVT_MESSAGES:
            client_event_thread_reply_received(unparse_uuid(val->message.team),
                unparse_uuid(val->message.thread_uuid),
                unparse_uuid(val->message.user), val->message.body);
            break;
        default: break;
    }
}

static void print_different_logs(const teams_res_data_t *val,
    teams_res_type_t type)
{
    switch (type) {
        case TRES_TEAMS:
            client_print_team_created(unparse_uuid(val->team.team_uuid),
                val->team.team_name, val->team.team_description);
            break;
        case TRES_CHANNELS:
            client_print_channel_created(
                unparse_uuid(val->channel.channel_uuid),
                val->channel.channel_name, val->channel.channel_description);
            break;
        case TRES_THREADS:
            client_print_thread_created(unparse_uuid(val->thread.thread_uuid),
                unparse_uuid(val->thread.user_uuid), val->thread.thread_timestamp,
                val->thread.thread_title, val->thread.thread_body);
            break;
        case TRES_MESSAGES:
            client_print_reply_created(unparse_uuid(val->message.thread_uuid),
                unparse_uuid(val->message.user),
                val->message.message_timestamp, val->message.body);
            break;
        default: print_different_logs_evt(val, type); break;
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

void RES(create)(const int sfd, teams_res_t *res)
{
    switch (CODE_SWITCH(res->code)) {
        case (COMPLETE_POSITIVE): print_logs(sfd, res); break;
        case (TRANSIENT_ERROR): print_log_error(res); break;
        case (PERMANENT_ERROR): client_error_already_exist(); break;
    }
}

static void manage_options(teams_req_t *req, context_t *ctx)
{
    ATTR_FREE_ARR char **args = get_all_args();

    if (!args[0])
        return;
    if (*ctx->thread) {
        MEMCPY_REQ(req->content.create.reply, args[0]);
        return;
    }
    if (!args[1])
        return;
    if (!*ctx->thread) {
        MEMCPY_REQ(req->content.create.thread.title, args[0]);
        MEMCPY_REQ(req->content.create.thread.message, args[1]);
    }
    if (!*ctx->team || !*ctx->channel) {
        MEMCPY_REQ(req->content.create.team.name, args[0]);
        MEMCPY_REQ(req->content.create.team.desc, args[1]);
    }
}

void REQ(create)(teams_req_t *req, context_t *ctx)
{
    req->type = TREQ_CREATE;
    memcpy(&req->content.create.context, ctx, sizeof(context_t));
    manage_options(req, ctx);
}
