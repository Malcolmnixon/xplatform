#include <mutex>
#include "os/critical_section.hpp"

using namespace xpf;

critical_section::critical_section() noexcept
{
	native_handle_ = new std::mutex();
}

critical_section::~critical_section()
{
	delete static_cast<std::mutex*>(native_handle_);
}

void critical_section::lock() noexcept
{
	static_cast<std::mutex*>(native_handle_)->lock();
}

void critical_section::unlock() noexcept
{
	static_cast<std::mutex*>(native_handle_)->unlock();
}
