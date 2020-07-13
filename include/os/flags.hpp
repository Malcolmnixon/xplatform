#pragma once

namespace xpf
{
    /// @brief Flags class
    class flags
    {
        /// @brief Native operating system handle
        void* native_handle_;
        
    public:
        /// @brief Construct the flags
        /// @param name                 Flags name
        /// @param initial              Initial flag bits
        flags(const char* name, unsigned int initial = 0) noexcept;
        
        /// @brief Destroys the flags
        ~flags();
        
        /// @brief Sets flag bits
        /// @param bits                 Flag bits to set
        void set(unsigned int bits) noexcept;
        
        /// @brief Clears flag bits
        /// @param bits                 Flag bits to clear
        void clear(unsigned int bits) noexcept;
        
        /// @brief Test for flag bits
        /// @param bits                 Flag bits to test for
        /// @return                     Tested flag bits that are set
        unsigned int test(unsigned int bits) noexcept;
        
        /// @brief Wait for any flag bits
        /// @param bits                 Flag bits to wait for
        /// @param clear                True to clear matching bits on wake
        /// @return                     Flag bits that woke the function
        unsigned int wait(unsigned int bits, bool clear = false) noexcept;
        
        // Delete unnecessary compiler-generated functions
        flags(const flags&) = delete;
        flags(flags&&) = delete;
        flags& operator=(const flags&) = delete;
        flags& operator=(flags&&) = delete;
    };
}
