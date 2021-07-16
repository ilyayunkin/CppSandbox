#include <QCoreApplication>
#include <QDebug>

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <queue>
#include <cassert>
#include <chrono>

using Task = std::function<void()>;

using TaskQueue = std::queue<Task>;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    TaskQueue tasks;
    std::queue<Task> queue;
    std::mutex mutex;
    std::condition_variable condVar;
    std::atomic<int> finishedThreads{0};

    auto pusher1 = [&]{
        for(int i = 0; i < 10; ++i){
            {
                {
                    std::lock_guard lock(mutex);
                    tasks.push([]{qDebug() << __PRETTY_FUNCTION__ << __LINE__;});
                }
                using namespace std::literals::chrono_literals;
                std::this_thread::sleep_for(1.0ms);
            }
            condVar.notify_one();
        }
        ++finishedThreads;
    };
    auto pusher2 = [&]{
        for(int i = 0; i < 10; ++i){
            {
                {
                    std::lock_guard lock(mutex);
                    tasks.push([]{qDebug() << __PRETTY_FUNCTION__ << __LINE__;});
                }
                using namespace std::literals::chrono_literals;
                std::this_thread::sleep_for(1.0ms);
            }
            condVar.notify_one();
        }
        ++finishedThreads;
    };

    auto popper = [&]{
        forever{
            std::unique_lock lock(mutex);
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

    std::thread t1(pusher1);
    std::thread t2(pusher2);
    std::thread t3(popper);

    t1.join();
    t2.join();

    condVar.notify_all();
    t3.join();

    assert(tasks.empty());

    qDebug() << __PRETTY_FUNCTION__ << __LINE__ << "Finish";
}
