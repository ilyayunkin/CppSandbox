#include <QCoreApplication>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << 5. << '\n';
    cout << .5 << '\n';
    cout << 5E1 << '\n';
    cout << 5E-1 << '\n';
    cout << 1'000 << "\n"; // C++14 feature

    return a.exec();
}
