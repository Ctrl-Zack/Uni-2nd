#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    long long N, ans = 0;
    cin >> N;
    vector<int> H(N), W(N);
    for (long long i = 0; i < N; i++) cin >> H[i];
    for (long long i = 0; i < N; i++) cin >> W[i];

    vector<long long> pxW(N + 1, 0);
    for (long long i = 0; i < N; i++) {
        pxW[i + 1] = pxW[i] + W[i];
    }

    stack<long long> st;
    for (long long i = 0; i <= N; i++) {
        long long h = (i < N) ? H[i] : 0;
        while (!st.empty() && H[st.top()] > h) {
            long long height = H[st.top()];
            st.pop();
            long long left = st.empty() ? 0 : pxW[st.top() + 1];
            long long right = pxW[i];
            long long width = right - left;
            ans = max(ans, height * width);
        }
        st.push(i);
    }

    cout << ans << endl;
}