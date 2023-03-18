/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-strace-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#define EXIT_SUCCESS 0
#define EXIT_ERROR 84

#include "color.h"
#include "macro.h"
#include "stdarg.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum error_e {
    FATAL,
    EMERGENCY,
    ALERT,
    CRITICAL,
    ERROR,
    WARN,
    NOTE,
    INFO,
    DEBUG
};

int *s_global(void);
#define g_exit_status *s_global()

#define ERROR__(...)                                                          \
    fprintf(stderr, "%s (%s:%d", __FUNCTION__, __FILE__, __LINE__);           \
    fprintf(stderr, ")" __VA_OPT__(": ") __VA_ARGS__);                        \
    if (errno) {                                                              \
        fprintf(stderr, ": %s", strerror(errno));                             \
    }                                                                         \
    fprintf(stderr, "\n");

#define NOT_FATAL(...)                                                        \
    do {                                                                      \
        fprintf(stderr, C_RED C_BOLD "[NOT FATAL] " C_NONE);                  \
        g_exit_status = 1;                                                    \
        ERROR__(__VA_ARGS__)                                                  \
        errno = 0;                                                            \
    } while (0)

#define FATAL(...)                                                            \
    do {                                                                      \
        fprintf(stderr, "===== FATAL =====\n");                               \
        ERROR__(__VA_ARGS__)                                                  \
        exit(EXIT_ERROR);                                                     \
    } while (0)

// Fatal Error
#define CATCH_FATAL(return_val, ...)                                          \
    do {                                                                      \
        if (return_val == -1 && errno)                                        \
            FATAL(__VA_ARGS__);                                               \
    } while (0)

// Not fatal error
#define CATCH_NOT_FATAL(return_val, ...)                                      \
    do {                                                                      \
        if (return_val == -1 && errno) {                                      \
            NOT_FATAL(__VA_ARGS__);                                           \
        }                                                                     \
    } while (0)
