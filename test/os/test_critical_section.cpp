#include "os/critical_section.hpp"
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
    
    // Manually enter then leave
    crit.enter();
    crit.leave();
    
    // Manually enter then leave
    crit.enter();
    crit.leave();
}

TEST(CriticalSection, Entry)
{
    // Create critical section
    critical_section crit;
    
    // Scoped entry
    {
        critical_section::entry entry(crit);
    }
    
    // Scoped entry
    {
        critical_section::entry entry(crit);
    }
}
    