#include "os/time.hpp"
#include "os/task.hpp"
#include "gtest/gtest.h"

using namespace xpf;

TEST(Time, Monotonic)
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
