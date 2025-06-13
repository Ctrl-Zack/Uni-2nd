#ifndef RENDERSCREEN_H
#define RENDERSCREEN_H

#include <iostream>
#include <vector>
#include <string>
#include <stdint.h>
#include <windows.h>

extern const WORD COLOR_NORMAL;
extern const WORD COLOR_SELECTED;
extern HANDLE console;

void clearConsole();
void setCursorTop();
void renderFilteredMenu(const std::string &query, const std::vector<uint8_t> &filtered_indices, uint8_t selected);
void renderBoxedMenu(uint8_t selected_option);

#endif
