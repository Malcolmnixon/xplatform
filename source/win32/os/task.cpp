#include <windows.h>
#include <process.h>
#include "os/task.hpp"

using namespace xpf;

/// @brief Thread entry procedure for tasks
/// @param arg                          Thread argument
static unsigned __stdcall task_entry(void* arg)
{
    // Get the function
    const auto* const f = static_cast<std::function<void()>*>(arg);

    // Call the function
    (*f)();

    // Delete the function
    delete f;

    // Return success
    return 0;
}

/// @brief Convert an xplatform priority to a win32 priority
/// @param priority                     Generic priority [0..255]
/// @return                             Win32 priority
static int win32_priority(int priority)
{
    // Linearly spread priorities [0..255] into the 7 standard windows priorities
    if (priority < 37) return THREAD_PRIORITY_IDLE;
    if (priority < 73) return THREAD_PRIORITY_LOWEST;
    if (priority < 110) return THREAD_PRIORITY_BELOW_NORMAL;
    if (priority < 146) return THREAD_PRIORITY_NORMAL;
    if (priority < 183) return THREAD_PRIORITY_ABOVE_NORMAL;
    if (priority < 219) return THREAD_PRIORITY_HIGHEST;
    return THREAD_PRIORITY_TIME_CRITICAL;
}

task::~task()
{
	if (native_handle_)
		CloseHandle(native_handle_);
}

bool task::start(
    const char*,
    const unsigned int,
    const int priority,
    std::function<void()>&& f) noexcept
{
    // Fail if already started
    if (native_handle_)
        return false;

    // Fail if invalid priority
    if (priority < 0 || priority > 255)
        return false;

    // Calculate the win32 priority
    const auto wp = win32_priority(priority);

    // Create function as argument on heap
    auto * const arg = new std::function<void()>(std::move(f));

    // Launch the thread suspended
    auto const handle = _beginthreadex(nullptr, 0, task_entry, arg, CREATE_SUSPENDED, nullptr);
    if (!handle)
    {
        delete arg;
        return false;
    }

    // Save the handle
    native_handle_ = reinterpret_cast<void*>(handle);

    // Set the thread priority
    SetThreadPriority(native_handle_, wp);

    // Resume the thread
    ResumeThread(native_handle_);

    // Return success
    return true;
}
