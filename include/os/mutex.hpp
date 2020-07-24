#pragma once

namespace xpf
{
    /// @brief Mutex class
    ///
    /// A mutex is a synchronization primitive used to safely share resources
    /// between multiple tasks.
    class mutex
    {
        /// @brief Native operating system handle
        void* native_handle_;
        
    public:
        /// @brief Constructs the mutex
        /// @param name                 Mutex name
        mutex(const char* name) noexcept;
        
        /// @brief Destroys the mutex
        ~mutex();
        
        /// @brief Locks the mutex
        void lock() noexcept;
        
        /// @brief Unlocks the mutex
        void unlock() noexcept;
        
        // Delete unnecessary compiler-generated functions
        mutex(const mutex&) = delete;
        mutex(mutex&&) = delete;
        mutex& operator=(const mutex&) = delete;
        mutex& operator=(mutex&&) = delete;
    };
}
