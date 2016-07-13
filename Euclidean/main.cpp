#include <iostream>


int euclidean(int a, int b)
{
    int quotient = a / b;
    int remainder = a - b * quotient;
    if (remainder == 0)
    {
        return b;
    }
    else
    {
        return euclidean(b, remainder);
    }
}


int main()
{
    int a, b;
    std::cin >> a;
    std::cin >> b;
    
    auto r = euclidean(a, b);
    
    std::cout << r << std::endl;
    
    return 0;
}
