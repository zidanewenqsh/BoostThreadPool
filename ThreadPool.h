#ifndef __THRDPOOL_H__
#define __THRDPOOL_H__
// #include <iostream>
// #ifdef __cplusplus
// extern "C" {
// #endif

#if defined(_WIN32) || defined(_WIN64)
    // Windows 平台
    #ifdef THREADPOOL_EXPORTS
        #define THREADPOOL_API __declspec(dllexport)
    #else
        #define THREADPOOL_API __declspec(dllimport)
    #endif
#else
    // 非 Windows 平台（如 Linux）
    #if __GNUC__ >= 4
        #define THREADPOOL_API __attribute__ ((visibility ("default")))
    #else
        #define THREADPOOL_API
    #endif
#endif

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

class THREADPOOL_API ThreadPool {
public:
    ThreadPool(size_t threadCount);
    ~ThreadPool();
    template<class F>
    void enqueue(F f);

private:
    boost::asio::io_service ioService_;
    boost::asio::io_service::work work_;
    boost::thread_group threads_;
};

template<class F>
void ThreadPool::enqueue(F f) {
    ioService_.post(f);
}
#endif