#pragma once

#include <vector>

namespace tou::util {

template <typename T>
class Deque {
  private:
    std::vector<T> data;

  public:
    Deque();

    void enqueue();
    T dequeueFront();
    T dequeueEnd();
};

} // namespace tou::util
