#include "MemoryTracker.h"

#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <mutex>
#include <new>

#if defined(_WIN32) || defined(_MSC_VER)
#include <malloc.h>
#endif

namespace
{
    std::atomic<std::size_t> g_totalAllocations{0};
    std::atomic<std::size_t> g_totalFrees{0};
    std::atomic<std::size_t> g_outstandingAllocations{0};

    std::ofstream g_logStream;
    std::mutex g_logMutex;
    std::atomic<bool> g_trackingEnabled{false};

    void recordAllocation()
    {
        g_totalAllocations.fetch_add(1, std::memory_order_relaxed);
        g_outstandingAllocations.fetch_add(1, std::memory_order_relaxed);
    }

    void recordFree()
    {
        g_totalFrees.fetch_add(1, std::memory_order_relaxed);
        auto current = g_outstandingAllocations.load(std::memory_order_relaxed);
        while (current > 0 &&
               !g_outstandingAllocations.compare_exchange_weak(
                   current, current - 1, std::memory_order_relaxed))
        {
        }
    }

    void *allocateRaw(std::size_t size)
    {
        if (void *ptr = std::malloc(size == 0 ? 1 : size))
        {
            recordAllocation();
            return ptr;
        }
        throw std::bad_alloc();
    }

    void *allocateAligned(std::size_t size, std::size_t alignment)
    {
        if (size > std::numeric_limits<std::size_t>::max() - alignment + 1)
        {
            throw std::bad_alloc();
        }

        const std::size_t adjustedSize =
            std::max<std::size_t>(1, (size + alignment - 1) / alignment * alignment);

#if defined(_WIN32) || defined(_MSC_VER)
        void *ptr = _aligned_malloc(adjustedSize, alignment);
#else
        void *ptr = ::aligned_alloc(alignment, adjustedSize);
#endif
        if (ptr)
        {
            recordAllocation();
            return ptr;
        }
        throw std::bad_alloc();
    }

    void deallocateAligned(void *ptr) noexcept
    {
#if defined(_WIN32) || defined(_MSC_VER)
        _aligned_free(ptr);
#else
        std::free(ptr);
#endif
        recordFree();
    }

} // namespace

namespace MemoryTracker
{

    void initialize(const std::string &logFilePath)
    {
        std::lock_guard<std::mutex> lock(g_logMutex);
        if (g_trackingEnabled.load(std::memory_order_acquire))
        {
            return;
        }
        g_logStream.open(logFilePath, std::ios::out | std::ios::trunc);
        if (g_logStream.is_open())
        {
            g_logStream << "rotation,total_allocations,total_frees,outstanding_allocations\n";
            g_trackingEnabled.store(true, std::memory_order_release);
            std::atexit(shutdown);
        }
    }

    void logRotation(std::size_t rotation)
    {
        std::lock_guard<std::mutex> lock(g_logMutex);
        if (!g_trackingEnabled.load(std::memory_order_acquire) ||
            !g_logStream.is_open())
        {
            return;
        }
        g_logStream << rotation << ','
                    << g_totalAllocations.load(std::memory_order_relaxed) << ','
                    << g_totalFrees.load(std::memory_order_relaxed) << ','
                    << g_outstandingAllocations.load(std::memory_order_relaxed) << '\n';
        g_logStream.flush();
    }

    void shutdown()
    {
        std::lock_guard<std::mutex> lock(g_logMutex);
        if (g_logStream.is_open())
        {
            g_logStream.flush();
            g_logStream.close();
        }
        g_trackingEnabled.store(false, std::memory_order_release);
    }

} // namespace MemoryTracker

void *operator new(std::size_t size)
{
    return allocateRaw(size);
}

void *operator new[](std::size_t size)
{
    return allocateRaw(size);
}

void *operator new(std::size_t size, std::align_val_t alignment)
{
    return allocateAligned(size, static_cast<std::size_t>(alignment));
}

void *operator new[](std::size_t size, std::align_val_t alignment)
{
    return allocateAligned(size, static_cast<std::size_t>(alignment));
}

void operator delete(void *ptr) noexcept
{
    if (!ptr)
    {
        return;
    }
    std::free(ptr);
    recordFree();
}

void operator delete[](void *ptr) noexcept
{
    if (!ptr)
    {
        return;
    }
    std::free(ptr);
    recordFree();
}

void operator delete(void *ptr, std::align_val_t) noexcept
{
    if (ptr)
    {
        deallocateAligned(ptr);
    }
}

void operator delete[](void *ptr, std::align_val_t) noexcept
{
    if (ptr)
    {
        deallocateAligned(ptr);
    }
}

void operator delete(void *ptr, std::size_t) noexcept
{
    operator delete(ptr);
}

void operator delete[](void *ptr, std::size_t) noexcept
{
    operator delete[](ptr);
}

void operator delete(void *ptr, std::size_t, std::align_val_t) noexcept
{
    operator delete(ptr, std::align_val_t{});
}

void operator delete[](void *ptr, std::size_t, std::align_val_t) noexcept
{
    operator delete[](ptr, std::align_val_t{});
}

void *operator new(std::size_t size, const std::nothrow_t &) noexcept
{
    try
    {
        return operator new(size);
    }
    catch (...)
    {
        return nullptr;
    }
}

void *operator new[](std::size_t size, const std::nothrow_t &) noexcept
{
    try
    {
        return operator new[](size);
    }
    catch (...)
    {
        return nullptr;
    }
}

void *operator new(std::size_t size, std::align_val_t alignment,
                   const std::nothrow_t &) noexcept
{
    try
    {
        return operator new(size, alignment);
    }
    catch (...)
    {
        return nullptr;
    }
}

void *operator new[](std::size_t size, std::align_val_t alignment,
                     const std::nothrow_t &) noexcept
{
    try
    {
        return operator new[](size, alignment);
    }
    catch (...)
    {
        return nullptr;
    }
}

void operator delete(void *ptr, const std::nothrow_t &) noexcept
{
    operator delete(ptr);
}

void operator delete[](void *ptr, const std::nothrow_t &) noexcept
{
    operator delete[](ptr);
}

void operator delete(void *ptr, std::align_val_t alignment,
                     const std::nothrow_t &) noexcept
{
    operator delete(ptr, alignment);
}

void operator delete[](void *ptr, std::align_val_t alignment,
                       const std::nothrow_t &) noexcept
{
    operator delete[](ptr, alignment);
}
