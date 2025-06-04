#include <iostream>
#include "inputlogic.h"
#include "renderscreen.h"
#include "databaselogic.h"

#define HIDE_CURSOR std::cout << "\033[?25l"

int main()
{   
    HIDE_CURSOR;
    clearConsole();

    uint8_t selected_option = 0;
    bool is_selecting = true;
    renderBoxedMenu(selected_option);

    while (true)
    {
        if (selectLogic(selected_option, is_selecting)) break;
        std::cout << "\nYou selected option " << (selected_option + 1) << '\n';
    }

    std::cout << "exiting program...\n";
    return 0;
}
