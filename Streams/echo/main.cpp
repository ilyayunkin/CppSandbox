#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
    cout << "This is echo:" << endl;
    std::copy(std::istream_iterator<char>(cin), std::istream_iterator<char>(),
              std::ostream_iterator<char>(cout));

    return 0;
}
