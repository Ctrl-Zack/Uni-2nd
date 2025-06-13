#include "inputlogic.h"
#include "renderscreen.h"
#include "menuconfig.h"

bool fuzzyMatch(const std::string &input, const std::string &target)
{
    size_t pos = 0;
    for (char c : input)
    {
        pos = target.find(tolower(c), pos);
        if (pos == std::string::npos)
            return false;
        ++pos;
    }
    return true;
}

bool selectLogic(uint8_t &selected_option, bool &is_selecting)
{
    std::string query;
    uint8_t selected_index = selected_option;

    while (is_selecting)
    {
        std::vector<uint8_t> filtered_indices;
        for (uint8_t i = 0; i < MAX_OPTION; ++i)
        {
            std::string lowered = menu_prompts[i];
            std::transform(lowered.begin(), lowered.end(), lowered.begin(), ::tolower);
            if (fuzzyMatch(query, lowered))
                filtered_indices.push_back(i);
        }

        if (filtered_indices.empty())
        {
            clearConsole();
            std::cout << "Search: " << query << "\n\n";
            std::cout << "No match found.\n";
        }
        else
        {
            setCursorTop();
            renderFilteredMenu(query, filtered_indices, selected_index);
        }

        char key_input = _getch();
        if (key_input == 0 || key_input == -32)
            key_input = _getch();

        switch (key_input)
        {
            case KEY_UP:
                if (selected_index > 0) --selected_index;
                break;
            case KEY_DOWN:
                if (selected_index < filtered_indices.size() - 1) ++selected_index;
                break;
            case KEY_ENTER:
                if (!filtered_indices.empty())
                {
                    selected_option = filtered_indices[selected_index];
                    is_selecting = false;
                }
                break;
            case KEY_BACKSPACE:
                if (!query.empty())
                {
                    query.pop_back();
                    selected_index = 0;
                }
                break;
            default:
                if (isprint(key_input))
                {
                    if(key_input >= K_ONE && key_input < K_ONE + MAX_OPTION)
                        selected_index = key_input - K_ONE;
                    else
                    {
                        query += key_input;
                        selected_index = 0;
                    }
                }
                break;
        }
    }

    is_selecting = true;
    return selected_option == EXIT_SELECT;
}