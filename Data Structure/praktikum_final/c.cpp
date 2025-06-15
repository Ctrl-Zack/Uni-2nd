#include <iostream>
using namespace std;

int main() {
    int n, k_l = 0, k_r = 0, i = 0;
    cin >> n;
    int kartu[n];
    for (i = 0; i < n; i++)
        cin >> kartu[i];
    
    int m_l[n] = {0}, m_r[n] = {0}, ans[n] = {0};

    for (i = 0; i < n; i++) {
        int j = n - i - 1;
        m_l[i] = k_l, m_r[j] = k_r;
        k_l = max(kartu[i], k_l), k_r = max(kartu[j], k_r);
    }
    
    for (i = 0; i < n; ++i) {
        int energi = min(m_l[i], m_r[i]);
        ans[i] = max(0, energi-kartu[i]);
    }

    int total = 0;
    for (i = 0; i < n; ++i)
        total += ans[i];
    
    cout << total;
    return 0;
}