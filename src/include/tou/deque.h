#pragma once

#include <cstddef>
#include <cstdlib>
#include <mutex>
#include <optional>

namespace tou::util {

template <typename T, size_t N>
class Deque {
  private:
    std::mutex mutex;
    size_t top = 0;
    size_t bottom = 0;
    size_t size;
    T *data;

    void grow() {
        size *= 2;
        auto newArr = static_cast<T *>(malloc(sizeof(T) * size));
        for (auto i = top; i < bottom; i++) {
            newArr[i % size] = data[i % size];
        }
        free(data);
        data = newArr;
    }

  public:
    Deque(size_t initialSize = N)
        : data(static_cast<T *>(malloc(sizeof(T) * initialSize))),
          size(initialSize) {};
    ~Deque() { free(data); }

    void pushBottom(T element) {
        std::scoped_lock<std::mutex> scoped(mutex);
        if (top - bottom == size)
            grow();

        data[bottom++ % size] = element;
    };

    std::optional<T> steal() {};

    std::optional<T> popBottom() {
        std::scoped_lock<std::mutex> scoped(mutex);
        if (empty())
            return std::nullopt;

        return data[--bottom % size];
    };

    bool empty() { return top == bottom; }
};

} // namespace tou::util
