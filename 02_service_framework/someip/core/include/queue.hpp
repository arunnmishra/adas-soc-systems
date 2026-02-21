#pragma once
#include <queue>
#include <mutex>

template<typename T>
class ThreadSafeQueue
{
    std::queue<T> q;
    std::mutex m;

public:
    void push(T&& value)
    {
        std::lock_guard lock(m);
        q.push(std::move(value));
    }

    bool pop(T& out)
    {
        std::lock_guard lock(m);
        if (q.empty()) return false;
        out = std::move(q.front());
        q.pop();
        return true;
    }
};
