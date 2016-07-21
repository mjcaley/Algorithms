#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


vector<unsigned long long> pisano(unsigned long long m)
{
    unsigned long long a { 0 };
    unsigned long long b { 1 };
    vector<unsigned long long> c { 0, 1, (a + b) % m };
    
    for (unsigned long long i = 1; i <= m*6; ++i)
    {
        a = b;
        b = c.back();
        c.emplace_back((a + b) % m);
        if ( (*(c.end()-2) == 0) && (*(c.end()-1) == 1) )
        {
            c.pop_back();
            c.pop_back();
            break;
        }
    }
    
    return c;
}

int main()
{
    unsigned long long Fn, m;
    cin >> Fn;
    cin >> m;
    
    auto pisano_seq = pisano(m);
    auto remainder = Fn % pisano_seq.size();
    
    cout << pisano_seq[remainder] << endl;
    
    return 0;
}