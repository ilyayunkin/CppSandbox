#include <QCoreApplication>
#include <iostream>

/// Объявляем типы
struct gramm
{
    using value_type = long double;
    constexpr explicit gramm(value_type value) : value_(value){}
    constexpr value_type value() const{return value_;};

private:
    value_type value_ = 0.;
};
struct killogramm
{
    using value_type = long double;
    constexpr explicit killogramm(value_type value) : value_(value){}
    constexpr value_type value() const{return value_;};

    constexpr operator gramm(){return gramm(value_ * 1000.);};
    constexpr killogramm(gramm g) : value_(g.value() / 1000.){}

private:
    value_type value_ = 0.;
};

/// Объявляем суфиксы единиц измерения.
/// Имя оператора должно начинаться с подчеркивания.
/// Остальные имена зарезервированы стандартной библотекой
constexpr auto operator"" _kg(long double value){return killogramm(value);}
constexpr auto operator"" _kg(unsigned long long value){return killogramm(value);}

constexpr auto operator"" _g(long double value){return gramm(value);}
constexpr auto operator"" _g(unsigned long long value){return gramm(value);}

/// Операторы вывода в поток (для консоли)
std::ostream & operator<<(std::ostream &s, gramm g){s << g.value() << " gramm";}
std::ostream & operator<<(std::ostream &s, killogramm kg){s << kg.value() << " kilogramm";}

int main(int argc, char *argv[])
{
    // Эти преобразования не работают, т.к. конструкторы объявлены explicit -
    // содавать объекты можно только с явным указанием типов, что и делается внутри операторов литералов
    //    killogramm k = 1;
    //    gramm g = 5;

    /// Пробуем создавать переменные
    constexpr killogramm mass1 = 1_kg;
    std::cout << mass1 << "\r\n";

    constexpr auto mass2 = 2_kg;
    std::cout << mass2 << "\r\n";

    constexpr gramm mass3 = 1_g;
    std::cout << mass3 << "\r\n";

    constexpr auto mass4 = 2_g;
    std::cout << mass4 << "\r\n";


    /// пробуем преобразования:
    constexpr gramm massGramm = 1_kg;
    std::cout << massGramm << "\r\n";
    constexpr killogramm massKg = 1_g;
    std::cout << massKg << "\r\n";    

    std::cout.flush();
}
