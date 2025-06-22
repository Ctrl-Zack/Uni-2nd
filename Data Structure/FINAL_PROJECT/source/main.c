#include "console_menu.h"
#include "database_menu.h"

int main()
{
    AVL records;
    avl_init(&records);
    
    loadDatabase(&records);

    int8_t menu_selected = -1;
    
    hideCursor();
    clearScreen();
    consoleMenu(menu_list, menu_count, &menu_selected, db_title);
    
    while (1)
    {
        if (consoleInput(menu_list, menu_count, &menu_selected)) {
            syncFile(records._root);
            break;
        }
        switch (menu_selected)
        {
        case 0:
            tambahData(&records);
            break;
        case 1:
            ubahData(&records);
            break;
        case 2:
            tampilkanIndex(&records);
            break;
        case 3:
            tampilkanTanpaIndex(&records);
            break;
        case 4:
            hapusData(&records);
            break;
        }

        consoleMenu(menu_list, menu_count, &menu_selected, db_title);
    }

    return 0;
}