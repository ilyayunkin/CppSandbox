#include <iostream>
#include <deque>

using namespace std;

int main()
{
    deque<int> d{1,2,3,4,5};
    auto it = d.begin();
    auto it2 = it + 1;
    cout << *it <<" " << *it2 << " " << *(it2 + 1)<< " " << *d.begin() << endl;

    for(int i = 0; i < 1000; ++i){
        d.push_front(111);
        cout << *it <<" " << *it2 << " " << *(it2 + 1)<< " " << *d.begin() << endl;
    }

    for(int i = 0; i < 1000; ++i){
        d.push_back(222);
        cout << *it <<" " << *it2 << " " << *(it2 + 1)<< " " << *d.begin() << endl;
    }

    d.insert(it2, 333);
//    cout << *it <<" " << *it2 << " " << *(it2 + 1) << endl;
//    for(int i = 0; i < 1000; ++i){
//        d.insert(it2, 333);
//    cout << *it <<" " << *it2 << " " << *(it2 + 1)<< " " << *d.begin() << endl;
//    }

//    for(int i = 0; i < 1000; ++i){
//        d.erase(it2);
//    cout << *it <<" " << *it2 << " " << *(it2 + 1)<< " " << *d.begin() << endl;
//    }


    return 0;
}
