#include "MemoryTracker.h"

#include <atomic>
#include <cstdlib>
#include <fstream>
#include <mutex>
#include <new>

namespace {
std::atomic<std::size_t> g_totalAllocations{0};
std::atomic<std::size_t> g_totalFrees{0};
std::atomic<std::size_t> g_outstandingAllocations{0};

std::ofstream g_logStream;
std::mutex g_logMutex;
bool g_trackingEnabled = false;

void incrementOutstanding() {
    g_outstandingAllocations.fetch_add(1, std::memory_order_relaxed);
}

void decrementOutstanding() {
    auto current = g_outstandingAllocations.load(std::memory_order_relaxed);
    while (current > 0 &&
           !g_outstandingAllocations.compare_exchange_weak(current, current - 1, std::memory_order_relaxed)) {
        // retry with updated current value
    }
}
} // namespace

namespace MemoryTracker {

void initialize(const std::string& logFilePath) {
    std::lock_guard<std::mutex> lock(g_logMutex);
    if (g_trackingEnabled) {
        return;
    }
    g_logStream.open(logFilePath, std::ios::out | std::ios::trunc);
    if (g_logStream.is_open()) {
        g_logStream << "rotation,total_allocations,total_frees,outstanding_allocations\n";
        g_trackingEnabled = true;
    }
}

void logRotation(std::size_t rotation) {
    if (!g_trackingEnabled) {
        return;
    }
    std::lock_guard<std::mutex> lock(g_logMutex);
    if (!g_logStream.is_open()) {
        return;
    }
    g_logStream << rotation << ','
                << g_totalAllocations.load(std::memory_order_relaxed) << ','
                << g_totalFrees.load(std::memory_order_relaxed) << ','
                << g_outstandingAllocations.load(std::memory_order_relaxed) << '\n';
    g_logStream.flush();
}

void shutdown() {
    std::lock_guard<std::mutex> lock(g_logMutex);
    if (g_logStream.is_open()) {
        g_logStream.flush();
        g_logStream.close();
    }
    g_trackingEnabled = false;
}

} // namespace MemoryTracker

void* operator new(std::size_t size) {
    if (void* ptr = std::malloc(size)) {
        g_totalAllocations.fetch_add(1, std::memory_order_relaxed);
        incrementOutstanding();
        return ptr;
    }
    throw std::bad_alloc();
}

void* operator new[](std::size_t size) {
    if (void* ptr = std::malloc(size)) {
        g_totalAllocations.fetch_add(1, std::memory_order_relaxed);
        incrementOutstanding();
        return ptr;
    }
    throw std::bad_alloc();
}

void operator delete(void* ptr) noexcept {
    if (!ptr) {
        return;
    }
    std::free(ptr);
    g_totalFrees.fetch_add(1, std::memory_order_relaxed);
    decrementOutstanding();
}

void operator delete[](void* ptr) noexcept {
    if (!ptr) {
        return;
    }
    std::free(ptr);
    g_totalFrees.fetch_add(1, std::memory_order_relaxed);
    decrementOutstanding();
}

void operator delete(void* ptr, std::size_t) noexcept {
    operator delete(ptr);
}

void operator delete[](void* ptr, std::size_t) noexcept {
    operator delete[](ptr);
}
