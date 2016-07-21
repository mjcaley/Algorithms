#include <iostream>

const int dime   = 10;
const int nickel = 5;
const int penny  = 1;

int get_change(int m) {
    int n { 0 };
    
    while (m > 0)
    {
        if (m >= dime)
        {
            m -= dime;
            ++n;
        }
        else if (m >= nickel)
        {
            m -= nickel;
            ++n;
        }
        else
        {
            m -= penny;
            ++n;
        }
    }
    
    return n;
}

int main() {
    int m;
    std::cin >> m;
    std::cout << get_change(m) << '\n';
}
