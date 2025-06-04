#include<bits/stdc++.h>
using namespace std;

int main() {
    int win, terbanyak = -1, lose = -1;
    map<int,int> mp;

    int n, x, tmp;
    cin >> n;
    for (size_t i = 1; i <= n; i++) {
        mp.insert(make_pair(i, 0));
    }
    
    cin >> x;
    for (size_t i = 0; i < x; i++) {
        cin >> tmp;
        auto it = mp.find(tmp);
        it->second++;
    }
    if(x % 2 == 0) x /= 2;
    else x = x / 2 + 1;

    for(auto i: mp) {
        // cout << i.first << " " << i.second << "\n";
        if(i.second > terbanyak) {
            terbanyak = i.second;
            win = i.first;
        }
        x -= i.second;
        if(x <= 0 && lose == -1) lose = i.first;
    }

    cout << win << " " << lose;
    if(win != lose) cout << "\nDistrik " << win << " menang";
    else cout << "\nTidak ada yang menang";
}