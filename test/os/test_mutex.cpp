#include "os/mutex.hpp"
#include "os/unique_lock.hpp"
#include "os/task.hpp"
#include "os/time.hpp"
#include "gtest/gtest.h"

using namespace xpf;

TEST(Mutex, Create)
{
    // Create mutex
    mutex m("Test Mutex");
}

TEST(Mutex, Manual)
{
    // Create mutex
    mutex m("Test Mutex");
    
    // Manually lock then unlock
    m.lock();
    m.unlock();
    
    // Manually lock then unlock
    m.lock();
    m.unlock();
}

TEST(Mutex, ScopedLock)
{
    // Create mutex
    mutex m("Test Mutex");
    
    // Manually lock then unlock
    {
        unique_lock<mutex> l(m);
    }
    
    // Manually lock then unlock
    {
        unique_lock<mutex> l(m);
    }
}

TEST(Mutex, TaskControl)
{
    // Create mutex
    mutex m("Test Mutex");
    
    // Manually lock the mutex
    m.lock();
    
    // Launch a task waiting for access to the mutex
    unsigned long duration = 0;
    task t;
    t.start(
        "Test Task",
        4096U,
        128,
        [&]()
        {
            const auto before = time::monotonic_ms();
            unique_lock<mutex> l(m);
            const auto after = time::monotonic_ms();
            duration = after - before;
        });
        
    // Sleep for 100ms then unlock mutex
    task::sleep_for(100U);
    m.unlock();
    
    // Sleep for another 100ms for the task to finish
    task::sleep_for(100U);
    
    // Assert task was blocked
    ASSERT_GT(duration, 80U);
    ASSERT_LT(duration, 120U);
}
