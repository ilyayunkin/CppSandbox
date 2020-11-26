#include <iostream>

struct B {virtual void f() = 0;};
struct D1 : virtual public B {void f()override;};
struct D2 : virtual public B {void f()override;};
struct MD : public D1, public D2{void f()override;};

void D1::f(){std::cout << "d1\n";}
void D2::f(){std::cout << "d2\n";}
void MD::f(){std::cout << "md\n";}

int main()
{
    MD md;
    D1 d1;
    D2 d2;
    B* v[]{&md, &d1, &d2};
    for(auto p : v){
        p->f();
    }
}
