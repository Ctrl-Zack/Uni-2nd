#include <iostream>
#include <set>

int main() {
    int n, m, tmp;
    std::cin >> n >> m;
    
    std::multiset<int> price;

    for(int i = 0; i < n; i++) {
        std::cin >> tmp; 
        price.insert(tmp);
    }

    for(int i = 0; i < m; i++) {
        std::cin >> tmp;
        std::multiset<int>::iterator it = price.upper_bound(tmp);
        if(it == price.begin()) std::cout << "-1\n";
        else {
            it--;
            std::cout << (*it) << "\n";
            price.erase(it);
        }
    }
    
    return 0;
}