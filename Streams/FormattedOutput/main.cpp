#include <QCoreApplication>
#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    {// Manipulating width
        cout << setw(3) << "#" << setw(8) << "Value\n";
        for(auto i = 0; i < 10; ++i)
        {
            cout << setw(3) << i << setw(8) << 0.02 * i << '\n';
        }
    }

    {// Manipulating width
        cout << fixed << setprecision(2); // Sets floats precision;
        cout << setw(3) << "#" << setw(8) << "Value\n";
        for(auto i = 0; i < 10; ++i)
        {
            cout << setw(3) << i
                 << setw(8) << 0.02 * i << '\n';
        }
    }

    return a.exec();
}
