#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdint.h>

#define KEY_UP      72  // 
#define KEY_DOWN    80  // 
#define KEY_ENTER   13  // 
#define MAX_OPTION  5   // 
#define HIDE_CURSOR std::cout << "\033[?25l"


enum SelectedOptions    // 
{
    S_ONE,              // 
    S_TWO,              // 
    S_THREE,            // 
    S_FOUR,             // 
    S_FIVE              // 
};

enum KeyOptions         // 
{
    K_ONE = 49,         // 
    K_TWO,              // 
    K_THREE,            // 
    K_FOUR,             // 
    K_FIVE              // 
};

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

void renderBoxedMenu(int selected_option)
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
    
        if (selected_before != selected_option) renderBoxedMenu(selected_option);
    }
    
    is_selecting = true;
    if (selected_option == S_FIVE) return 1;
    return 0;
}

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
