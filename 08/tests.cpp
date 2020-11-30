#include "pthread.cpp"
#include "profiler.h"
#include <numeric>
#include <iostream>
#include <unistd.h>

int add(const std::vector<int>& v, size_t begin, size_t end) {
    int result = 0;
    for (size_t i = begin; i < end; ++i) {
        result += v[i];
    }
    return result;
};

void heavy_func() {
    sleep(1);
}

void test_thread_pool() {
    vector<int> v(10000000, 1);
    int sum_threads = 0;
    int sum = 0;
    {
        size_t threads = 4;
        ThreadPool pool(threads);
        
        vector<future<int>> futures;
        LOG_DURATION("multiple threads addition")
        size_t shift = 0;
        for (size_t shift = 0; shift != v.size(); shift += v.size() / threads) {
            futures.push_back(pool.exec(add, v, shift, shift + v.size() / threads));
        }
        for (auto& f : futures) {
            sum_threads += f.get();
        }
    }

    {
        LOG_DURATION("single thread addition")
        sum = add(v, 0, v.size());
    }

    ASSERT_EQUAL(sum_threads, sum)

    {
        size_t threads = 4;
        ThreadPool pool(threads);
        vector<future<void>> futures;
        LOG_DURATION("multiple threads haevy func")
        size_t shift = 0;
        for (size_t i = 0; i < 4; ++i) {
            futures.push_back(pool.exec(heavy_func));
        }

        for(auto& f : futures) {
            f.get();
        }
    }

    {
        LOG_DURATION("single thread heavy func");
        for (size_t i = 0; i < 4; ++i) {
            heavy_func();
        }
    }
}