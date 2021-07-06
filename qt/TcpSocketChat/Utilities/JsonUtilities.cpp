#include "JsonUtilities.h"

QByteArrayList JsonUtilities::split(const QByteArray data)
{
    QByteArrayList frames;

    QByteArray tmpf;
    tmpf.reserve(data.size());
    int braceCnt = 0;
    for(const auto c : data){
        switch (c) {
        case '{' : ++braceCnt;
            break;
        case '}' : --braceCnt;
            break;
        }
        tmpf.append(c);

        if(braceCnt == 0 && !tmpf.isEmpty()){
            frames << tmpf;
            tmpf.clear();
        }
    }
    return frames;
}
