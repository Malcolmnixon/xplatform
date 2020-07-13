#include <mutex>
#include "os/mutex.hpp"

using namespace xpf;

mutex::mutex(const char*) noexcept
{
	native_handle_ = new std::mutex();
}

mutex::~mutex()
{
	delete static_cast<std::mutex*>(native_handle_);
}

void mutex::lock() noexcept
{
	static_cast<std::mutex*>(native_handle_)->lock();
}

void mutex::unlock() noexcept
{
	static_cast<std::mutex*>(native_handle_)->unlock();
}
