#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using std::multiset;
using std::vector;


long long min_dot_product(const multiset<long long>& a, const multiset<long long>& b) {
    long long result { 0 };
    
    auto iter_a = a.begin();
    auto iter_b = b.rbegin();
    while (iter_a != a.end() && iter_b != b.rend())
    {
        result += *iter_a * *iter_b;
        ++iter_a;
        ++iter_b;
    }
    return result;
}

int main() {
    size_t n;
    std::cin >> n;
    multiset<long long> a, b;
    //vector<int> a(n), b(n);
    for (size_t i = 0; i < n; i++) {
        long long input;
        std::cin >> input;
        a.emplace(input);
    }
    for (size_t i = 0; i < n; i++) {
        long long input;
        std::cin >> input;
        b.emplace(input);
    }
    std::cout << min_dot_product(a, b) << std::endl;
}
