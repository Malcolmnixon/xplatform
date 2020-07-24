#include "os/critical_section.hpp"
#include "os/unique_lock.hpp"
#include "gtest/gtest.h"

using namespace xpf;

TEST(CriticalSection, Create)
{
    // Create critical section
    critical_section crit;
}

TEST(CriticalSection, Manual)
{
    // Create critical section
    critical_section crit;
    
    // Manually lock then unlock
    crit.lock();
    crit.unlock();
    
    // Manually lock then unlock
    crit.lock();
    crit.unlock();
}

TEST(CriticalSection, Entry)
{
    // Create critical section
    critical_section crit;
    
    // Scoped entry
    {
        unique_lock<critical_section> lock(crit);
    }
    
    // Scoped entry
    {
        unique_lock<critical_section> lock(crit);
    }
}
    