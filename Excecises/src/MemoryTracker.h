#ifndef MEMORY_TRACKER_H
#define MEMORY_TRACKER_H

#include <cstddef>
#include <string>

namespace MemoryTracker {

/**
 * @brief Initializes memory tracking and opens the CSV log file.
 */
void initialize(const std::string& logFilePath);

/**
 * @brief Logs a snapshot of current allocation counters for the given rotation.
 */
void logRotation(std::size_t rotation);

/**
 * @brief Closes the log file and flushes any buffered data.
 */
void shutdown();

} // namespace MemoryTracker

#endif // MEMORY_TRACKER_H
