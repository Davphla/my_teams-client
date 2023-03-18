/*
** EPITECH PROJECT, 2022
** teams [WSL: Ubuntu-20.04]
** File description:
** main
*/

#include "main.h"
#include <stdio.h>

static void get_flags(const int ac, char *const *av, opt_t *opt)
{
    int option;

    while ((option = getopt_long(ac, av, "h", long_options, NULL)) != EOF) {
        switch (option) {
            case 'h': display_usage_and_quit(EXIT_SUCCESS); break;
            default: display_usage_and_quit(EXIT_ERROR); break;
        }
    }
    strncpy(opt->ip, av[1], 16);
    opt->port = strtol(av[2], NULL, 10);
    if (errno)
        FATAL();
}

static void start(const int ac, char *const *av)
{
    opt_t opt = {0};

    get_flags(ac, av, &opt);
    main_loop(&opt);
}

int main(const int ac, char *const *av)
{
    if (ac < 3)
        display_usage_and_quit(EXIT_ERROR);
    start(ac, av);
    if (g_exit_status)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
