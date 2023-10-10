## @package telemetry
# `

## Grouping of constants for telemetry data.
# Kind of similar to a namespace in C++.
class telemetry:
   ## Member for number of threads.
   kNumThreads = 8
   ## Member for number of entries per thread.
   kNumEntriesPerThread = 8
   ## Member for number of entries per frame.
   kNumEntriesPerFrame = int( kNumThreads * kNumEntriesPerThread )
   ## Member for number of frames(samples).
   kMaxFrames = 64
   ## Member for number of entries.
   kNumEntries = int( kMaxFrames * kNumEntriesPerFrame )
   ## Member for total size in bytes.
   kTotalByteSize = int( kNumEntries * 4 )

