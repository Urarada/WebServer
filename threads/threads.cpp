#include "./threads.h"
ThreadPool::ThreadPool():size(std::thread::hardware_concurrency()-1){
    std::cerr << size+1 << " concurrent threads are supported" << std::endl;
    {   std::lock_guard<std::mutex> lk(tasknqueue_mutex);
        for (int i = 0; i < size; i++){
            free_queue.push_back(new MyThread(*this));
        };
    }
}
ThreadPool::ThreadPool(int n):size((std::thread::hardware_concurrency()-1<n)?
std::thread::hardware_concurrency()-1:n){
    std::cerr << size+1 << " concurrent threads are supported" << std::endl;
    {   std::lock_guard<std::mutex> lk(tasknqueue_mutex);
        for (int i = 0; i < size; i++){
            free_queue.push_back(new MyThread(*this));
        };
    }
}
ThreadPool::~ThreadPool(){
    stop_all();
    for(;free_queue.size()>0;){
        delete free_queue.back();
        free_queue.pop_back();
    }
    // delete &task_queue, &running_queue, &free_queue;
    std::cerr<< "~ThreadPool ended" << std::endl;
}
int ThreadPool::start_all(){
    while(!free_queue.empty()){
        free_queue.front()->start();
    }
    return 0;
}
int ThreadPool::stop_all(){
    bool has;
    for(;;){
        {
            std::lock_guard<std::mutex> lk(tasknqueue_mutex);
            has = running_queue.empty() ? false : true;
        }
        if(has){
            std::cerr<< "has" << std::endl;
            running_queue.front()->stop();
        }
        else{
            std::cerr<< "not has" << std::endl;
            break;
        }
    }
    return 0;
}
// MyThread::MyThread(ThreadPool& threadpool):father(threadpool),my_task([&]{std::this_thread::sleep_for(std::chrono::milliseconds(900));return;}){
//     run_flag = false;
// }
MyThread::MyThread(ThreadPool& threadpool):father(threadpool){
    run_flag = false;
}
int MyThread::get_task(){
    {
        std::lock_guard<std::mutex> lk(father.tasknqueue_mutex);
        if(!father.task_queue.empty()){
            std::cerr<< "not empty!" << std::endl;
            // delete &my_task;
            my_task = std::move(father.task_queue.front());
            father.task_queue.pop();
        }
        else{
            std::cerr<< "empty!" << std::endl;
            my_task = [&]{std::this_thread::sleep_for(std::chrono::seconds(2));return;};
        }
        return 0;
    }
}
MyThread::~MyThread(){
    stop();
}
void MyThread::start(){
    {
        std::lock_guard<std::mutex> lk_local(run_flag_mutex);
        if(run_flag){
            return;
        }
        run_flag = true;
        std::lock_guard<std::mutex> lk(father.tasknqueue_mutex);
        for (auto itr = father.free_queue.cbegin(); itr != father.free_queue.cend(); itr++){
            if (*itr == this){
                father.free_queue.erase(itr);
                father.running_queue.push_back(this);
                break;
            }
        }
    }
    run();
}
void MyThread::stop(){
    std::cerr<< "begin stop!" << std::endl;
    {
        std::lock_guard<std::mutex> lk_local(run_flag_mutex);
        if(!run_flag){
            return;
        }
        run_flag = false;
    }
    my_thread.join();
    std::cerr<< "joined" << std::endl;
    {
        std::lock_guard<std::mutex> lk(father.tasknqueue_mutex);
        for (auto itr = father.running_queue.cbegin(); itr != father.running_queue.cend(); itr++){
            if (*itr == this){
                father.running_queue.erase(itr);
                father.free_queue.push_back(this);
                break;
            }
        }
    }
    std::cerr<< "stoped" << std::endl;
}
void MyThread::run(){
    std::cerr<< "run" << father.free_queue.size() << father.running_queue.size() << std::endl;
    // get_task();
    // my_task();
    my_thread = std::thread([this]{
        for (;;){
            {
                std::lock_guard<std::mutex> lk_local(run_flag_mutex);
                if(!run_flag){
                    return;
                }
            }
            // if(get_task()){
            //     return;
            // }
            get_task();
            my_task();
        }
    });
}


