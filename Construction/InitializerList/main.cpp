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

vector<vector<A>> f()
{
    cout << __PRETTY_FUNCTION__ << '\n';
    cout << "Here will be copying from the initializer list to vector. "
         << "Copy to the initializer list won't be performed because A() is a temporary object."
         << endl;
    vector<A> v = {A()};
    cout << "Here will be two copy constructor calls of vector<A>: "
         << "One to the initializer list and to the vector"
         << endl;
    return {v};
}

int main()
{
    f();
    cout << "Hello World!" << endl;
    return 0;
}
