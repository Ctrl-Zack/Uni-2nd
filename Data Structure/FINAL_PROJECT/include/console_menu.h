    #ifndef CONSOLEMENU_H
    #define CONSOLEMENU_H

    #include <stdio.h>
    #include <stdint.h>
    #include <conio.h>

    #define C_RESETATTR     "\e[0m"
    #define C_HIGHLIGHT     "\e[30;1;107m"
    #define C_BOLD          "\e[1m"
    #define C_CURSORPOS     "\e[1;1H"
    #define C_CLEARSCREEN   "\e[2J"
    #define C_HIDECURSOR    "\e[?25l"
    #define C_SHOWCURSOR    "\e[?25h"
    #define K_SPECIAL       224
    #define K_UP            72
    #define K_DOWN          80
    #define K_LEFT          75
    #define K_RIGHT         77
    #define K_ENTER         13
    #define S_M             0
    #define S_U             1
    #define S_X             2
    #define S_T             3
    #define S_H             4
    #define S_K             5

    extern const char *db_title;
    extern const int8_t menu_count;
    extern const char *menu_list[];

    extern const char *add_title;
    extern const int8_t add_op_count;
    extern const char *add_option[];

    void hideCursor();
    void showCursor();
    void clearScreen();
    void consoleMenu(const char *menu_list[], const int8_t menu_count, int8_t *menu_selected, const char *title);
    _Bool consoleInput(const char *menu_list[], const int8_t menu_count, int8_t *menu_selected);
    _Bool generalConsoleInput(const char *menu_list[], const int8_t menu_count, int8_t *menu_selected, const char *title);

    #endif