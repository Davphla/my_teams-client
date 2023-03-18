/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#include "client.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

static const struct sockaddr_in DEFAULT_SOCKET = {.sin_family = AF_INET,
    .sin_addr.s_addr = INADDR_ANY,
    .sin_port = 0};

static inline void reset_fds(const int sfd, fd_set *fds)
{
    FD_ZERO(fds);
    FD_SET(sfd, fds);
    FD_SET(0, fds);
}

void manage_socket_protocol(int sfd, context_t *ctx);
int manage_user_cli(int sfd, context_t *ctx);
