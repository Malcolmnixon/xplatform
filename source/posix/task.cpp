#include <pthread.h>
#include <time.h>
#include "os/task.hpp"

using namespace xpf;

/// @brief Thread entry procedure for tasks
/// @param arg                          Thread argument
static void* task_entry(void* arg)
{
    // Get the function
    const auto* const f = static_cast<std::function<void()>*>(arg);

    // Call the function
    (*f)();

    // Delete the function
    delete f;

    // Return success
    return nullptr;
}

task::~task()
{
	if (native_handle_)
    {
        auto* const handle = static_cast<pthread_t*>(native_handle_);
        pthread_join(*handle, nullptr);
        delete handle;
    }
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

    // Construct the thread attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    {
        if (priority < 128)
        {
            // Priorities 0..127 use the default scheduler
            pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
        }
        else
        {
            // Priorities 128..255 use the round-robin scheduler with linearly interpolated priorities
            const auto priority_min = sched_get_priority_min(SCHED_RR);
            const auto priority_max = sched_get_priority_max(SCHED_RR);
            
            sched_param param{};
            param.sched_priority = (priority_min * (255 - priority) + priority_max * (priority - 128)) / 127;
            pthread_attr_setschedpolicy(&attr, SCHED_RR);
            pthread_attr_setschedparam(&attr, &param);
        }
    }
    
    // Create function as argument on heap
    auto * const arg = new std::function<void()>(std::move(f));

    // Create thread
    pthread_t thread;
    if (pthread_create(&thread, &attr, task_entry, arg))
    {
        delete arg;
        return false;
    }

    // Destroy attributes
    pthread_attr_destroy(&attr);

    // Save handle
    native_handle_ = new pthread_t(thread);

    // Return success
    return true;
}
