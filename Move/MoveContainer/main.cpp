#include <iostream>
#include <vector>
#include <QVector>

using namespace std;

struct MoveOnly{
    MoveOnly(int)noexcept{};
    MoveOnly(const MoveOnly &) = delete ;
    MoveOnly(MoveOnly &&)noexcept = default;
    MoveOnly& operator=(const MoveOnly &) = delete ;
    MoveOnly& operator=(MoveOnly &&)noexcept = default;
};

int main()
{
    std::vector<MoveOnly> v;
    v.push_back(MoveOnly(1));

//    std::vector<MoveOnly> v1(v); // Won't compile because the objects can't bee deep-copied.

    QVector<MoveOnly> qv;
//    qv.push_back(MoveOnly(1)); // Won't compile: Qt containers don't work with move-only objects.
    cout << "Hello World!" << endl;
    return 0;
}
