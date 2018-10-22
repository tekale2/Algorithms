// Example program
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <memory>
#include <atomic>
#include <condition_variable>

class Task {
    public:
        virtual void Run() = 0;
};


class ThreadPool {
    public:
        ThreadPool (unsigned int const &thread_count) {
           count = thread_count;
        }
        void init() {
            for(unsigned int i = 0; i<count;i++) {
                threads.emplace_back(std::thread(&ThreadPool::run_tasks, this));
            }
        }
        void run_tasks() {
            //std::lock_guard<std::mutex> locker(task_lock);
            while(!destroy) {
             std::shared_ptr<Task> task;
             {
                std::unique_lock<std::mutex> locker(task_lock);
                while(tasks.empty())
                    cv.wait(locker);
                task = tasks.back();
                tasks.pop_back();
             }
             task->Run();
            }        
        }
        void add_task(std::shared_ptr<Task> const task) {
            std::lock_guard<std::mutex> locker (task_lock);
            tasks.push_back(task);
            cv.notify_one();
        }
        ~ThreadPool() {
            destroy = true;
            for(auto &thread: threads)
                thread.join();
        }
    private:
        std::vector<std::shared_ptr<Task>> tasks;
        std::vector<std::thread> threads;
        std::atomic<bool> destroy {false};
        std::mutex task_lock;
        std::condition_variable cv;
        unsigned int count;
        
};

// synchronize stdout printing
std::mutex printLock;

class P : public Task {
    public:
        P(int i) : val(i) {}
        void Run () {
            std::lock_guard<std::mutex> locker(printLock);
            std::cout<<"I have been execed by the threadpool thread: "<<std::this_thread::get_id();
            std::cout<<" My val: "<<val<<std::endl;
            std::cout<<std::flush;
        }
    private:
        int val;
};


int main()
{
   {
    std::lock_guard<std::mutex> locker(printLock);
    std::cout<<"Main thread ID "<<std::this_thread::get_id()<<std::endl;
    std::cout<<std::flush;
   }
   ThreadPool pool(2);
    pool.init();
    pool.add_task(std::make_shared<P>(1));
    pool.add_task(std::make_shared<P>(2));
    return 0;
}
