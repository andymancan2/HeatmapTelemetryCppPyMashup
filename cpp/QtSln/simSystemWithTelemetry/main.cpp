#include <iostream>
#include <thread>
#include <atomic>
#include <list>
#include "utillib.h"
#include "rwshm.h"
using namespace std;


//! \var Constant for thread delay.
const uint32_t kThreadDelay = 10;

//! \var Ready flag to synchronize all threads to start.
atomic_flag ready {};

//! \var Complete flag to synchronize all threads complete.
atomic_flag complete {};

//! \var The object for writing shared memory.
writer w;

//! The thread function to do some simulated work.
//! \param id - Unique for each thread to index shared memory.
void tWork( uint32_t id )
{
    uint32_t value = (0x01 << id);

    uint32_t *startPtr = w.getMapPtr()
                         + (id * telemetry::kNumEntriesPerThread);
    uint32_t *ptr = startPtr;//NULL;
    uint32_t frameCtr = 0;
    uint32_t entryCtr = 0;

    while ( !ready._M_i ) {
        std::this_thread::yield();
    }
    while ( frameCtr < telemetry::kMaxFrames ) {
        *ptr++ = value;
        if ((0x10000000 & value) == 0x10000000) {
            value = (0x01 << id);
        } else {
            value = (value << 1) | 0x01;
        }
        if (++entryCtr == telemetry::kNumEntriesPerThread) {
            startPtr += (telemetry::kNumEntriesPerFrame * telemetry::kNumEntriesPerThread);
            ptr = startPtr;
        } else {
            ptr += telemetry::kNumEntriesPerFrame;
        }

        sleepms( kThreadDelay );
        ++frameCtr;
    }
}

//! Simulate a system by spawning threads and setting bits in shared memory.
void simSystem( void )
{
    cout << "Hello World!" << endl;
    uint32_t tIdx {};
    list<std::thread> tList {};

    ready.clear();
    complete.clear();

    tList.clear();
    for (tIdx = 0; tIdx < telemetry::kNumThreads; ++tIdx) {
        tList.emplace_back( tWork, tIdx );
    }
    sleepms( 100 ); // Give the threads time to spawn.
    cout << "Go!\n";
    ready.test_and_set();
    for (uint32_t i=0; i < telemetry::kMaxFrames; ++i)
    {
        // Allow for threads to run and fill a frame.
        sleepms( kThreadDelay );
    }
    complete.test_and_set();
    for (auto& t: tList)
    {
        t.join();
    }
}

//! Main the entry point for starting the program.
int main()
{
    cout << "simSystemWithTelemetry Hello World!" << endl;
    simSystem();
    return 0;
}
