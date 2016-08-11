#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;


int edit_distance(const string &str1, const string &str2)
{
    // A[1...j]
    // B[1...j]
    //
    // insertion:
    //      A[1...i]    | -
    //      B[1...j-1]  | B[j]  +1
    //
    // deletion:
    //      A[1...i-1]  | A[i]
    //      B[1...j]    | -     +1
    //
    // mismatch:
    //      A[1...i-1]  | A[i]
    //      B[1...j]    | B[j]  +1
    //
    // match:
    //      A[1...i-1]  | A[i]
    //      B[1...j-1]  | B[j]
    //
    //
    //  D[i, j] = min   { D(i, j-1)+1
    //                  { D(i-1, j)+1
    //                  { D(i-1, j-1)+1     if A[i] != B[j]
    //                  { D(i-1, j-1)       if A[i] == B[j]
    
    vector< vector<int> > table(str1.length()+1, vector<int>(str2.length()+1));
    int n { 0 };
    std::generate(table[0].begin()+1, table[0].end(), [&n] { return ++n; } );
    n = 0;
    std::generate(table.begin()+1, table.end(), [&] { vector<int> a(str2.length()+1); a[0] = ++n; return a; });
    
    for (int i {1}; i <= str1.length(); ++i)
    {
        for (int j {1}; j <= str2.length(); ++j)
        {
            vector<int> range;
            range.emplace_back(table[i][j-1] + 1);
            range.emplace_back(table[i-1][j] + 1);
            if (str1[i-1] != str2[j-1])
            {
                range.emplace_back(table[i-1][j-1] + 1);
            }
            if (str1[i-1] == str2[j-1])
            {
                range.emplace_back(table[i-1][j-1]);
            }
            
            table[i][j] = *std::min_element(range.begin(), range.end());
        }
    }
    
    return table[str1.length()][str2.length()];
}

int main() {
    string str1;
    string str2;
    std::cin >> str1 >> str2;
    std::cout << edit_distance(str1, str2) << std::endl;

    return 0;
}
