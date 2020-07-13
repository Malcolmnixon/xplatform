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
        
        /// @brief Enter the critical section
        void enter() noexcept;
        
        /// @brief Leave the critical section
        void leave() noexcept;
        
        // Delete unnecessary compiler-generated functions
        critical_section(const critical_section&) = delete;
        critical_section(critical_section&&) = delete;
        critical_section& operator=(const critical_section&) = delete;
        critical_section& operator=(critical_section&&) = delete;
        
        /// @brief Critical section entry class
        class entry
        {
            /// @brief Critical section
            critical_section& crit_;
            
        public:
            /// @brief Constructs the critical section entry
            /// @param c                Critical section to enter
            entry(critical_section& c) noexcept : crit_(c)
            {
                crit_.enter();
            }
            
            /// @brief Destroys the critial section entry
            ~entry()
            {
                crit_.leave();
            }
        };
    };
}
