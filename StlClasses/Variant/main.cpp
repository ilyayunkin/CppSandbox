#include <QCoreApplication>
#include <QDebug>
#include <variant>

// Структуры команд, которые нам может пригодиться обрабатывать.
struct S1{
    int i;
};

struct S2{
    QString s;
    char c;
};

struct S3{
    float f;
};

// Обработчик, имеющий operator() для каждого типа команд.
struct Visitor{
    void operator()(S1 s){
        qDebug() << __PRETTY_FUNCTION__ << s.i;
    }
    void operator()(S2 s){
        qDebug() << __PRETTY_FUNCTION__ << s.s << s.c;
    }
    void operator()(S3 s){
        qDebug() << __PRETTY_FUNCTION__ << s.f;
    }
};

template<class> inline constexpr bool always_false_v = false;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // Еще один обработчик (альтернативный)
    auto lambdaVisitor = [] (auto &&s){
        using T = std::decay_t<decltype(s)>;
        if constexpr(std::is_same_v<T, S1>){
            qDebug() << __PRETTY_FUNCTION__ << s.i;
        }else if constexpr(std::is_same_v<T, S2>){
            qDebug() << __PRETTY_FUNCTION__ << s.s << s.c;
        }else if constexpr(std::is_same_v<T, S3>){
            qDebug() << __PRETTY_FUNCTION__ << s.f;
        }else{
            static_assert(always_false_v<T>, "non-exhaustive visitor!");
        }
    };

    std::variant<S1, S2, S3> command = S1{1};
    // std::visit вызывает operator() обработчика с нужным типом аргумента,
    // в зависимости от содержимого std::variant
    std::visit(Visitor(), command);
    std::visit(lambdaVisitor, command);

    command = S2{"7543", 'f'};
    std::visit(Visitor(), command);
    std::visit(lambdaVisitor, command);
}
