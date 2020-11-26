#include <iostream>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

int main()
{
    vector<char> v1{'1', '2', '3', '4', '5', '6', '7', '8', '9', 'a'};
    vector<char> v2;
    array<char, 8> a1;
    //works with vector
    transform(v1.begin(), v1.end(), back_inserter(v2), [](const auto i){return i + 1;});

    // won't work with array because array doesn't support push_back() operation
    // transform(v1.begin(), v1.end(), back_inserter(a1), [](const auto i){return i + 1;});

    // This
    transform(v1.begin(), v1.end(), a1.begin(), [](const auto i){return i + 1;});

    copy(a1.begin(), a1.end(), ostreambuf_iterator(cout));
    cout << "\nHello World!" << endl;
    return 0;
}
