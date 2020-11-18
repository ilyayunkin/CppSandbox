#include <iostream>

using namespace std;
struct A
{
    static int i;
    A(){
        ++i;
        cout << __PRETTY_FUNCTION__ << '\n';
    }
    A(const A &other){
        ++i;
        cout << __PRETTY_FUNCTION__ << '\n';
    }
    A(const A &&other){
        ++i;
        cout << __PRETTY_FUNCTION__ << '\n';
    }
    void operator=(const A &other){
        ++i;
        cout << __PRETTY_FUNCTION__ << '\n';
    }
    void operator=(const A &&other){
        ++i;
        cout << __PRETTY_FUNCTION__ << '\n';
    }
};
int A::i = 0;

A unnamedRVO()
{
    cout << __PRETTY_FUNCTION__ << '\n';
    return A();
}

A namedRVO()
{
    cout << __PRETTY_FUNCTION__ << '\n';
    A a;
    return a;
}

static A globalA;
A getGlobal()
{
    cout << __PRETTY_FUNCTION__ << '\n';
    return globalA;
}

void setByValue(const A a)
{
    cout << __PRETTY_FUNCTION__ << '\n';
}

int main()
{
    cout << "Hello World!" << endl;
    {
        cout << "\nURVO. Copy ellision is allowed:" << '\n';
        A::i = 0;
        A a = unnamedRVO();
        cout << A::i << " special functions called\n";
    }
    {
        cout << "\nNRVO. Copy ellision is allowed:" << '\n';
        A::i = 0;
        A a = namedRVO();
        cout << A::i << " special functions called\n";
    }
    {
        cout << "\nReturning a global object. Copy ellision is NOT allowed:" << '\n';
        A::i = 0;
        A a = getGlobal();
        cout << A::i << " special functions called\n";
    }
    {
        cout << "\nPass a named object by value. Copy ellision is NOT allowed:" << '\n';
        A::i = 0;
        A a;
        setByValue(a);
        cout << A::i << " special functions called\n";
    }
    {
        cout << "\nPass an unnamed object by value. Copy ellision is allowed:" << '\n';
        A::i = 0;
        setByValue(A());
        cout << A::i << " special functions called\n";
    }
    return 0;
}
