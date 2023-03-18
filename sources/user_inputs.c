/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "client.h"
#include "commands.h"
#include "utils/macro.h"
#include <stdio.h>
#include <unistd.h>

static void launch_command(const int sfd, char *input, context_t *ctx)
{
    char *cmd = strtok(input, CMD_SEPARATOR);
    teams_req_t req = {0};

    if (cmd == NULL)
        return;
    for (size_t i = 0; i < LEN(REQ_FUNC); i++) {
        if (strcmp(cmd, REQ_FUNC[i].cmd) == 0 && REQ_FUNC[i].method) {
            REQ_FUNC[i].method(&req, ctx);
            send_packet(sfd, &req);
            return;
        }
    }
    puts("Error");
}

int manage_user_cli(const int sfd, context_t *ctx)
{
    ATTR_FREE char *line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;

    line_size = getline(&line_buf, &line_buf_size, stdin);
    if (!line_buf_size || !line_size)
        return 1;
    launch_command(sfd, line_buf, ctx);
    return 0;
}
