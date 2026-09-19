#pragma once

#include "deque.h"
#include <atomic>
#include <cstdint>
#include <functional>
#include <thread>
#include <vector>

namespace tou {

class Task {
  private:
    std::function<void()> func;

  public:
    Task(std::function<void()> func) : func(func) {};

    void execute() { func(); }
};

class Scheduler {
  private:
    std::atomic<bool> isRunning = true;

    std::vector<util::Deque<Task, 32>> deques;
    std::vector<std::thread> workers;
    size_t nextWorker = 0;

    void processTasks(uint32_t id);

  public:
    // Spawn a scheduler with the specified number of workers
    // defaults to the number of cores - 1 (leave a core for the main thread)
    Scheduler(uint32_t workers = std::thread::hardware_concurrency() - 1);
    ~Scheduler();

    Scheduler(const Scheduler &) = delete;
    Scheduler &operator=(const Scheduler &) = delete;

    Scheduler(Scheduler &&) = delete;
    Scheduler &operator=(Scheduler &&) = delete;

    // Submit a task to be queued for execution on a worker
    void queueTask(Task task);
};

} // namespace tou
