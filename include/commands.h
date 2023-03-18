/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#include "client.h"
#include "protocol/teams_req.h"
#include "protocol/teams_res.h"
#include "teams_log.h"
#include "utils/error.h"
#include "utils/macro.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define CMD_SEPARATOR " \n\0"
#define REQ_PARAMS teams_req_t *req, context_t *ctx
#define RES_PARAMS int sfd, teams_res_t *res

#define PRT(...) __VA_ARGS__

#define NO_CODES PRT({})
#define CDS(...)                                                              \
    {                                                                         \
        __VA_ARGS__                                                           \
    }

// CDS : CODES
#define X_CMD                                                                 \
    X(noop, CDS(TC_OK))                                                       \
    X(login, CDS(TC_LOGIN_OK, TC_LOGIN_EVT, TC_LOGIN_ERROR))                  \
    X(logout, CDS(TC_LOGOUT_OK, TC_LOGOUT_EVT, TC_LOGOUT_ERROR))              \
    X(create, CDS(TC_CREATE_OK, TC_CREATE_ERROR))                             \
    X(list, CDS(TC_LIST_OK, TC_LIST_ERROR))                                   \
    X(info, CDS(TC_INFO_OK, TC_INFO_ERROR))                                   \
    X(users, CDS(TC_USERS_OK))                                                \
    X(user, CDS(TC_USER_OK, TC_USER_ERROR))                                   \
    X(send, CDS(TC_SEND_OK, TC_SEND_ERROR))                                   \
    X(subscribe, CDS(TC_SUBSCRIBE_OK, TC_SUBSCRIBE_ERROR))                    \
    X(subscribed, CDS(TC_SUBSCRIBED_OK, TC_SUBSCRIBED_ERROR))                 \
    X(unsubscribe, CDS(TC_UNSUBSCRIBE_OK, TC_UNSUBSCRIBE_ERROR))              \
    X(messages, CDS(TC_MESSAGES_OK, TC_MESSAGES_ERROR))                       \
    X(help, NO_CODES)                                                         \
    X(use, NO_CODES)

#define REQ(name) req_##name
#define RES(name) res_##name

#define X(name, res_code) void REQ(name)(REQ_PARAMS);

X_CMD

#undef X

#define X(name, res_code) void RES(name)(RES_PARAMS);

X_CMD

#undef X

typedef void (*req_method_t)(REQ_PARAMS);

typedef void (*res_method_t)(RES_PARAMS);

#define X(name, res_code) {#name, REQ(name)},
static const struct req_methods {
    char *cmd;
    req_method_t method;
} REQ_FUNC[] = {X_CMD};
#undef X

#define X(name, res_code) {res_code, RES(name)},
static const struct res_methods {
    teams_res_code_t codes[3];
    res_method_t method;
} RES_FUNC[] = {X_CMD};
#undef X

#define CODE_SWITCH(code) ((code) / 100)

#define COMPLETE_POSITIVE 2
#define INTERMEDIATE_POSITIVE 3
#define TRANSIENT_ERROR 4
#define PERMANENT_ERROR 5

#define MEMCPY_REQ(dest, src)                                                 \
    memcpy(dest, src, clamp(strlen((char *) (src)), 0, sizeof(dest)))

static inline char *next_arg(void)
{
    char *str = strtok(NULL, CMD_SEPARATOR);
    char *end;

    if (*str == '"') {
        end = strtok(NULL, "\"");
        if (!end)
            return str;
        for (int i = 0; str + i != end; i++) {
            if (!str[i]) {
                str[i] = ' ';
            }
        }
        str += 1;
    }
    return str;
}

static inline void send_packet(const int sfd, const teams_req_t *req)
{
    if (req->type) {
        send(sfd, req, sizeof(*req), 0);
    }
}

static inline void create_simple_req(teams_req_t *req,
    enum teams_req_type type)
{
    char *uuid = next_arg();

    req->type = type;
    if (uuid) {
        MEMCPY_REQ(req->content.uuid, uuid);
    }
}

static inline _Bool fill_res_struct(const int sfd, void *data, size_t size)
{
    if (recv(sfd, &data, size, MSG_WAITALL) != (ssize_t) size) {
        NOT_FATAL();
        return 1;
    }
    return 0;
}

static inline char *unparse_uuid(const uuid_t uuid)
{
    char *full_uuid = malloc(sizeof(char) * 40);

    uuid_unparse(uuid, full_uuid);
    return full_uuid;
}

char **get_all_args(void);

void print_log_error(const teams_res_t *res);
