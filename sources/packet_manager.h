/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#include "client.h"
#include "commands.h"
#include "protocol/teams_res.h"
#include "utils/error.h"
#include <search.h>
#include <stdbool.h>
#include <sys/socket.h>

static inline bool compar(const teams_res_code_t a[], const teams_res_code_t b)
{
    for (size_t i = 0; i < 4; i++) {
        if (a[i] == b)
            return 0;
    }
    return 1;
}
