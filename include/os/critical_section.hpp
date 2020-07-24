#pragma once

namespace xpf
{
    /// @brief Critical section class
    ///
    /// A critical-section is a light-weight mutex with certain limitations, 
    /// but usable from all execution contexts. Specifically:
    /// * Cannot be used for complex thread synchronization
    /// * May be implemented as mutex on some platforms
    /// * May be implemented as disabling contex-switching on some platforms
    /// * May be implemented as disabling interrupts on some platforms
    class critical_section
    {
        /// @brief Native operating system handle (if any)
        void *native_handle_;
        
    public:
        /// @brief Constructs the critical section
        critical_section() noexcept;
        
        /// @brief Destroys the critical section
        ~critical_section();
        
        /// @brief Lock the critical section
        void lock() noexcept;
        
        /// @brief Unlock the critical section
        void unlock() noexcept;
        
        // Delete unnecessary compiler-generated functions
        critical_section(const critical_section&) = delete;
        critical_section(critical_section&&) = delete;
        critical_section& operator=(const critical_section&) = delete;
        critical_section& operator=(critical_section&&) = delete;
    };
}
