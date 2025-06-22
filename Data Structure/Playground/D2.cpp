/**
 *    author:  FrenH
 *    created: 31.05.2025 11:27:32
**/

#include <bits/stdc++.h>
using namespace std;

//Shortcut
#define fp(i, l, r)     for(i = l; i < r; i++)
#define ms(x, y)        memset(x, y, sizeof(x))
#define all(x)          x.begin(), x.end()
#define sc              second
#define fr              first
#define el              '\n'

using dd                = double;
using ll                = long long;
using ull               = unsigned long long;
using pii               = pair<int, int>;
using pll               = pair<ll, ll>;

// Global variabel
const int S = 1e5,
minf = INT_MIN, 
pinf = INT_MAX,
mod = 1e9 + 7;

// Fren -> Not, Equal, AND, OR
// ASCII 0 = 48, A = 65, a = 97

vector<vector<int>> adj;
vector<int> par;
vector<bool> vis;

int cyc = -1;
void dfs(int n, int parent = -1) {
    vis[n] = true;
    for(int &ch : adj[n]) {
        if(parent == ch) continue;
        if(!vis[ch]) {
            par[ch] = n;
            dfs(ch, n);
        }
        else if(cyc == -1) {
            cyc = par[ch] = n;
        }
    }
}

void solve() {
    int n, m, a, b, i, j;
    cin >> n;
    adj.resize(n);
    vis.resize(n);
    par.resize(n);

    for(cin >> m; m--;) {
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for(i = 0; i < n; i++) {
        if(vis[i]) continue;
        par[i] = i;
        dfs(i);
        if(cyc != -1) {
            // cout << cyc << endl;
            for(i = 0; i < n; i++)
                vis[i] = false;
            vector<int> ans;
            while(!vis[cyc]) {
                ans.push_back(cyc);
                vis[cyc] = true;
                cyc = par[cyc];
            }
            sort(all(ans));
            cout << "VOCALOID CYCLE PROGRAM (VCP) : CYCLE DETECTED ";
            for(j = 0; j < ans.size(); j++)
                cout << ans[j] << ' ';
            cout << el;
            return;
        }
    }
    cout << "VOCALOID CYCLE PROGRAM (VCP) : NO CYCLE DETECTED" << el;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);
    
    int tc;
    for(cin >> tc; tc--;) {
        cyc = -1;
        solve();
        adj.clear();
        vis.clear();
        par.clear();
    }
    
    return 0;
}