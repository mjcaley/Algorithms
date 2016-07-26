#include <cmath>
#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

int binary_search(const vector<int> &a, int x) {
    int left = 0, right = static_cast<int>(a.size() - 1);
    
    while ( !(left > right) )
    {
        int midpoint = static_cast<int>(std::floor((left + right) / 2));
        if (a[midpoint] < x)
        {
            left = midpoint + 1;
        }
        else if (a[midpoint] > x)
        {
            right = midpoint - 1;
        }
        else
        {
            return midpoint;
        }
    }
    
    // Element not found
    return -1;
}

int linear_search(const vector<int> &a, int x) {
    for (size_t i = 0; i < a.size(); ++i)
    {
        if (a[i] == x)
        {
            return i;
        }
    }
    return -1;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    int m;
    std::cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }
//    for (int i = 0; i < m; ++i) {
//        //replace with the call to binary_search when implemented
//        std::cout << linear_search(a, b[i]) << ' ';
//    }
//    
//    std::cout << std::endl;
    
    for (int i = 0; i < m; ++i) {
        //replace with the call to binary_search when implemented
        std::cout << binary_search(a, b[i]) << ' ';
    }
}
