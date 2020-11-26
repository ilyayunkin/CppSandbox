#include <iostream>
#include <vector>
using namespace std;

int main()
{
    try {
        vector<int> v;
        v.front();
    } catch (...) {
        cout << "Exception!" << endl;
    }
    cout << "Finish!" << endl;
    return 0;
}
