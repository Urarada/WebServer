#ifndef THREADS
#define THREADS 1

#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <functional>
#include <vector>
#include <queue>
class MyThread;
class ThreadPool{
private:
    std::queue<std::function<void ()>> task_queue;
    std::vector<MyThread*> free_queue, running_queue;

    std::mutex tasknqueue_mutex;
public:
    ThreadPool();
    ThreadPool(int);
    ~ThreadPool();

    const unsigned int size;
    template<class F, class... Args>
    int add_task(F func, Args... args){
        std::lock_guard<std::mutex> lk(tasknqueue_mutex);
        task_queue.push(std::bind(func, args...));
        return 0;
    }
    int start_all();
    int stop_all();
    friend class MyThread;
};

//always scheduled by threads it self
//notification should provided by task
class MyThread{
private:
    ThreadPool& father;
    std::thread my_thread;
    std::function<void ()> my_task;
    bool run_flag;
    std::mutex run_flag_mutex;
    void run();
    int get_task();
public:
    MyThread(ThreadPool&);
    ~MyThread();
    void start();
    void stop();
};

#endif