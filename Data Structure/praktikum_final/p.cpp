#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

int main() {
    unordered_map<char, int> freq;
    priority_queue<int> sch;

    int p, q, ans = 0;
    cin >> p >> q;
    for (int i = 0; i < p; i++) {
        char tmp; cin >> tmp;
        freq[tmp]++;
    }

    for (auto &i : freq)
        sch.push(i.second);
    
    while (!sch.empty()) {
        vector<int> doJob;

        for (int i = 0; i < q + 1; i++)
            if (!sch.empty())
                doJob.push_back(sch.top()), sch.pop();
            else break;

        for (int i = 0; i < doJob.size(); i++) 
            if (--doJob[i] > 0) sch.push(doJob[i]);

        ans += sch.empty() ? doJob.size() : q + 1;
    }

    cout << ans;
}
