#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<string, int> buah;
    int N, q;
    string cmd, key;
    cin >> N;
    while (N--) {
        cin >> cmd >> key >> q;
        auto it = buah.find(key);
        if (cmd == "ADD") {
            if(it == buah.end()) buah.insert({key, q});
            else it->second += q;
        } else if (cmd == "SELL") {
            if(it == buah.end()) cout << "item not found\n";
            else if(it->second < q) cout << "not enough stock\n";
            else {
                it->second -= q;
                cout << "SUCCESS\n";
            }
        }
    }
}