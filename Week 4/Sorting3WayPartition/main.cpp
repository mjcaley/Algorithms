#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

using std::pair;
using std::vector;
using std::swap;


pair<int, int> partition3(vector<int>& a, int l, int r)
{
    int j = l;    // lower bound of equal range
    int k = l;    // upper bound of equal range
    
    int comparison = a[l];
    
    for (int i = l+1; i <= r; ++i)
    {
        if (a[i] == comparison)
        {
            swap(a[i], a[k+1]);
            ++k;
        }
        else if (a[i] < comparison)
        {
            swap(a[i], a[j]);
            swap(a[i], a[k+1]);
            ++j;
            ++k;
        }
    }
    
    return { j, k };
}

void randomized_quick_sort3(vector<int>& a, int l, int r)
{
    if (l >= r)
    {
        return;
    }
    
    int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);
    pair<int, int> m = partition3(a, l, r);
    
    randomized_quick_sort3(a, l, m.first-1);
    randomized_quick_sort3(a, m.second+1, r);
}

int partition2(vector<int> &a, int l, int r) {
    int x = a[l];
    int j = l;
    for (int i = l + 1; i <= r; i++) {
        if (a[i] <= x) {
            j++;
            swap(a[i], a[j]);
        }
    }
    swap(a[l], a[j]);
    return j;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
    if (l >= r) {
        return;
    }
    
    int k = l + rand() % (r - l + 1);
    swap(a[l], a[k]);
    int m = partition2(a, l, r);
    
    randomized_quick_sort(a, l, m - 1);
    randomized_quick_sort(a, m + 1, r);
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    
    randomized_quick_sort3(a, 0, a.size() -1);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
}
