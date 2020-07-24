#include "os/time.hpp"
#include <chrono>

namespace xpf
{
    namespace time
    {
        unsigned long monotonic_ms() noexcept
        {
            // Get now time since epoch
            const auto now = std::chrono::steady_clock::now().time_since_epoch();

            // Convert to milliseconds
            const auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now);
            
            // Cast milliseconds count to unsigned long
            return static_cast<unsigned long>(now_ms.count());
        }
    }
}
