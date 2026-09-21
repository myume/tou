#pragma once

#include <atomic>
#include <cstddef>
#include <cstdlib>
#include <cwchar>
#include <optional>

namespace tou::util {

template <typename T>
class Deque {
  private:
    std::atomic<size_t> top = 0;
    std::atomic<size_t> bottom = 0;
    std::atomic<size_t> cap;
    T *data;

    void grow() {
        auto newCapacity = cap * 2;
        auto newArr = static_cast<T *>(malloc(sizeof(T) * newCapacity));
        for (auto i = top.load(); i < bottom; i++) {
            newArr[i % newCapacity] = data[i % cap];
        }
        free(data);
        data = newArr;
        cap = newCapacity;
    }

  public:
    explicit Deque(size_t initialSize)
        : data(static_cast<T *>(malloc(sizeof(T) * initialSize))),
          cap(initialSize) {};

    ~Deque() { free(data); }

    void pushBottom(T element) {
        if (bottom - top == cap)
            grow();

        data[bottom++ % cap] = element;
    };

    std::optional<T> popBottom() {
        if (empty())
            return std::nullopt;

        return data[--bottom % cap];
    };

    std::optional<T> steal() {
        if (empty())
            return std::nullopt;
    };

    bool empty() { return top == bottom; }

    size_t capacity() { return cap; }
    size_t size() { return top - bottom; }
};

} // namespace tou::util
