#include <iostream>
#include <vector>
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
    {
        cout << __PRETTY_FUNCTION__ << "Copy of a named object" << '\n';
        A a1(1);
        A a2(a1);
    }
    {
        cout << __PRETTY_FUNCTION__ << "Move of a named object" << '\n';
        A a1(1);
        A a2(std::move(a1));
    }
    {
        cout << __PRETTY_FUNCTION__ << "Copy of an unnamed object - copy elision" << '\n';
        A a2(A(1));
    }
    {
        cout << __PRETTY_FUNCTION__ << "Pushback of a named object - copy" << '\n';
        vector<A> v;
        A a1(1);
        v.push_back(a1);
    }
    {
        cout << __PRETTY_FUNCTION__ << "Pushback of an unnamed object - move" << '\n';
        vector<A> v;
        v.push_back(A(1));
    }
    return 0;
}
