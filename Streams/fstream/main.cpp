#include <QCoreApplication>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    const string textData = "This is \n"
                            " \t an example String\n"
                            "\n";
    const string filename = string(".\\") + tmpnam(nullptr);
    cout << "Filename: " << filename << '\n';
    cout << "textData: " << textData << '\n';
    {
        ofstream file;
        file.open(filename);
        assert(!file.fail());
        assert(file.is_open());
        file.write(textData.c_str(), textData.length());
        file.close();
    }
    string input;
    {
        ifstream file;
        vector<char> buf(1024, '\0');
        file.open(filename);
        assert(!file.fail());
        assert(file.is_open());
        int i = 0;
        while(file.getline(buf.data(), buf.size())){
            if(i > 0)
                input+= '\n';
            input+= buf.data();
            cout << "buf: " << buf.data() << '\n';
            ++i;
        }
        file.close();
    }

    cout << "input: " << input << '\n';
    remove(filename.c_str());
    assert(input == textData);

    return a.exec();
}
