#include <iostream>
#include <chrono>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


long long naive_fib(int number)
{
    if (number <= 1)
    {
        return number;
    }
    else
    {
        return naive_fib(number-1) + naive_fib(number-2);
    }
}

long long new_fib(int number)
{
    vector<long long> list { 0, 1 };
    for (int i = 2; i <= number; ++i)
    {
        list.emplace_back(list[i-2] + list[i-1]);
    }
    
    return list.back();
}

int main()
{
    int input { 0 };
    cin >> input;
    
    auto start = std::chrono::steady_clock::now();
    auto result = naive_fib(input);
    auto end = std::chrono::steady_clock::now();
    cout << result << endl;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << endl;

    auto start2 = std::chrono::steady_clock::now();
    auto result2 = new_fib(input);
    auto end2 = std::chrono::steady_clock::now();
    cout << result2 << endl;
    cout << std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << endl;
    
    return 0;
}