#include <QCoreApplication>
#include <iostream>

using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << int(5.49) << '\n';
    cout << int(5.51) << '\n';
    cout << int(5.0) << '\n';
    cout << int(5.99) << '\n';

    return a.exec();
}
