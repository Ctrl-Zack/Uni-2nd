#include "renderscreen.h"
#include "menuconfig.h"

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

void renderFilteredMenu(const std::string &query, const std::vector<uint8_t> &filtered_indices, uint8_t selected_option)
{
    setCursorTop();

    std::cout << "Database Operation Options\n";
    std::cout << "Search (type to filter, Enter to select): " << query << std::string(40 - query.length(), ' ') << "\n\n";

    for (uint8_t i = 0; i < filtered_indices.size(); ++i)
    {
        uint8_t index = filtered_indices[i];
        SetConsoleTextAttribute(console, (i == selected_option) ? COLOR_SELECTED : COLOR_NORMAL);
        // std::cout << menu_prompts[index] << '\n';
        std::cout << menu_prompts[index] << std::string(40 - menu_prompts[index].size(), ' ') << '\n';
    }

    SetConsoleTextAttribute(console, COLOR_NORMAL);

    for (int i = filtered_indices.size(); i < MAX_OPTION; ++i)
        std::cout << std::string(40, ' ') << '\n';
}

void renderBoxedMenu(uint8_t selected_option)
{
    setCursorTop();
    
    std::cout << "Database Operation Options\n";
    std::cout << "Search (type to filter, Enter to select): \n\n";
    
    for (uint8_t i = 0; i < MAX_OPTION; ++i)
    {
        SetConsoleTextAttribute(console, (i == selected_option) ? COLOR_SELECTED : COLOR_NORMAL);
        std::cout << menu_prompts[i] << '\n';
    }
    SetConsoleTextAttribute(console, COLOR_NORMAL);
}