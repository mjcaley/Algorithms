#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n)
{
    vector<int> summands;
    
    int total { 1 };
    int last_used { 1 };
    summands.emplace_back(last_used);
    
    while(true)
    {
        int next = last_used + 1;
        if ( (total + next) == n )
        {
            // Got the exact number
            summands.emplace_back(next);
            break;
        }
        else if ( (total + next) > n )
        {
            // Got duplicate number
            total -= last_used;
            summands.pop_back();
            summands.emplace_back(n - total);
            break;
        }
        else
        {
            total += next;
            last_used = next;
            summands.emplace_back(next);
        }
    }
    
    return summands;
}

int main()
{
    int n;
    std::cin >> n;
    vector<int> summands = optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) {
        std::cout << summands[i] << ' ';
    }
}
