#pragma once

#include "deque.h"
#include <cstdint>
#include <thread>
#include <vector>

namespace tou {

class Task {};

class Scheduler {
  private:
    std::vector<util::Deque<Task>> deques;
    std::vector<std::thread> workers;

    void processTasks(uint32_t id);

  public:
    // Spawn a scheduler with the specified number of workers
    // defaults to the number of cores - 1 (leave a core for the main thread)
    Scheduler(uint32_t workers = std::thread::hardware_concurrency() - 1);

    // Submit a task to be queued for execution on a worker
    void queueTask(Task task);
};
} // namespace tou
