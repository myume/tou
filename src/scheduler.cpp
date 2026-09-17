#include "tou/scheduler.h"

tou::Scheduler::Scheduler(uint32_t workers) : deques(workers) {
    for (auto i = 0; i < workers; i++) {
        this->workers.emplace_back(&Scheduler::processTasks, this, i);
    }
};

void tou::Scheduler::processTasks(uint32_t id) {
    auto &deque = this->deques[id];
    while (isRunning) {
        if (deque) {
            deque.dequeueEnd().execute();
        }
    }
};

tou::Scheduler::~Scheduler() {
    isRunning = false;
    for (auto &worker : workers) {
        worker.join();
    }
};

void tou::Scheduler::queueTask(Task task) {
    this->deques[nextWorker].enqueue(task);

    // round robin style work distribution
    nextWorker = ++nextWorker % workers.size();
};
