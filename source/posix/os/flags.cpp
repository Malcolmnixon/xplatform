#include <mutex>
#include <condition_variable>
#include "os/flags.hpp"

using namespace xpf;

/// @brief STL implementation of flags
struct stl_flags
{
	std::mutex mutex;
	std::condition_variable condition;
	unsigned int flags = 0;
};

flags::flags(const char*, unsigned int initial) noexcept
{
	native_handle_ = new stl_flags;
	static_cast<stl_flags*>(native_handle_)->flags = initial;
}

flags::~flags()
{
	delete static_cast<stl_flags*>(native_handle_);
}

void flags::set(unsigned int bits) noexcept
{
	auto* const f = static_cast<stl_flags*>(native_handle_);

	// Set the bits while holding the mutex
	f->mutex.lock();
	f->flags |= bits;
	f->mutex.unlock();

	// Notify all listeners
	f->condition.notify_all();
}

void flags::clear(unsigned int bits) noexcept
{
	auto* const f = static_cast<stl_flags*>(native_handle_);

	// Clear the bits while holding the mutex
	f->mutex.lock();
	f->flags &= ~bits;
	f->mutex.unlock();
}

unsigned int flags::test(unsigned int bits) noexcept
{
	auto* const f = static_cast<stl_flags*>(native_handle_);

	// Test the bits while holding the mutex
	f->mutex.lock();
	const unsigned int ret = f->flags & bits;
	f->mutex.unlock();

	// Return the true bits
	return ret;
}

unsigned int flags::wait(unsigned int bits, bool clear) noexcept
{
	auto* const f = static_cast<stl_flags*>(native_handle_);

	// Construct a unique-lock on the mutex
	std::unique_lock<std::mutex> lock(f->mutex);

	// Wait until some of our bits are set
	f->condition.wait(lock, [&]() { return (f->flags & bits) != 0; });

	// Save the bits that unblocked the wait
	const auto ret = f->flags & bits;

	// If requested, clear the bits
	if (clear)
		f->flags &= ~bits;

	// Return the bits that unblocked the wait
	return ret;
}
