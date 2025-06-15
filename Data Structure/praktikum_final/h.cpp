#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    int ans = -1;
    string input;
    unordered_map<char, int> a;
    cin >> input;

    for (auto &idx : input) {
        auto it = a.find(idx);
        if(it == a.end()) a.insert({idx, 1});
        else it->second++;
    }
    
    for (size_t i = 0; i < input.length(); i++) {
        if(a.at(input[i]) == 1) {
            ans = i;
            break;
        }
    }
    
    cout << ans;
}