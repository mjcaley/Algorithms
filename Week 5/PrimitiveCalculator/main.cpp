#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;


vector<int> optimal_sequence(int n) {
    std::vector<int> sequence;
    while (n >= 1) {
        sequence.push_back(n);
        if (n % 3 == 0) {
            n /= 3;
        } else if (n % 2 == 0) {
            n /= 2;
        } else {
            n = n - 1;
        }
    }
    reverse(sequence.begin(), sequence.end());
    return sequence;
}

int fastest(int n, const vector<int>& sequence)
{
    vector<int> paths;
    paths.emplace_back(n - 1);
    if (n % 2 == 0)
    {
        paths.emplace_back(n / 2);
    }
    if (n % 3 == 0)
    {
        paths.emplace_back(n / 3);
    }
    
    auto path_counter = [&](int i)
    {
        //std::cout << n << "'s path counter " << i << ' ';
        int counter { 0 };
        while (i > 1)
        {
            i = sequence[i];
            ++counter;
        }
        //std::cout << counter << std::endl;
        return counter;
    };
    
    auto path_sorter = [&](const int& a, const int& b)
    {
        return path_counter(a) < path_counter(b);
    };
    
    std::sort(paths.begin(), paths.end(), path_sorter);
    //std::cout << n << " picking " << paths[0] << " as best path" << std::endl;
    
    return paths[0];
}

vector<int> dp_sequence(int n)
{
    vector<int> hops(n + 1);
    hops[1] = 1;
    for (int i { 2 }; i <= n; ++i)
    {
        hops[i] = fastest(i, hops);
    }
    
    vector<int> sequence;
    while (n != 1)
    {
        sequence.emplace_back(n);
        n = hops[n];
    }
    sequence.emplace_back(1);
    std::reverse(sequence.begin(), sequence.end());
    
    return sequence;
}


int main() {
    int n;
    std::cin >> n;
    //vector<int> sequence = optimal_sequence(n);
    //std::cout << sequence.size() - 1 << std::endl;
    //for (size_t i = 0; i < sequence.size(); ++i) {
    //    std::cout << sequence[i] << " ";
    //}
    
    //std::cout << std::endl;
    
    auto seq = dp_sequence(n);
    
    std::cout << seq.size() - 1 << std::endl;
    for (auto s : seq)
    {
        std::cout << s << ' ';
    }
}
