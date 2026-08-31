#include "tou/scheduler.h"
#include <print>

tou::Scheduler::Scheduler(uint32_t workers) {
    for (auto i = 0; i < workers; i++) {
        this->workers.emplace_back(&Scheduler::processTasks, this, i);
    }
};

void tou::Scheduler::processTasks(uint32_t id) {
    auto deque = this->deques[id];

    std::println("thread number {} reporting for duty", id);
};
