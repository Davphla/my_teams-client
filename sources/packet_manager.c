/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "packet_manager.h"

static bool change_evt_ctx(const teams_res_t *res, context_t *ctx)
{
    switch (res->code) {
        case (TC_LOGIN_OK):
            MEMCPY_REQ(ctx->user, res->content.user.uuid);
            break;
        case (TC_LOGOUT_OK): ctx->user[0] = 0; break;
    }
    return false;
}
static void launch_cmd(const int sfd, teams_res_t *res, context_t *ctx)
{
    size_t i = 0;

    while (i < LEN(RES_FUNC) && compar(RES_FUNC[i].codes, res->code)) {
        i++;
    }
    if (i == LEN(RES_FUNC))
        return;
    RES_FUNC[i].method(sfd, res);
    change_evt_ctx(res, ctx);
}

static bool special_codes(const teams_res_t *res)
{
    switch (res->code) {
        case (TC_INTERNAL_ERROR): return true;
        case (TC_NOT_LOGGED_IN):
        case (TC_UNAUTHORIZED): client_error_unauthorized(); return true;
        case (TC_ALREADY_EXISTS): client_error_already_exist(); return true;
    }
    return false;
}

void manage_socket_protocol(const int sfd, context_t *ctx)
{
    teams_res_t res;

    if (recv(sfd, &res, sizeof(res), MSG_PEEK) != sizeof(res))
        return;
    recv(sfd, &res, sizeof(res), MSG_WAITALL);
    if (special_codes(&res))
        return;
    launch_cmd(sfd, &res, ctx);
}
