#ifndef RENDERSCREEN_H
#define RENDERSCREEN_H

#include <iostream>
#include <stdint.h>
#include <windows.h>

extern const char *PROMPT[5];
extern const WORD COLOR_NORMAL;
extern const WORD COLOR_SELECTED;
extern HANDLE console;

void clearConsole();
void setCursorTop();
void renderBoxedMenu(uint8_t selected_option);

#endif
