#include <iostream>
#include <math.h>
#include <set>
using namespace std;

int main() {
    set<long> G, B; // list gak & beli
    long N, M;
    cin >> N >> M;
    long hari;
    
    B.insert(0); B.insert(N+1);
    for(int i = 1; i <= N; i++) G.insert(i);
    
    for (int i = 0; i < M; i++) {
        cin >> hari;
        if(B.find(hari) == B.end()) { // gak beli
            B.insert(hari);
            G.erase(hari);
        } else {
            G.insert(hari);
            B.erase(hari);
        }
        cout << "Beli: ";
        for (auto &i : B) {
            cout << i << " ";
        } cout << "\nGa: ";

        for (auto &i : G) {
            cout << i << " ";
        } cout << endl;
        
    }

}