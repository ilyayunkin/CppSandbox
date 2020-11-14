#include <QCoreApplication>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    {
        cout << "Input a float. f= ";
        float f;
        cin >> f;
        cout << "You've input " << f << '\n';
    }
    {
        cout << "Input an int. i= ";
        int i;
        cin >> i;
        cout << "You've input " << i << '\n';
    }
    {
        cout << "Input three ints ";
        int i[3];
        cin >> i[0] >> i[1] >> i[2];
        cout << "You've input";
        for(auto const ii : i)
        {
            cout << ' ' << ii;
        }
        cout << '\n';
    }
    {
        string nameSurname;
        cout << "Enter your name and surname: ";
        getline(cin, nameSurname);
        cout << "You've input " << nameSurname << '\n';
        cout << "Length= " << nameSurname.length() << '\n';
    }

    return a.exec();
}
