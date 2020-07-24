#include "os/flags.hpp"
#include "os/task.hpp"
#include "os/time.hpp"
#include "gtest/gtest.h"

using namespace xpf;

TEST(Flags, CreateZero)
{
    flags f("Test Flags");
    
    // Assert no bits set
    ASSERT_EQ(f.test(0xFFFFU), 0x0000U);
}

TEST(Flags, CreateNonZero)
{
    flags f("Test Flags", 0xAA55);
    
    // Assert correct bits set
    ASSERT_EQ(f.test(0xFFFFU), 0xAA55U);
}

TEST(Flags, Set)
{
    flags f("Test Flags");
    
    // Assert no bits set
    ASSERT_EQ(f.test(0xFFFFU), 0x0000U);

    // Set no bits
    f.set(0x0000U);
    
    // Assert no bits set
    ASSERT_EQ(f.test(0xFFFFU), 0x0000U);

    // Set bits
    f.set(0x000FU);
    
    // Assert correct bits set
    ASSERT_EQ(f.test(0xFFFFU), 0x000FU);

    // Set more
    f.set(0x0A0FU);
    
    // Assert correct bits set
    ASSERT_EQ(f.test(0xFFFFU), 0x0A0FU);

    // Set more
    f.set(0x0F00U);
    
    // Assert correct bits set
    ASSERT_EQ(f.test(0xFFFFU), 0x0F0FU);
}

TEST(Flags, Clear)
{
    flags f("Test Flags", 0xFFFFU);
    
    // Assert all bits set
    ASSERT_EQ(f.test(0xFFFFU), 0xFFFFU);

    // Clear no bits
    f.clear(0x0000U);
    
    // Assert all bits set
    ASSERT_EQ(f.test(0xFFFFU), 0xFFFFU);

    // Clear bits
    f.clear(0x000FU);
    
    // Assert correct bits set
    ASSERT_EQ(f.test(0xFFFFU), 0xFFF0U);

    // Clear more bits
    f.clear(0x0A0FU);
    
    // Assert correct bits set
    ASSERT_EQ(f.test(0xFFFFU), 0xF5F0U);

    // Clear more bits
    f.clear(0x0F00U);
    
    // Assert correct bits set
    ASSERT_EQ(f.test(0xFFFFU), 0xF0F0U);
}

TEST(Flags, Test)
{
    flags f("Test Flags", 0xFAF5U);

    // Assert testing across bits
    ASSERT_EQ(f.test(0xFFFFU), 0xFAF5U);
    ASSERT_EQ(f.test(0xF000U), 0xF000U);
    ASSERT_EQ(f.test(0x0F00U), 0x0A00U);
    ASSERT_EQ(f.test(0x00F0U), 0x00F0U);
    ASSERT_EQ(f.test(0x000FU), 0x0005U);
}

TEST(Flags, Wait)
{
    flags f("Test Flags", 0xFF00U);

    // Assert waiting immediate finish without clearing
    ASSERT_EQ(f.wait(0xF000U, false), 0xF000U);
    ASSERT_EQ(f.test(0xFFFFU), 0xFF00U);
    
    // Assert waiting immediate finish with clearing
    ASSERT_EQ(f.wait(0xF000U, true), 0xF000U);
    ASSERT_EQ(f.test(0xFFFFU), 0x0F00U);
    
    // Test waking without clear
    {
        task t;
        t.start(
            "Test Task",
            4096U,
            128,
            [&]()
            {
                task::sleep_for(100U);
                f.set(0x000FU);
            });
            
        // Wait for bits
        const auto before = time::monotonic_ms();
        const auto results = f.wait(0x00FFU, false);
        const auto after = time::monotonic_ms();
        const auto duration = after - before;
        
        // Check range
        ASSERT_EQ(results, 0x000FU);
        ASSERT_EQ(f.test(0x00FFU), 0x000FU);
        ASSERT_GT(duration, 80U);
        ASSERT_LT(duration, 120U);
        
        // Allow task to terminate
        task::sleep_for(100U);
        
        // Clear bits
        f.clear(0x00FFU);
        ASSERT_EQ(f.test(0x00FFU), 0x0000U);
    }
    
    // Test waking with clear
    {
        task t;
        t.start(
            "Test Task",
            4096U,
            128,
            [&]()
            {
                task::sleep_for(100U);
                f.set(0x000FU);
            });
            
        // Wait for bits
        const auto before = time::monotonic_ms();
        const auto results = f.wait(0x00FFU, true);
        const auto after = time::monotonic_ms();
        const auto duration = after - before;
        
        // Check range
        ASSERT_EQ(results, 0x000FU);
        ASSERT_EQ(f.test(0x00FFU), 0x0000U);
        ASSERT_GT(duration, 80U);
        ASSERT_LT(duration, 120U);
        
        // Allow task to terminate
        task::sleep_for(100U);
    }
}
