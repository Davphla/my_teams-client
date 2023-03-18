/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#include <linux/limits.h>
#include <uuid/uuid.h>

#define USAGE                                                                 \
    "USAGE: ./myteams_cli ip port\n"                                          \
    "   ip is the server ip address on which the server socket listens\n"     \
    "   port is the port number on which the server socket listens"

typedef struct opt_s {
    char ip[16];
    unsigned short port;
} opt_t;

int main_loop(const opt_t *opt);

#define FD_COUNT 3
enum fds_e { READ, WRITE, EXCEPTION };

typedef struct context_s {
    uuid_t user;
    uuid_t team;
    uuid_t channel;
    uuid_t thread;
} context_t;
