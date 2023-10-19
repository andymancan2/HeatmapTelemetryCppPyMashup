//! @file rwshm.cpp
//! Method class details for reading and writing shared memory.
//! \author Andrew Louder
#include <iostream>
#include <iomanip>
#include "rwshm.h"

using namespace std;

wshm::wshm( const char* shmMapFile,
     size_t shmValueSz,
     int shmOpenFlag,
     int shmMapProt,
     mode_t shmOpenMode )
    : mapFile( shmMapFile ),
      valueSz(shmValueSz),
      openFlag(shmOpenFlag),
      mapProt(shmMapProt),
      openMode(shmOpenMode),
      mapDataPtr(NULL)
{
    fd = shm_open(mapFile, openFlag, openMode);
    if (fd < 0) {
        perror("shm_open()");
        exit( EXIT_FAILURE );
    }

    ftruncate(fd, valueSz);

    uint32_t *ptr = mapDataPtr = getMapPtr();

    for (uint32_t i=0; i < telemetry::kNumEntries; i++)
    {
        *ptr++ = 0;
    }
}

uint32_t * wshm::getMapPtr( void )
{
    if (mapDataPtr == NULL)
    {
        mapDataPtr = (uint32_t *)mmap(0, valueSz, mapProt, MAP_SHARED, fd, 0);
    }

    return mapDataPtr;
}

wshm::~wshm()
{
    cout << "wshm destructor called." << endl;
    if (mapDataPtr != NULL)
    {
        munmap(mapDataPtr, valueSz);
    }
    close(fd);
}

writer::writer() : wshm( "telemetry", telemetry::kTotalByteSize )
{

}

writer::~writer()
{
    cout << "writer destructor called" << endl;
}

void writer::initIncPattern( void )
{
    uint32_t *ptr = getMapPtr();

    for (uint32_t i=0; i < telemetry::kNumEntries; i++)
    {
        *ptr++ = i;
    }
}

void writer::initThreadEntry( uint8_t threadId, uint8_t entryIdx, uint32_t value )
{
    uint32_t *ptr = getMapPtr()
                    + (threadId * telemetry::kNumEntriesPerThread)
                    + (entryIdx);

    *ptr++ = value;
}

rshm::rshm( const char* shmMapFile,
     size_t shmValueSz,
     int shmOpenFlag,
     int shmMapProt,
     mode_t shmOpenMode )
    : mapFile( shmMapFile ),
      valueSz(shmValueSz),
      openFlag(shmOpenFlag),
      mapProt(shmMapProt),
      openMode(shmOpenMode)
{
    fd = shm_open(mapFile, openFlag, openMode);
    if (fd < 0) {
        perror("shm_open()");
        exit( EXIT_FAILURE );
    }
    mapDataPtr = NULL;
}

uint32_t * rshm::getMapPtr( void )
{
    if (mapDataPtr == NULL)
    {
        mapDataPtr = (uint32_t *)mmap(0, valueSz, PROT_READ, MAP_SHARED, fd, 0);
    }

    return mapDataPtr;
}

rshm::~rshm()
{
    cout << "rshm destructor called." << endl;
    close(fd);
    if (mapDataPtr != NULL)
    {
        munmap(mapDataPtr, valueSz);
    }
    shm_unlink( mapFile );
}

reader::reader() : rshm( "telemetry", telemetry::kTotalByteSize )
{

}
void reader::gatherTelemetryBitCounts( uint32_t numSamples )
{
    uint32_t *ptr = getMapPtr();
    uint32_t row;
    uint32_t col;
    uint32_t entryValue;
    uint32_t bitIdx;
    uint32_t bitMask;

    assert( numSamples < UINT16_MAX );

    for ( row=0; row < telemetry::kNumThreads; ++row)
    {
        for (col=0; col < telemetry::kNumEntriesPerThread; ++col)
        {
            bitCounts[row][col] = 0;
        }
    }
    for (uint32_t teleSample=0; teleSample < numSamples; ++teleSample)
    {
        row = 0;
        col = 0;
        for (uint32_t entry=0; entry < telemetry::kNumEntriesPerFrame; ++entry)
        {
            assert( row < telemetry::kNumThreads );
            assert( col < telemetry::kNumEntriesPerThread );
            entryValue = *ptr++;
            bitMask = 0x1;
            for (bitIdx=0; bitIdx < 32; bitIdx++)
            {
                if ((entryValue & bitMask) != 0)
                {
                    bitCounts[row][col]++;
                }
                bitMask = (bitMask << 1);
            }
            //cout << "r:" << row << ", c:" << col << ", E:" << entryValue << ", cnt:" << bitCounts[row][col] << endl;
            if (++col >= telemetry::kNumEntriesPerThread)
            {
                col = 0;
                row++;
            }
        }
        //printBitCounts();
    }
}

bool reader::verifyIncPattern( void )
{
    bool RV = true;
    uint32_t *ptr = getMapPtr();

    for ( uint32_t i=0; i < telemetry::kNumEntries; ++i)
    {
        if (*ptr++ != i)
        {
            RV = false;
            break;
        }
    }

    return RV;
}

void reader::printBitCounts( void )
{
    uint32_t row;
    uint32_t col;

    cout << "Bit counts" << endl;
    for ( row=0; row < telemetry::kNumThreads; ++row)
    {
        cout << hex << setfill('0') << setw(4) << "ROW: " << row << " : ";// << endl;
        for (col=0; col < telemetry::kNumEntriesPerThread; ++col)
        {
            cout << hex << setfill('0') << setw(4) << bitCounts[row][col] << ", ";
        }
        cout << endl;
    }
}

reader::~reader()
{

}
