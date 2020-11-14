#include <QCoreApplication>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::vector<double> v;
    double value;
    cout << "Input values:";
    while(cin >> value){
        v.push_back(value);
    }
    auto average = accumulate(v.begin(), v.end(), 0.) / v.size();
    cout << "Average value is: " << average;

    return a.exec();
}
