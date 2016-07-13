#include <iostream>
#include <vector>


using std::vector;
using std::cin;
using std::cout;


long long MaxPairwiseProductVeryFast(const vector<int>& numbers)
{
    int n = numbers.size();
    int max_index1 { -1 };
    int max_index2 { -1 };
    
    for (int i = 0; i < n; ++i)
    {
        if ((max_index1 == -1) || (numbers[i] >= numbers[max_index1]))
        {
            max_index2 = max_index1;
            max_index1 = i;
        }
        else if ((max_index2 == -1) || (numbers[i] > numbers[max_index2]))
        {
            max_index2 = i;
        }
    }
    
    long long result = static_cast<long long>(numbers[max_index1]) * numbers[max_index2];
    return result;
}

int main(int argc, const char * argv[])
{
    int n;
    cin >> n;
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
    
    long long result = MaxPairwiseProductVeryFast(numbers);
    cout << result << "\n";
    return 0;
}
