/*
** EPITECH PROJECT, 2022
** B-NWP-400-LYN-4-1-myftp-david.gozlan
** File description:
** TODO: add description
*/

#pragma once

#ifndef NO_COLOR

    #define C_NONE "\e[0m"
    #define C_BLACK "\e[0;30m"
    #define C_LBLACK "\e[1;30m"
    #define C_RED "\e[0;31m"
    #define C_LRED "\e[1;31m"
    #define C_GREEN "\e[0;32m"
    #define C_LGREEN "\e[1;32m"
    #define C_BROWN "\e[0;33m"
    #define C_YELLOW "\e[1;33m"
    #define C_BLUE "\e[0;34m"
    #define C_LBLUE "\e[1;34m"
    #define C_PURPLE "\e[0;35m"
    #define C_LPURPLE "\e[1;35m"
    #define C_CYAN "\e[0;36m"
    #define C_LCYAN "\e[1;36m"
    #define C_GRAY "\e[0;37m"
    #define C_WHITE "\e[1;37m"
    #define C_BOLD "\e[1m"
    #define C_ULINE "\e[4m"
    #define C_BLINK "\e[5m"
    #define C_REV "\e[7m"
    #define C_HIDE "\e[8m"

#else

    #define C_NONE ""
    #define C_BLACK ""
    #define C_LBLACK ""
    #define C_RED ""
    #define C_LRED ""
    #define C_GREEN ""
    #define C_LGREEN ""
    #define C_BROWN ""
    #define C_YELLOW ""
    #define C_BLUE ""
    #define C_LBLUE ""
    #define C_PURPLE ""
    #define C_LPURPLE ""
    #define C_CYAN ""
    #define C_LCYAN ""
    #define C_GRAY ""
    #define C_WHITE ""
    #define C_BOLD ""
    #define C_ULINE ""
    #define C_BLINK ""
    #define C_REV ""
    #define C_HIDE ""
    #define C_HIDE ""

#endif
