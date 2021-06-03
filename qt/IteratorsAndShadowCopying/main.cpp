#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QVector>

#include <algorithm>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    {
        qDebug() <<"";
        QVector<int> s = {1, 2, 3};
        QVector<int> s1 = s;
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
        auto b = s.begin(); // calls detach
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
        *b = 3;
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
    }
    {
        qDebug() <<"";
        QVector<int> s = {1, 2, 3};
        QVector<int> s1 = s;
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
        for(auto &i : s){ // calls detach because for() calls begin() internally
        }
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
    }
    {
        qDebug() <<"";
        QVector<int> s = {1, 2, 3};
        QVector<int> s1 = s;
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
        for(const auto &i : s){ // calls detach, though i is a const ref
        }
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
    }
    {
        qDebug() <<"";
        QVector<int> s = {1, 2, 3};
        QVector<int> s1 = s;
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
        for(auto it = s.begin(); it != s.end(); ++it){ // calls detach
        }
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
    }
    {
        qDebug() <<"\r\nforeach";
        QVector<int> s = {1, 2, 3};
        QVector<int> s1 = s;
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
        foreach(auto &i, s){ // Doesn't call detach because foreach declares const variables
        }
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
    }
    {
        qDebug() <<"\r\nforeach const";
        QVector<int> s = {1, 2, 3};
        QVector<int> s1 = s;
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
        foreach(const auto &i, s){ // Doesn't call detach because foreach declares const variables
        }
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
    }
    {
        qDebug() <<"";
        QVector<int> s = {1, 2, 3};
        QVector<int> s1 = s;
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
        for(auto it = s.cbegin(); it != s.cend(); ++it){ // Doesn't call detach!
        }
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
    }
    {
        qDebug() <<"";
        const QVector<int> s = {1, 2, 3};
        QVector<int> s1 = s;
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
        for(auto it = s.begin(); it != s.end(); ++it){ // Doesn't call detach because s is const!
        }
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
    }
    {
        qDebug() <<"";
        const QVector<int> s = {1, 2, 3};
        QVector<int> s1 = s;
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
        for(auto &i : s){ // Doesn't call detach because s is const!
        }
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
    }
    {
        qDebug() <<"";
        QVector<int> s = {1, 2, 3};
        QVector<int> s1 = std::move(s); // Really moves the data.
        qDebug() << s << s1 << s.isDetached() << s1.isDetached();
    }
    {
        qDebug() <<"";
        QVector<int> s = {1, 2, 3};
        QVector<int> s1 = s;
        QVector<int> s2 = std::move(s1); // Really moves the data.
        qDebug() << s << s1 << s2 << s.isDetached() << s1.isDetached() << s2.isDetached();
    }

    return a.exec();
}
