#include "tou/scheduler.h"
#include <print>
#include <unistd.h>

int main() {
    tou::Scheduler scheduler;
    for (auto i = 0; i < 100; i++) {
        scheduler.queueTask(
            tou::Task([i] { std::println("executing task {}", i); }));
    }
}
