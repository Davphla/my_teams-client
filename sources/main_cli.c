/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "main_cli.h"
#include "utils/error.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

static int init_socket(const opt_t *opt)
{
    int sfd;
    struct sockaddr_in addr = DEFAULT_SOCKET;

    CATCH_FATAL((sfd = socket(AF_INET, SOCK_STREAM, 0)));
    addr.sin_addr.s_addr = inet_addr(opt->ip);
    addr.sin_port = htons(opt->port);
    CATCH_FATAL(connect(sfd, (struct sockaddr *) &addr, sizeof(addr)));
    return sfd;
}

static int loop_select(const int sfd, const fd_set *fds, context_t *ctx)
{
    int error = 0;

    if (FD_ISSET(sfd, fds)) {
        manage_socket_protocol(sfd, ctx);
    }
    if (FD_ISSET(0, fds)) {
        error |= manage_user_cli(sfd, ctx);
    }
    return error;
}

int main_loop(const opt_t *opt)
{
    int sfd = init_socket(opt);
    context_t ctx = {0};
    fd_set fds;

    do {
        reset_fds(sfd, &fds);
        select(sfd + 1, &fds, NULL, NULL, NULL);
    } while (loop_select(sfd, &fds, &ctx) == 0);
    close(sfd);
    return 0;
}

SINGLETON(int, 0, global)
