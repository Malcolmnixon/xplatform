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
        
        /// @brief Mutex lock class
        class lock
        {
            /// @brief Mutex reference
            mutex& mutex_;
            
        public:
            /// @brief Constructs the mutex lock
            /// @param m                Mutex to lock
            lock(mutex& m) noexcept : mutex_(m)
            {
                mutex_.lock();
            }
            
            /// @brief Destroys the mutex lock
            ~lock()
            {
                mutex_.unlock();
            }
            
            // Delete unnecessary compiler-generated functions
            lock(const lock&) = delete;
            lock(lock&&) = delete;
            lock& operator=(const lock&) = delete;
            lock& operator=(lock&&) = delete;
        };
    };
}
