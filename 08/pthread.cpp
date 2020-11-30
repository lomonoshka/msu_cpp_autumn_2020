#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <vector>

using namespace std;

class ThreadPool {
   public:

    ThreadPool() = delete;
    ThreadPool& operator=(ThreadPool&) = delete;
    
    explicit ThreadPool(size_t poolSize)
        : is_terminate(false) {
        for (size_t i = 0; i < poolSize; ++i)
            threads.emplace_back([this]() {
                std::function<void()> task;
                while (true) {
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        thread_notifier.wait(lock, [this] { return !task_queue.empty() || is_terminate; });
                        if (is_terminate && task_queue.empty())
                            return;
                        task = std::move(task_queue.front());
                        task_queue.pop();
                    }
                    task();
                }
            });
    }

    ~ThreadPool() {
        is_terminate = true;
        thread_notifier.notify_all();
        for (std::thread &thread : threads)
            thread.join();
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
        using type = decltype(func(args...));
        auto task = std::make_shared<std::packaged_task<type()>>(std::packaged_task<type()>(std::move(std::bind(func, args...))));
        std::future<type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            if (is_terminate)
                throw std::runtime_error("Thread threads has been terminated.");

            task_queue.push([task]() { (*task)(); });
        }
        thread_notifier.notify_one();
        return res;
    }

   private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> task_queue;
    std::mutex queue_mutex;
    std::condition_variable thread_notifier;
    std::atomic<bool> is_terminate;
};
