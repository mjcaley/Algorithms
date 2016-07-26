#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

using std::vector;


//int test_majority(const vector<int> a)
//{
//    //std::unordered_map<int, int> count;
//    vector<int> count(1000000000);
//    for (auto i : a)
//    {
//        count[i] += 1;
//    }
//    
//    int largest { -1 };
//    for (int i { 0 }; i < count.size(); ++i)
//    {
//        if ( count[i] > count[largest])
//        {
//            largest = i;
//        }
//    }
//    
//    if (count[largest] > (a.size()/2))
//    {
//        return largest;
//    }
//    else
//    {
//        return -1;
//    }
//}


vector<int> merge(vector<int>& bottom, vector<int>& top)
{
    vector<int> sorted;
    
    while (!bottom.empty() && !top.empty())
    {
        auto& b = bottom.front();
        auto& t = top.front();
        
        if (b <= t)
        {
            sorted.emplace_back(b);
            bottom.erase(bottom.begin());
        }
        else
        {
            sorted.emplace_back(t);
            top.erase(top.begin());
        }
    }
    
    if (!bottom.empty())
    {
        sorted.insert(sorted.end(), bottom.begin(), bottom.end());
    }
    else if (!top.empty())
    {
        sorted.insert(sorted.end(), top.begin(), top.end());
    }
    
    return sorted;
}

vector<int> sort(const vector<int> &a, int left, int right)
{
    int m = std::floor((static_cast<float>(left) + right) / 2);
    
    if (right - left == 0)
    {
        return { a[left] };
    }
    else
    {
        auto bottom = sort(a, left, m);
        auto top = sort(a, m+1, right);
        auto sorted = merge(bottom, top);
        
        return sorted;
    }
}

int get_majority_element(vector<int> &a, int left, int right) {
    if (left == right) return -1;
    //if (left + 1 == right) return a[left];
    
    --right;
    auto sorted = sort(a, left, right);
    auto midpoint = sorted.size() / 2;
    auto elem_at_midpoint = sorted[midpoint];
    
    int first { 0 };
    while (true)
    {
        if (sorted[first] == elem_at_midpoint)
        {
            break;
        }
        else
        {
            ++first;
        }
    }
    
    int last { static_cast<int>(sorted.size()-1) };
    while (true)
    {
        if (sorted[first] == elem_at_midpoint)
        {
            break;
        }
        else
        {
            --last;
        }
    }
    
    if ( (last - first) > midpoint )
    {
        // more than half are the same value
        return 1;
    }
    else
    {
        return -1;
    }
}

int main() {
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) {
        std::cin >> a[i];
    }
    std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
    //std::cout << "\nSafe " << test_majority(a) << std::endl;
}
