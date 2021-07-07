#ifndef JSONUTILITIES_H
#define JSONUTILITIES_H

#include <QByteArrayList>

namespace JsonUtilities
{
    QByteArrayList split(const QByteArray data);

    class JsonDefragmentator
    {
    public:
        QByteArrayList process(const QByteArray data);
    private:
        QByteArray tmpObject_;
        int braceCnt_ = 0;
    };
};

#endif // JSONUTILITIES_H
