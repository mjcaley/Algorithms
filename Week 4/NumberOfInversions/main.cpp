#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::pair;
using std::vector;


long long naive(vector<int>& a)
{
    long long inversions { 0 };
    
    auto outer = a.begin();
    
    for (; outer != a.end(); ++outer)
    {
        for (auto inner = outer + 1; inner != a.end(); ++inner)
        {
            if (*outer > *inner)
            {
                ++inversions;
            }
        }
    }
    
    return inversions;
}


pair<vector<int>, long long> merge(vector<int>& a, vector<int>& b)
{
    long long inversions { 0 };
    
    vector<int> sorted;
    
    size_t i { 0 };
    size_t j { 0 };
    
    while (i < a.size() && j < b.size())
    {
        auto& left_value = a[i];
        auto& right_value = b[j];
        
        if (left_value <= right_value)
        {
            sorted.emplace_back(left_value);
            ++i;
        }
        else
        {
            sorted.emplace_back(right_value);
            ++j;
            inversions += a.size() - i;
        }
    }
    
    while (i < a.size())
    {
        sorted.emplace_back(a[i]);
        ++i;
    }
    
    while (j < b.size())
    {
        sorted.emplace_back(b[j]);
        ++j;
    }
    
    return { sorted, inversions };
}


pair<vector<int>, long long>  get_number_of_inversions(vector<int> &a, vector<int> &b, size_t left, size_t right) {
    long long number_of_inversions = 0;
    if (right <= left + 1)
    {
        return { { a[left] }, number_of_inversions };
    }
    size_t m = left + (right - left) / 2;
    
    auto l = get_number_of_inversions(a, b, left, m);
    auto r = get_number_of_inversions(a, b, m, right);
    auto s = merge(l.first, r.first);
    number_of_inversions += l.second;
    number_of_inversions += r.second;
    number_of_inversions += s.second;
    
    return { s.first, number_of_inversions };
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); i++) {
        std::cin >> a[i];
    }
    vector<int> b;
    
    auto result = get_number_of_inversions(a, b, 0, a.size());
    std::cout << result.second << std::endl;
}
