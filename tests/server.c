/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "../include/commands.h"
#include <assert.h>
#include <criterion/criterion.h>
#include <netinet/in.h>
#include <unistd.h>

static int create_socket()
{
    int sfd;
    struct sockaddr_in MAIN_SOCKET = {.sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(4240)};

    CATCH_FATAL((sfd = socket(AF_INET, SOCK_STREAM, 0)));
    CATCH_FATAL(
        bind(sfd, (struct sockaddr *) &MAIN_SOCKET, sizeof(MAIN_SOCKET)));
    CATCH_FATAL(listen(sfd, 1));
    return sfd;
}

Test(a, b)
{
    int sfd = create_socket();
    int cfd = accept(sfd, NULL, NULL);
    teams_req_t req;
    teams_res_t res = {.code = TC_LOGIN_OK,
        .content.user.uuid = "abcd",
        .content.user.name = "David",
        .content.user.status = 1,
        .type = 0};

    CATCH_FATAL(recv(cfd, &req, sizeof(req), 0));
    cr_assert(req.type == TREQ_LOGIN, "Wrong type");
    CATCH_FATAL(send(cfd, &res, sizeof(res), 0));
}
