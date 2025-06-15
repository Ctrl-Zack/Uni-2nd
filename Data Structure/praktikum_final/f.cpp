#include <iostream>
#include <stack>
#include <string.h>
using namespace std;

int main() {
    stack<long> st;
    long tmp1, tmp2, total = 0;
    
    char str[1005];
    scanf("%[^\n]", str);

    char *token;
    char *rest = str;

    while ((token = strtok_r(rest, " ", &rest))) {
        if (!strcmp(token, "+")) {
            tmp1 = st.top(); st.pop();
            tmp2 = st.top();
            st.push(tmp1);
            st.push(tmp1 + tmp2);
        }
        else if (!strcmp(token, "D")) st.push(st.top() * 2);
        else if (!strcmp(token, "C")) st.pop();
        else st.push(strtol(token, NULL, 0));
    }

    while (!st.empty()) {
        total += st.top();
        st.pop();
    }

    cout << total;
    
    return(0);
}