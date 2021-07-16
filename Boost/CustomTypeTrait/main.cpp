#include <QCoreApplication>
#include <QDebug>

#include <vector>
#include <QVector>
#include <list>

#include <boost/type_traits/integral_constant.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_float.hpp>

#include <algorithm>

/// Создадим Traits для определения, является ли контейнер вектором.
template<typename Container>
struct is_vector : boost::false_type{};

template<typename T>
struct is_vector<std::vector<T>> : boost::true_type{};

template<typename T>
struct is_vector<QVector<T>> : boost::true_type{};

/// НЕ СУЩЕСТВУЕТ частичной специализации функций. Поэтому создаем класс -помощник
// Его базовая реализация.
template<typename T, class Enable = void>
struct MysortHelper{
    // Можно было бы вообще запретить использование для не вектора
//    static_assert (is_vector<T>::value, "Template is availible only for vectors");
void MySort(T &c)
{
    qDebug() << "Common version";
    c.sort();
}
};

// Реализация для вектора.
template<typename T>
// Тип T оставляем шаблонным, аргумент Enable специализируем типом enable_if_c<>
struct MysortHelper<T, typename boost::enable_if_c<is_vector<T>::value >::type>{
void MySort(T &c)
{
    qDebug() << "Vector version";
    std::sort(c.begin(), c.end());
}
};

/// Создаем функцию сортировки через класс-помощник
template<typename T>
void MySort(T &c)
{
    MysortHelper<T> h;
    h.MySort(c);
}

/// Все то же самое, но с CONSTEXPR - короче.
template<typename T>
void ConstexprSort(T &c){
    if constexpr(is_vector<T>::value){
        qDebug() << "Constexpr Vector version";
        std::sort(c.begin(), c.end());
    }else{
        qDebug() << "ConstexprCommon version";
        c.sort();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::vector<int> stdV{1, 2, 3};
    QVector<int> qV{1, 2, 3};
    std::list<int> stdL{1, 2, 3};

    MySort(stdV);
    MySort(qV);
    MySort(stdL);

    ConstexprSort(stdV);
    ConstexprSort(qV);
    ConstexprSort(stdL);

    return a.exec();
}
