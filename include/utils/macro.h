/*
** EPITECH PROJECT, 2022
** B-PSU-402-LYN-4-1-strace-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#include <bits/types/FILE.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN(a) (sizeof(a) / sizeof(a)[0])

#define FOREACH(NAME, DATA, SIZE)                                             \
    for (__typeof__(*(DATA)) *(NAME) = &(DATA)[0]; (NAME) < &(DATA)[(SIZE)];  \
         (NAME)++)

#define SINGLETON(t, init, name)                                              \
    t *s_##name()                                                             \
    {                                                                         \
        static t inst = init;                                                 \
        return &inst;                                                         \
    }

static inline void cleanup_free(void *p)
{
    free(*(void **) p);
}

#define ATTR_FREE __attribute__((__cleanup__(cleanup_free)))

static inline void cleanup_free_arr(void *p)
{
    int i = 0;
    void **ptr = *(void **) p;

    if (ptr == NULL)
        return;
    while (ptr[i]) {
        free(ptr[i++]);
    }
    free(ptr);
}

#define ATTR_FREE_ARR __attribute__((__cleanup__(cleanup_free_arr)))

#define LAMBDA(return_value, params, expression)                              \
    ({                                                                        \
        return_value lambda_func params expression;                           \
        &lambda_func;                                                         \
    })

#define UNUSED __attribute__((unused))

static inline void cleanup_fclose(FILE **fd)
{
    fclose(*fd);
}

#define ATTR_FCLOSE __attribute__((__cleanup__(cleanup_fclose)))

static inline size_t clamp(size_t value, size_t low, size_t high)
{
    if (value < low)
        return low;
    else if (high < value)
        return high;
    else
        return value;
}
