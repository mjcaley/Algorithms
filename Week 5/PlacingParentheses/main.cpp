#include <algorithm>
#include <iostream>
#include <cassert>
#include <limits>
#include <string>
#include <utility>
#include <vector>

using std::vector;
using std::string;
using std::max;
using std::min;
using std::pair;


using answers = vector< vector<long long> >;


answers populate(vector<long long>& digits)
{
    answers data(digits.size(), vector<long long>(digits.size()) );
    
    for (int i { 0 }; i < digits.size(); ++i)
    {
        data[i][i] = digits[i];
    }
    
    return data;
}





long long eval(long long a, long long b, char op) {
    if (op == '*') {
        return a * b;
    } else if (op == '+') {
        return a + b;
    } else if (op == '-') {
        return a - b;
    } else {
        assert(0);
    }
}

pair<long long, long long> min_and_max(int i, int j, answers& m, answers& M, vector<char>& op)
{
    using std::max;
    using std::min;
    
    long long minimum = std::numeric_limits<long long>::max();
    long long maximum = std::numeric_limits<long long>::min();
    
    for (int k { i }; k < j; ++k)
    {
        long long a = eval(M[i][k], M[k+1][j], op[k]);
        //std::cout << "max/max " << M[i][j] << ' ' << op[j] << ' ' << M[j+1][j] << '=' << a << std::endl;
        
        long long b = eval(M[i][k], m[k+1][j], op[k]);
        //std::cout << "max/min " << M[i][j] << ' ' << op[j] << ' ' << m[j+1][j] << '=' << a << std::endl;
        
        long long c = eval(m[i][k], M[k+1][j], op[k]);
        //std::cout << "min/max " << m[i][j] << ' ' << op[j] << ' ' << M[j+1][j] << '=' << a << std::endl;
        
        long long d = eval(m[i][k], m[k+1][j], op[k]);
        //std::cout << "min/min " << m[i][j] << ' ' << op[j] << ' ' << m[j+1][j] << '=' << a << std::endl;
        
        vector<long long> min_range { minimum, a, b, c, d };
        minimum = *std::min_element(min_range.begin(), min_range.end());
        vector<long long> max_range { maximum, a, b, c, d };
        maximum = *std::max_element(max_range.begin(), max_range.end());
    }
    
    return { minimum, maximum };
}

long long get_maximum_value(const string& exp)
{
    vector<long long> digits;
    vector<char> operations;
    
    for (int d { 0 }; d < exp.length(); d += 2)
    {
        string s = &exp[d];
        digits.emplace_back( std::stoll(s) );
    }
    
    for (int o { 1 }; o < exp.length(); o += 2)
    {
        operations.emplace_back( exp[o] );
    }
    
    
    answers maximum = populate(digits);
    answers minimum = populate(digits);
    
    
    for (long long s { 1 }; s < digits.size(); ++s)
    {
        for (long long i { 0 }; i < digits.size() - s; ++i)
        {
            auto j = i + s;
            auto result = min_and_max(i, j, minimum, maximum, operations);
            minimum[i][j] = result.first;
            maximum[i][j] = result.second;
            //std::cout << "s " << i << " i " << j << std::endl;
            //std::cout << "min " << result.first << " max " << result.second << std::endl;
        }
    }
    
    return maximum[0][digits.size()-1];
}

int main() {
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}
