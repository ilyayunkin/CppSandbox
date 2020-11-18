#include <iostream>

using namespace std;
struct A
{
    static int i;
    int v;
    A(){
        ++i;
        cout << __PRETTY_FUNCTION__ << '\n';
    }
    A(int v)
        :v(v){
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
    return A(2);
}

A namedRVO()
{
    cout << __PRETTY_FUNCTION__ << '\n';
    A a(2);
    return a;
}

A getOneOfTwoNamed(bool b)
{
    cout << __PRETTY_FUNCTION__ << '\n';
    A a1(1);
    A a2(2);
    return b ? a1 : a2;
}

A getOneOfTwoUnNamed(bool b)
{
    cout << __PRETTY_FUNCTION__ << '\n';
    return b ? A(2) : A(3);
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
        cout << "\nURVO. Copy ellision is performed:" << '\n';
        A::i = 0;
        A a = unnamedRVO();
        cout << A::i << " special functions called\n";
    }
    {
        cout << "\nNRVO. Copy ellision is performed:" << '\n';
        A::i = 0;
        A a = namedRVO();
        cout << A::i << " special functions called\n";
    }
    {
        cout << "\nReturning one of two named local object. "
                "Copy ellision is NOT performed:" << '\n';
        A::i = 0;
        A a = getOneOfTwoNamed(true);
        cout << A::i << " special functions called\n";
    }
    {
        cout << "\nReturning one of two conditionally constructed objects. "
                "Copy ellision is NOT performed:" << '\n';
        A::i = 0;
        A a = getOneOfTwoUnNamed(true);
        cout << A::i << " special functions called\n";
    }
    {
        cout << "\nReturning a global object. "
                "Copy ellision is NOT possible:" << '\n';
        A::i = 0;
        A a = getGlobal();
        cout << A::i << " special functions called\n";
    }
    {
        cout << "\nPass a named object by value. "
                "Copy ellision is NOT performed:" << '\n';
        A::i = 0;
        A a(2);
        setByValue(a);
        cout << A::i << " special functions called\n";
    }
    {
        cout << "\nPass an unnamed object by value. "
                "Copy ellision is performed:" << '\n';
        A::i = 0;
        setByValue(A());
        cout << A::i << " special functions called\n";
    }
    return 0;
}
