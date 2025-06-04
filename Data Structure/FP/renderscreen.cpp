#include "renderscreen.h"
#include "menuconfig.h"

const char *PROMPT[5] = // 
{
    "1. CREATE\n",
    "2. READ\n",
    "3. UPDATE\n",
    "4. DELETE\n",
    "5. EXIT\n"
};

// 
const WORD COLOR_NORMAL = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
const WORD COLOR_SELECTED = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void clearConsole()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cell_count;
    COORD home_coords = { 0, 0 };

    if (GetConsoleScreenBufferInfo(console, &csbi))
    {
        cell_count = csbi.dwSize.X * csbi.dwSize.Y;
        FillConsoleOutputCharacter(console, ' ', cell_count, home_coords, &count);
        FillConsoleOutputAttribute(console, csbi.wAttributes, cell_count, home_coords, &count);
        SetConsoleCursorPosition(console, home_coords);
    }
}

void setCursorTop()
{
    COORD home_coords = {0, 0};
    SetConsoleCursorPosition(console, home_coords);
}

void renderBoxedMenu(uint8_t selected_option)
{
    setCursorTop();
    
    std::cout << "Database Operation Options\n";
    SetConsoleTextAttribute(console, COLOR_NORMAL);
    
    for (uint8_t i = S_ONE; i < MAX_OPTION; ++i)
    {
        SetConsoleTextAttribute(console, (i == selected_option) ? COLOR_SELECTED : COLOR_NORMAL);
        std::cout << PROMPT[i];
    }
    SetConsoleTextAttribute(console, COLOR_NORMAL);
}