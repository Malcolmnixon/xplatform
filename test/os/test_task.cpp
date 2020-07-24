#include "os/task.hpp"
#include "os/time.hpp"
#include "gtest/gtest.h"

using namespace xpf;

TEST(Task, SleepFor)
{
    // Get time before
    const auto before = time::monotonic_ms();
    
    // Sleep for 100ms
    task::sleep_for(100U);
    
    // Get time after
    const auto after = time::monotonic_ms();
    
    // Get time delta
    const auto delta = after - before;
    
    // Check range
    ASSERT_GT(delta, 80U);
    ASSERT_LT(delta, 120U);
}

TEST(Task, NonStart)
{
    task t;
}

TEST(Task, Start)
{
    auto started = false;
    auto finished = false;
    
    // Start task
    task t;
    t.start(
        "Test Task",
        4096U,
        128,
        [&]()
        {
            started = true;
            task::sleep_for(100U);
            finished = true;
        });
        
    // Wait for 200ms for task to finish
    task::sleep_for(200U);
    
    // Assert started and finished
    ASSERT_TRUE(started);
    ASSERT_TRUE(finished);
}
