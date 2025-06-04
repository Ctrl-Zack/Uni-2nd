#include "inputlogic.h"
#include "renderscreen.h"
#include "menuconfig.h"

bool selectLogic(uint8_t &selected_option, bool &is_selecting)
{
    while (is_selecting)
    {
        char key_input = _getch();
        if (key_input == 0 || key_input == -32) key_input = _getch();

        int selected_before = selected_option;

        switch (key_input)
        {
            case KEY_UP:
                if (selected_option > 0) --selected_option;
                break;
            case KEY_DOWN:
                if (selected_option < MAX_OPTION - 1) ++selected_option;
                break;
            case KEY_ENTER:
                is_selecting = false;
                break;
            case K_ONE:
                selected_option = S_ONE;
                break;
            case K_TWO:
                selected_option = S_TWO;
                break;
            case K_THREE:
                selected_option = S_THREE;
                break;
            case K_FOUR:
                selected_option = S_FOUR;
                break;
            case K_FIVE:
                selected_option = S_FIVE;
                break;
        }

        if (selected_before != selected_option)
            renderBoxedMenu(selected_option);
    }

    is_selecting = true;
    return selected_option == S_FIVE;
}