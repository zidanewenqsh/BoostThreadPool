#include "ThreadPool.h"
#include <iostream>

int main() {
    ThreadPool pool(4); // 创建一个包含4个线程的线程池

    for (int i = 0; i < 16; ++i) {
        pool.enqueue([i](){
            std::cout << "Task " << i << " is running on thread " << boost::this_thread::get_id() << std::endl;
            boost::this_thread::sleep_for(boost::chrono::milliseconds(1000)); // 模拟任务执行时间
        });
    }

    boost::this_thread::sleep_for(boost::chrono::seconds(1)); // 等待任务完成

    return 0;
}