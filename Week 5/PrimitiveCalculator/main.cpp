#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using std::map;
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



enum class Method2
{
    DIV2,
    DIV3,
    MIN1
};

class Element
{
public:
    Element(int e)
    {
        set_element(e);
    };
    
    int get_element()
    {
        return e;
    }
    
    void set_element(int element)
    {
        e = element;
    }
    
    std::pair<int, int> get_div3()
    {
        return { e / 3, e % 3 };
    }
    
    std::pair<int, int> get_div2()
    {
        return { e / 2, e % 2 };
    }
    
    std::pair<int, int> get_min1()
    {
        return { e - 1, 0 };
    }
    
private:
    int e;
};

vector<int> dynamic_optimal_sequence(int n, map<int, vector<int>>& mem)
{
    std::cout << "recursion number: " << n << std::endl;
    vector<int> sequence;
    
    if (n == 1)
    {
        sequence.emplace_back(1);
        return sequence;
    }
    
    try
    {
        auto& existing = mem.at(n);
        if (!existing.empty())
        {
            return existing;
        }
    }
    catch (std::out_of_range) {}
    
    auto div3 = n / 3;
    auto div3_r = n % 3;
    vector<int> div3_result;
    if (div3 != 0 && div3_r == 0)
    {
        div3_result = dynamic_optimal_sequence(div3, mem);
    }
    
    auto div2 = n / 2;
    auto div2_r = n % 2;
    vector<int> div2_result;
    if (div2 != 0 && div2_r == 0)
    {
        div2_result = dynamic_optimal_sequence(div2, mem);
    }
    
    auto min1 = n - 1;
    vector<int> min1_result;
    if (min1 != 0)
    {
        min1_result = dynamic_optimal_sequence(min1, mem);
    }
    
    auto shortest = [&]()
    {
        vector< vector<int> > shortest_sequence { div3_result, div2_result, min1_result };
        shortest_sequence.erase( std::remove_if(shortest_sequence.begin(), shortest_sequence.end(), [&](const vector<int>& v) { return v.empty(); }), shortest_sequence.end());
        
        std::sort(shortest_sequence.begin(),
                  shortest_sequence.end(),
                  [&](const vector<int>& v1, const vector<int>& v2) { return v1.size() < v2.size(); });
        
        return shortest_sequence.front();
    };
    
    sequence = shortest();
    sequence.emplace_back(n);
    
    // save to mem
    mem[n] = sequence;
    
    return sequence;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> sequence = optimal_sequence(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (size_t i = 0; i < sequence.size(); ++i) {
        std::cout << sequence[i] << " ";
    }
    
    std::cout << std::endl;
    vector<int> seq;
    //{
        map<int, vector<int>> memoization;
        seq = dynamic_optimal_sequence(n, memoization);
    //}
    std::cout << seq.size() - 1 << std::endl;
    for (auto& i : seq)
    {
        std::cout << i << ' ';
    }
}
