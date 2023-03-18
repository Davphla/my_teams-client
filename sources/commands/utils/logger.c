/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#include "commands.h"

void print_log_error(const teams_res_t *res)
{
    switch (res->type) {
        case TRES_TEAMS:
            client_error_unknown_team((char *) res->content.uuid);
            break;
        case TRES_CHANNELS:
            client_error_unknown_channel((char *) res->content.uuid);
            break;
        case TRES_THREADS:
            client_error_unknown_thread((char *) res->content.uuid);
            break;
        default: break;
    }
}
