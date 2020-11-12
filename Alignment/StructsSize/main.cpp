#include <QCoreApplication>
#include <QDebug>

#include <stdint.h>

struct A
{
    uint8_t c1;
    uint16_t ui16;
    uint8_t c2;
    uint64_t ui64;
    uint32_t ui32;
};
struct A1
{
    uint8_t c1;
    uint8_t c11;
    uint16_t ui16;
    uint8_t c2;
    uint64_t ui64;
    uint32_t ui32;
};

struct B
{
    uint16_t ui16;
    uint8_t c1;
    uint8_t c2;
    uint64_t ui64;
    uint32_t ui32;
};

struct B1
{
    uint16_t ui16;
    uint8_t c1;
    uint8_t c2;
    uint64_t ui64;
    uint32_t ui32;
    // By ordering B we got some place for additional data
    uint16_t ui16_1;
    uint8_t c3;
    uint8_t c4;
};

struct C
{
    uint16_t ui16;
    uint8_t c1;
    uint8_t c2;
    uint32_t ui32;
    uint64_t ui64;
};
struct D
{
    A a;
    B b;
};
struct E
{
    A a;
    uint8_t c1;
};

struct F
{
    uint8_t c1;
    A a;
};
struct S1{uint16_t i; char c;};
struct S2{char c; uint16_t i; };
struct G
{
    S1 s1;
    S2 s2;
};

struct H
{
    uint8_t c1;
    uint8_t c2;
    uint8_t c3;
};
struct H2
{
    H h1;
    H h2;
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "A" << sizeof(A);
    qDebug() << "A1" << sizeof(A1);
    qDebug() << "B" << sizeof(B);
    qDebug() << "B1" << sizeof(B1);
    qDebug() << "C" << sizeof(C);
    qDebug() << "D" << sizeof(D);
    qDebug() << "E" << sizeof(E);
    qDebug() << "F" << sizeof(F);
    qDebug() << "G" << sizeof(G);
    qDebug() << "H" << sizeof(H);
    qDebug() << "H2" << sizeof(H2);

    return a.exec();
}
