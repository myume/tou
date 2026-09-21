#include "tou/deque.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <cstdlib>

TEST_CASE("push and pop bottom") {
    auto dq = tou::util::Deque<int>(4);
    auto num = rand();
    dq.pushBottom(num);
    REQUIRE(dq.popBottom() == num);
}

TEST_CASE("push and grow") {
    auto dq = tou::util::Deque<int>(2);
    std::vector<int> vals = {1, 2, 3, 4, 5, 6, 7, 8};
    for (auto val = vals.begin(); val != vals.end(); val++) {
        dq.pushBottom(*val);
    }

    for (auto expected = vals.rbegin(); expected != vals.rend(); expected++) {
        REQUIRE(dq.popBottom() == *expected);
    }
}

TEST_CASE("pop on empty") {
    auto dq = tou::util::Deque<int>(4);
    REQUIRE(dq.popBottom() == std::nullopt);
}
