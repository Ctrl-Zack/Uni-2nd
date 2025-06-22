#include "console_menu.h"

void hideCursor()
{
    printf("%s", C_HIDECURSOR);
}

void showCursor()
{
    printf("%s", C_SHOWCURSOR);
}

void clearScreen()
{
    printf("%s%s", C_CLEARSCREEN, C_CURSORPOS);
}

void consoleMenu(const char *menu_list[], const int8_t menu_count, int8_t *menu_selected, const char *title)
{
    printf("%s", C_CURSORPOS);
    printf("%s\n", title);

    for (uint8_t i = 0; i < menu_count; i++)
    {
        if (i == *menu_selected) printf("%s %d.%s%s\n", C_HIGHLIGHT, (int)i + 1, menu_list[i], C_RESETATTR);
        else printf(" %d.%s\n", (int)i + 1, menu_list[i]);
    }
    
}

_Bool consoleInput(const char *menu_list[], const int8_t menu_count, int8_t *menu_selected)
{
    _Bool is_selecting = 1;
    while (is_selecting)
    {
        int8_t select = *menu_selected;

        uint8_t ch = getch();
        
        if (ch == K_SPECIAL)
        {
            ch = getch();
            switch (ch)
            {
            case K_UP:
                if (select > 0) select--;
                break;
            case K_DOWN:
                if (select < menu_count - 1) select++;
                break;
            case K_LEFT: case K_RIGHT:
                break;
            }
        }
        else
        {
            switch (ch)
            {
                case K_ENTER:
                    if (select == -1) select = S_K;
                    is_selecting = 0;
                    break;
                case 'm': case 'M':
                    select = S_M; break;
                case 'u': case 'U':
                    select = S_U; break;
                case 'x': case 'X':
                    select = S_X; break;
                case 't': case 'T':
                    select = S_T; break;
                case 'h': case 'H':
                    select = S_H; break;
                case 'k': case 'K':
                    select = S_K; break;
                default:
                    if (ch >= '1' && ch <= '6') select = ch - '1';
            }
        }

        if (select != *menu_selected)
        {
            *menu_selected = select;
            consoleMenu(menu_list, menu_count, menu_selected, db_title);
        }
    }

    if (*menu_selected == S_K) return 1;
    return 0;
}

_Bool generalConsoleInput(const char *menu_list[], const int8_t menu_count, int8_t *menu_selected, const char *title)
{
    _Bool is_selecting = 1;
    while (is_selecting)
    {
        int8_t select = *menu_selected;

        uint8_t ch = getch();
        
        if (ch == K_SPECIAL)
        {
            ch = getch();
            switch (ch)
            {
            case K_UP:
                if (select > 0) select--;
                break;
            case K_DOWN:
                if (select < menu_count - 1) select++;
                break;
            case K_LEFT: case K_RIGHT:
                break;
            }
        }
        else
        {
            switch (ch)
            {
                case K_ENTER:
                    if (select == -1) select = S_K;
                    is_selecting = 0;
                    break;
                default:
                    if (ch >= 49 && ch <= 49 + menu_count - 1) select = ch - '1';
            }
        }

        if (select != *menu_selected)
        {
            *menu_selected = select;
            consoleMenu(menu_list, menu_count, menu_selected, title);
        }
    }

    if (*menu_selected == S_K) return 1;
    return 0;
}