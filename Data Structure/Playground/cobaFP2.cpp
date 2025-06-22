#include <iostream>
#include <vector>
#include <string>
#include <conio.h> // untuk _getch()
#include <algorithm>

using namespace std;

void clearScreen() {
    system("cls"); // Gunakan "clear" jika di Linux
}

bool fuzzyMatch(const string& input, const string& option) {
    size_t pos = 0;
    for (char c : input) {
        pos = option.find(tolower(c), pos);
        if (pos == string::npos) return false;
        ++pos;
    }
    return true;
}

int main() {
    vector<string> options = {
        "Open File", "Save File", "Close Project", "Exit", "Open Recent", "Search Files", "Settings"
    };

    string query;
    int selected = 0;

    while (true) {
        clearScreen();
        cout << "Search: " << query << "\n\n";

        // Filter opsi
        vector<string> filtered;
        for (const auto& opt : options) {
            if (fuzzyMatch(query, opt)) {
                filtered.push_back(opt);
            }
        }

        if (filtered.empty()) {
            cout << "No match found.\n";
        } else {
            for (int i = 0; i < filtered.size(); ++i) {
                if (i == selected)
                    cout << "> " << filtered[i] << "\n";
                else
                    cout << "  " << filtered[i] << "\n";
            }
        }

        char ch = _getch();

        if (ch == 13 && !filtered.empty()) { // ENTER
            clearScreen();
            cout << "You selected: " << filtered[selected] << endl;
            break;
        } else if (ch == 8 && !query.empty()) { // BACKSPACE
            query.pop_back();
            selected = 0;
        } else if (ch == 72 && selected > 0) { // UP arrow
            selected--;
        } else if (ch == 80 && selected < filtered.size() - 1) { // DOWN arrow
            selected++;
        } else if (isprint(ch)) {
            query += ch;
            selected = 0;
        }
    }

    return 0;
}
