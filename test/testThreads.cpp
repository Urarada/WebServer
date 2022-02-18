#include "../threads/threads.h"
void print(int i){
    std::cerr << i << std::endl;
}
class A{
private:
    int a;
public:
    A(int i){
        a = i;
    }
    ~A(){
    }
    void print(){
        std::cerr << this->a << 'a' << std::endl;
    }
};

int main(){
    int i, count = 5;
    {
        // std::thread t([](){
        // std::cout << "hello world." << std::endl;});
        // t.join();
        ThreadPool threads;
        int counter = 0;
        for (i = 0; i < count; i++){
            threads.add_task(print, i);
        }
        std::cout << "added1" << std::endl;
        threads.start_all();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "finish1" << std::endl;
        std::vector<A> vec;
        for (i = 0; i < count; i++){
            vec.emplace_back(i);
        }
        for (i = 0; i < count; i++){
            auto f = std::bind(&A::print, &vec[i]);
            threads.add_task(f);
        }
        /*note:if use 
        ```
        for (i = 0; i < count; i++){
            vec.emplace_back(i);
            auto f = std::bind(&A::print, &vec[i]);
            threads.add_task(f);
        }
        ```
        there would be some bugs. It seems vec is deleted when thread2 runs.
        */
        std::cout << "added2" << std::endl;
        threads.start_all();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "finish2" << std::endl;
    }
    return 0;
}