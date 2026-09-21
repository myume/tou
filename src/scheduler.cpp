#include "tou/scheduler.h"
#include "tou/deque.h"
#include <mutex>

tou::Scheduler::Scheduler(uint32_t workersCount) {
    deques.reserve(workersCount);
    for (uint32_t i = 0; i < workersCount; i++)
        deques.emplace_back(std::make_unique<util::Deque<Task>>(32));

    workers.reserve(workersCount);
    for (uint32_t i = 0; i < workersCount; i++)
        workers.emplace_back(&Scheduler::processTasks, this, i);
}

void tou::Scheduler::processTasks(uint32_t id) {
    auto &deque = deques[id];
    while (isRunning) {
        if (deque->empty()) {
            injectTasks(id);
        }

        if (auto task = deque->popBottom())
            task->execute();
    }
};

tou::Scheduler::~Scheduler() {
    isRunning = false;
    for (auto &worker : workers) {
        worker.join();
    }
};

void tou::Scheduler::queueTask(Task &&task) {
    std::scoped_lock<std::mutex> scope(pendingLock);
    pendingWork.push(task);
};

void tou::Scheduler::injectTasks(uint32_t id) {
    std::scoped_lock<std::mutex> scope(pendingLock);
    auto &deque = deques[id];
    auto take = std::min({
        pendingWork.size() / workers.size() + 1,
        deque->capacity() - deque->size(),
        pendingWork.size() / 2,
    });
    for (auto i = take; i > 0; i--) {
        deque->pushBottom(pendingWork.front());
        pendingWork.pop();
    }
};
