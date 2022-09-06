#include <iostream>
#include <vector>
#include <future>
#include <queue>

#include <thread>
#include <functional>

class SimpleThreadPool
{
public:
    explicit SimpleThreadPool(std::size_t threadCount) : m_threadCount(threadCount), stop()
    {
        for (int i = 0; i < m_threadCount; i++)
        {
            threads.emplace_back(std::bind(&SimpleThreadPool::WorkOn, this));
        }
    }
    ~SimpleThreadPool()
    {
        for (auto &thread : threads)
        {
            thread.join();
        }
    }

    SimpleThreadPool(const SimpleThreadPool &) = delete;
    SimpleThreadPool &operator=(const SimpleThreadPool &) = delete;

    template <typename Fnc_T>
    auto Post(Fnc_T task) -> std::future<decltype(task())>
    {
        auto packagedTask = std::make_shared<std::packaged_task<decltype(task())()>>(std::move(task));
        std::future<decltype(task())> fut = packagedTask->get_future();
        {
            std::unique_lock lock(mut);
            tasks.emplace([packagedTask]()
                          { (*packagedTask)(); });
        }
        condition.notify_one();
        return fut;
    }
    void WorkOn()
    {
        while (true)
        {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mut);
                condition.wait(lock, [this]()
                               { return stop || !tasks.empty(); });
                if (stop && tasks.empty())
                    return;
                task = std::move(tasks.front());
                tasks.pop();
            }
            {
                std::unique_lock lock(coutMut);
                task();
            }
        }
    }
    void Destroy()
    {
        {
            std::unique_lock<std::mutex> lock(mut);
            stop = true;
        }
        condition.notify_all();
    }

private:
    size_t m_threadCount;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::condition_variable condition;
    std::mutex mut;
    std::mutex coutMut;
    bool stop;
};

int main()
{
    const auto threads = std::thread::hardware_concurrency();
    std::vector<std::future<int>> results;
    int tasks = 10;
    SimpleThreadPool t(threads);

    for (int i = 0; i < tasks; i++)
    {
        auto fut = t.Post([i]
                          { std::cout << "Number in task: " << i << std::endl;
                            return i; });
        results.emplace_back(std::move(fut));
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    t.Destroy();

    std::cout << "Results in the main thread:\n";
    for (int i = 0; i < tasks; i++)
    {
        std::cout << results[i].get() << std::endl;
    }
}