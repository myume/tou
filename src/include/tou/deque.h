#pragma once

#include <cstddef>
#include <mutex>
#include <stdexcept>
#include <vector>

namespace tou::util {

template <typename T>
class Deque {
  private:
    std::mutex mutex;
    std::vector<T> data;

  public:
    void enqueue(T element) {
        std::scoped_lock<std::mutex> scope(mutex);
        data.push_back(element);
    };

    T dequeueFront() { return dequeueEnd(); };

    T dequeueEnd() {
        std::scoped_lock<std::mutex> scope(mutex);
        if (data.empty())
            throw std::runtime_error("wtf bro");
        auto el = data.back();
        data.pop_back();
        return el;
    };

    size_t size() { return data.size(); }

    explicit operator bool() const { return !data.empty(); };
};

} // namespace tou::util
