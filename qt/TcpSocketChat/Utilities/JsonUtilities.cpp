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

QByteArrayList JsonUtilities::JsonDefragmentator::process(const QByteArray data)
{
    QByteArrayList frames;
    for(const auto c : data){
        switch (c) {
        case '{' : ++braceCnt_;
            break;
        case '}' : --braceCnt_;
            break;
        }
        tmpObject_.append(c);

        if(braceCnt_ == 0 && !tmpObject_.isEmpty()){
            frames << tmpObject_;
            tmpObject_.clear();
        }
    }
    return frames;
}
