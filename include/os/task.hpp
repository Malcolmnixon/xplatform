#pragma once

#include <functional>

namespace xpf
{
    /// @brief Task class
    class task
    {
        /// @brief Native operating system handle
        void* native_handle_ = nullptr;
        
    public:
        /// @brief Default constructor
        task() = default;
        
        /// @brief Destroys the task
        ~task();
        
        /// @brief Starts the task
        /// @param name                 Task name
        /// @param stack                Task stack
        /// @param priority             Task priority [0..255]
        /// @param f                    Task function
        /// @return                     true on success
        bool start(
            const char* name,
            const unsigned int stack,
            const int priority,
            std::function<void()> &&f) noexcept;
            
        /// @brief Put the calling task to sleep
        /// @param milliseconds         Milliseconds to sleep for
        static void sleep_for(unsigned long milliseconds) noexcept;
        
        // Delete unnecessary compiler-generated functions
        task(const task&) = delete;
        task(task&&) = delete;
        task& operator=(const task&) = delete;
        task& operator=(task&&) = delete;
    };
}
