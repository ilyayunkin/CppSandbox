#include <QCoreApplication>
#include <iostream>
#include <math.h>

using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout << int(5.49) << '\n';
    cout << int(5.51) << '\n';
    cout << int(5.0) << '\n';
    cout << int(5.99) << '\n';
    cout << "round\n";
    cout << round(5.49) << '\n';
    cout << round(5.51) << '\n';
    cout << round(5.0) << '\n';
    cout << round(5.99) << '\n';
    cout << "ceil\n";
    cout << ceil(5.49) << '\n';
    cout << ceil(5.51) << '\n';
    cout << ceil(5.0) << '\n';
    cout << ceil(5.99) << '\n';
    cout << "floor\n";
    cout << floor(5.49) << '\n';
    cout << floor(5.51) << '\n';
    cout << floor(5.0) << '\n';
    cout << floor(5.99) << '\n';

    return a.exec();
}
