//#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::multimap;
using std::pair;
using std::vector;


using Items = multimap<double, pair<int, int>>;

//struct Backpack
//{
//    int capacity { 0 };
//    Items items;
//    
//    std::string print()
//    {
//        cout << "Capacity:" << capacity << ' ';
//        std::string out;
//        for (auto& i : items)
//        {
//            out = "{ Value per Unit:" + std::to_string(i.first) +
//                "{ Weight:" + std::to_string(i.second.first) +
//                "Value:" + std::to_string(i.second.second) + " }" +
//                " }\n";
//        }
//        return out;
//    }
//};
//
//Backpack generate_backpack()
//{
//    double value { 0 };
//    Backpack backpack;
//    backpack.capacity = rand() % 50;
//    int cur_capacity { 0 };
//    while(cur_capacity < backpack.capacity)
//    {
//        int num_items = rand() % 5 + 1;
//        int weight = rand() % backpack.capacity + 1;
//        int value = rand() %
//    }
//    
//    return backpack;
//}


double get_optimal_value(int capacity, const Items& items) {
    double value = 0.0;
    
    auto iter = items.rbegin();
    while (capacity > 0 && iter != items.rend())
    {
        const auto& item = (*iter).second;
        if (item.second > capacity)
        {
            // get fraction of item
            value += static_cast<double>(item.first) / (static_cast<double>(item.second) / capacity);
            capacity = 0;
        }
        else
        {
            // fit in whole item
            value += item.first;
            capacity -= item.second;
        }
        ++iter;
    }
    
    return value;
}

int main() {
    
//    while(true)
//    {
//        auto backpack = generate_backpack();
//        
//        auto main_value = get_optimal_value(backpack.capacity, backpack.items);
//    }
    
    int n;
    int capacity;
    cin >> n >> capacity;
    Items items;
    for (int i = 0; i < n; i++)
    {
        double a, b;
        cin >> a >> b;
        items.emplace( (a / b), make_pair(a, b) );
    }
    
    double optimal_value = get_optimal_value(capacity, items);
    
    cout.precision(10);
    cout << optimal_value << endl;
    return 0;
}
