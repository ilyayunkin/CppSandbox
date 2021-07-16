#include <QCoreApplication>
#include <QDebug>

#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>

// ВНИМАНИЕ. Используется enable_if_c, WITH _c на конце
// Универсальная реализация
template <class T, class Enable = void>
class data_processor {
public:
    double process(T v1, T v2, T v3){
        qDebug() << "Common version" << v1 << v2 << v3;
        return 0.;
    }
};

// Оптимизированная версия для интегральных типов
template <class T>
class data_processor<
        T,
        typename boost::enable_if_c<boost::is_integral<T>::value
        >::type
        >
{
public:
    double process(T v1, T v2, T v3){
        qDebug() << "Integral version" << v1 << v2 << v3;
        return v1 + v2 + v3;
    }
};
// Оптимизированная SSE-версия для типов с плавающей точкой
template <class T>
class data_processor<
        T,
        typename boost::enable_if_c<boost::is_float<T>::value >::type
        >
{
public:
    double process(T v1, T v2, T v3){
        qDebug() << "Float version" << v1 << v2 << v3;
        return v1 + v2 + v3;
    }
};

template <class T>
double example_func(T v1, T v2, T v3) {
    data_processor<T> proc;
    return proc.process(v1, v2, v3);
}

int main () {
    // Будет вызвана оптимизированная версия для интегральных типов.
    example_func(1, 2, 3);
    short s = 0;
    example_func(s, s, s);
    // Будет вызвана версия для действительных типов
    example_func(1.0, 2.0, 3.0);
    example_func(1.0f, 2.0f, 3.0f);
    // Будет вызвана универсальная версия
    example_func("Hello", "word", "processing");
}
