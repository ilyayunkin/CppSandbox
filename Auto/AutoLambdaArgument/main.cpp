#include <iostream>

using namespace std;

auto sqrt = [](auto v)
{return v * v;};

int main()
{
    cout << sqrt(2) << endl;
    cout << sqrt(2.2) << endl;
    return 0;
}
