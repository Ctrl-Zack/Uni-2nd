#include <iostream>
#include <vector>
using namespace std;

//           l    u    r   d
short x[] = {-1,  0,   1,  0};
short y[] = {0 , -1,   0,  1};

int H, W;
int C = 0, S = 0, E = 0;

int dfs(vector<vector<char>> &grid, vector<vector<bool>> &vis, int xpos, int ypos, int ans = 1) {
    if(ypos < 0 || ypos >= H || xpos < 0 || xpos >= W || grid[ypos][xpos] == '#' || vis[ypos][xpos]) return 0;
    vis[ypos][xpos] = true;
    for(int i = 0; i < 4; i++) {
        int nxpos = xpos + x[i];
        int nypos = ypos + y[i];
        ans += dfs(grid, vis, nxpos, nypos);
    }
    return ans;
}

int main() {
    cin >> H >> W;
    vector<vector<char>> grid;
    vector<vector<bool>> vis;

    grid.resize(H, vector<char>(W));
    vis.resize(H, vector<bool>(W));

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> grid[i][j];
            vis[i][j] = false;
        }
    }
    
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (grid[i][j] == '+' && !vis[i][j]) {
                int tmp = dfs(grid, vis, j, i);
                if(tmp % 2 == 0) E++;
                S = max(S, tmp);
                C++;
            }
        }
    }

    cout << C << ' ' << S << ' ' << E;
}