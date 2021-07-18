#include <QCoreApplication>
#include <QDebug>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/atomic.hpp>
#include <boost/thread/condition_variable.hpp>
#include <functional>
#include <queue>
#include <cassert>
#include <boost/chrono.hpp>

using Task = std::function<void()>;

using TaskQueue = std::queue<Task>;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TaskQueue tasks;
    std::queue<Task> queue;
    boost::mutex mutex;
    boost::condition_variable condVar;
    boost::atomic<int> finishedThreads{0};

    auto pusher1 = [&]{
        for(int i = 0; i < 10; ++i){
            {
                {
                    boost::lock_guard lock(mutex);
                    tasks.push([]{qDebug() << __PRETTY_FUNCTION__ << __LINE__;});
                }
                using namespace std::literals::chrono_literals;
//                std::this_thread::sleep_for(1.0ms);
            }
            condVar.notify_one();
        }
        ++finishedThreads;
    };
    auto pusher2 = [&]{
        for(int i = 0; i < 10; ++i){
            {
                {
                    boost::lock_guard lock(mutex);
                    tasks.push([]{qDebug() << __PRETTY_FUNCTION__ << __LINE__;});
                }
//                using namespace std::literals::chrono_literals;
//                std::this_thread::sleep_for(1.0ms);
                boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
            }
            condVar.notify_one();
        }
        ++finishedThreads;
    };

    auto popper = [&]{
        forever{
            boost::unique_lock lock(mutex);
            while(tasks.empty()){
                if(finishedThreads >= 2){
                    return;
                }
                condVar.wait(lock);
            }
            auto task = tasks.front();
            tasks.pop();

            qDebug() << __PRETTY_FUNCTION__ << __LINE__ << "Execute";
            task();
        }
    };

    boost::thread t1(pusher1);
    boost::thread t2(pusher2);
    boost::thread t3(popper);

    t1.join();
    t2.join();

    condVar.notify_all();
    t3.join();

    assert(tasks.empty());

    qDebug() << __PRETTY_FUNCTION__ << __LINE__ << "Finish";
}
