#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threadCount) : ioService_(), work_(ioService_) {
    for (size_t i = 0; i < threadCount; ++i) {
        threads_.create_thread(boost::bind(&boost::asio::io_service::run, &ioService_));
    }
}

ThreadPool::~ThreadPool() {
    ioService_.stop();
    threads_.join_all();
}


