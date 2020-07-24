#pragma once

namespace xpf
{
    /// @brief Unique lock class
    /// @tparam T                       Type of mutex-like object to lock
    template <typename T>
    class unique_lock
    {
        /// @brief Mutex-like object reference
        T& mutex_;
        
    public:
        /// @brief Constructs the unique lock
        /// @param m                Mutex-like object to lock
        unique_lock(T& m) noexcept : mutex_(m)
        {
            mutex_.lock();
        }
        
        /// @brief Destroys the unique lock
        ~unique_lock()
        {
            mutex_.unlock();
        }
        
        // Delete unnecessary compiler-generated functions
        unique_lock(const unique_lock&) = delete;
        unique_lock(unique_lock&&) = delete;
        unique_lock& operator=(const unique_lock&) = delete;
        unique_lock& operator=(unique_lock&&) = delete;
    };
}
