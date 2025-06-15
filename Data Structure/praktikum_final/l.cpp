#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define MOD 1000000007

long long Hamiltonian_path(vector<vector<long long>>& adj, long long N) {
    long long dp[1 << N][N + 1];
    memset(dp, 0, sizeof(dp));
    dp[1][1] = 1;

    for (long long i = 1; i < (1 << N); i++){
        for (long long j = 1; j <= N; j++){
            if (!(i & (1 << (j - 1))) || dp[i][j] == 0) continue;
            for (long long k: adj[j]){
                if (i & (1 << (k - 1))) continue;
                dp[i | (1 << (k - 1))][k] = (dp[i | (1 << (k - 1))][k] + dp[i][j]) % MOD;
            }
        }
    }
    return dp[(1 << N) - 1][N];
}

int main() {
    long long N, M;
    cin >> N >> M;
    vector<vector<long long>> adj(N+1);
    
    for (long long i = 0; i < M; i++) {
        long long a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    cout << Hamiltonian_path(adj, N);

    return 0;
}