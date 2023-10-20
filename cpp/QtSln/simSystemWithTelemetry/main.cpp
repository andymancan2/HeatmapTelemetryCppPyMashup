//! @file main.cpp
//! @author Andrew Louder
//! @mainpage The main() for the simSystemWithTelemetry executable.
//! @section intro_sec Introduction
//! Simulates a system with telemerty.
//! Telemetry is raw data that we want to visualize to better understand its
//! meaning. Samples are taken at a periodic rate to animate and thus observe
//! changes.
//! The "simSystemWithTelemetry" is an imaginary system with telemetry data.
//! There are 8 threads with 8 entryies per thread, thus 64 32-bit
//! entries per sample(frame).
//! There are a total of 64 samples(frames) taken.
//! To generate a color we count the #'s of 1's(bits) in a 32-bit entry,
//! thus color will increase over time as the 1's are increased.


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

//! main() Simulates a system with telemerty.
//! \param argc The argument count.
//! \param argv A list of argume
int main( int argc, char *argv[] )
{
    cout << "simSystemWithTelemetry Hello World!" << endl;
    simSystem();
    return 0;
}
