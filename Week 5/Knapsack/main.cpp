#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;


int dp_weight(int W, vector<int>& w)
{
    std::sort(w.begin(), w.end());
    
    auto number_of_items = w.size();
    vector< vector<int> > table(W+1, vector<int>(number_of_items+1));
    
    for (int item {1}; item <= number_of_items; ++item)
    {
        for (int total_weight {1}; total_weight <= W; ++total_weight)
        {
            table[total_weight][item] = table[total_weight][item - 1];
            
            auto& current_item = w[item-1];
            if (current_item <= total_weight)
            {
                auto new_value = current_item + table[total_weight - current_item][item-1];
                auto old_value = table[total_weight][item-1];
                auto value = std::max(new_value, old_value);
                table[total_weight][item] = value;
            }
        }
    }
    
    return table[W][number_of_items];
}

int main() {
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    
    std::cout << dp_weight(W, w) << std::endl;
}
