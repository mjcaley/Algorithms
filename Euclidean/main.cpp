#include <iostream>


long long greatest_common_divisor(long long a, long long b)
{
    long long quotient = a / b;
    long long remainder = a - b * quotient;
    if (remainder == 0)
    {
        return b;
    }
    else
    {
        return greatest_common_divisor(b, remainder);
    }
}


int main()
{
    long long a, b;
    std::cin >> a;
    std::cin >> b;
    
    auto r = greatest_common_divisor(a, b);
    
    std::cout << (a * b) / r << std::endl;
    
    return 0;
}
