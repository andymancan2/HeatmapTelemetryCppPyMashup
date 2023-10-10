#ifndef KTELEMETRY_H
#define KTELEMETRY_H

#include <cstdint>
#include <stddef.h>
#include <assert.h>

//! Namespace to encapsulate telemetry constants.
namespace telemetry
{
    //! Number of threads.
    const uint32_t kNumThreads   = 8;

    //! Number of entries per thread.
    const uint32_t kNumEntriesPerThread = 8;

    //! Number of entries per frame.
    const uint32_t kNumEntriesPerFrame = (kNumThreads * kNumEntriesPerThread);

    //! Maximum number of frames.
    const uint32_t kMaxFrames = 64;

    //! The number of entries for the telemetry buffer.
    const uint32_t kNumEntries = (kMaxFrames * kNumEntriesPerFrame);

    //! The total byte size of the telemetry buffer.
    const uint32_t kTotalByteSize = (kNumEntries * sizeof(uint32_t));
}

#endif // KTELEMETRY_H
