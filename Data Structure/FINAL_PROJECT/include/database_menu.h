#ifndef DATABASEMENU_H
#define DATABASEMENU_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <conio.h>
#include "avl_tree.h"
#include "console_menu.h"

extern const char *file_name;

void saveData(DataKomponen d);
void rewriteFile(FILE *fp, AVLNode *records);
void syncFile(AVLNode *records);
void loadDatabase(AVL *records);
void tambahData(AVL *records);
void ubahData(AVL *records);
void tampilkanIndex(AVL *records);
void tampilkanTanpaIndex(AVL *records);
void hapusData(AVL *records);

#endif