/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myteams-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#include "client.h"
#include "utils/error.h"
#include "utils/macro.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

static const struct option long_options[] = {
    {"help", optional_argument, 0, 'h'},
};

static inline void display_usage_and_quit(const int status)
{
    puts(USAGE);
    exit(status);
}
