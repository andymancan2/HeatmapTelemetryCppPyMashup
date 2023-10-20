//! @file rwshm.h
//! Class definitions for reading and writing shared memory.
//! @author Andrew Louder
#ifndef RWSHM_H
#define RWSHM_H

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <cstdint>
#include "ktelemetry.h"

//! wshm == Write shared memory.
class wshm
{
    const char * mapFile;  //!< Map filename.
    const size_t valueSz;  //!< Value size in bytes.
    const int openFlag;    //!< Open flag.
    const int mapProt;     //!< Map protect.
    const mode_t openMode; //!< Open mode.
    int fd;                //!< File descriptor.
    uint32_t * mapDataPtr; //!< Map data pointer.

public:
    //! The constructor.
    //! \param shmMapFile
    //! \param shmValueSz
    //! \param shmOpenFlag
    //! \param shmMapProt
    //! \param shmOpenMode
    //! \public
    wshm( const char* shmMapFile="/shmem-example",
         size_t shmValueSz=3,
         int shmOpenFlag=O_CREAT | O_EXCL | O_RDWR,
         int shmMapProt=PROT_READ | PROT_WRITE,
         mode_t shmOpenMode=0600 );

    //! Returns a pointer to shared memory.
    //! \return Unsigned 32-bit pointer.
    //! \public \memberof wshm
    uint32_t * getMapPtr();

    //! The destructor.
    //! \public \memberof wshm
    virtual ~wshm();
};

//! A derived shared memory class for writing.
class writer : public wshm
{
public:
    //! The constructor encapsulating shared memory parameters.
    //! \public \memberof writer
    writer();

    //! The vitual destructor.
    //! \public \memberof writer
    virtual ~writer();

    //! Initialize an incrementing pattern across shared memory for verification.
    //! \public \memberof writer
    void initIncPattern( void );

    //! Initialize a shared memory entry by thread id and entry idx.
    //! \param threadId  Thread identifier
    //! \param entryIdx  Entry index
    //! \param value  The value to set in shared memory.
    //! \public \memberof writer
    void initThreadEntry( uint8_t threadId, uint8_t entryIdx, uint32_t value );
};

//! rshm == Read shared memory.
class rshm
{
    const char * mapFile;  //!< Map file.
    const size_t valueSz;  //!< Value size in bytes.
    const int openFlag;    //!< Open flag.
    const int mapProt;     //!< Map protection.
    const mode_t openMode; //!< Open mode.
    int fd;                //!< File descriptor.
    uint32_t * mapDataPtr; //!< Shared memory map data pointer.

public:
    //! The constructor.
    //! \param shmMapFile Filename
    //! \param shmSz Shared memory size in bytes.
    //! \param shmOpenFlag
    //! \param shmMapProt
    //! \param shmOpenMode
    //! \public \memberof rshm
    rshm( const char* shmMapFile="/shmem-example",
          size_t shmSz=3,
         int shmOpenFlag=O_RDONLY,
         int shmMapProt=PROT_READ | PROT_WRITE,
         mode_t shmOpenMode=0666 );

    //! Get the shared memory pointer.
    //! \return A unsigned 32-bit pointer.
    //! \public \memberof rshm
    uint32_t * getMapPtr( void );

    //! The destructor.
    //! \public \memberof rshm
    virtual ~rshm( void );
};

//! A derived shared memory class for reading.
class reader : public rshm
{
    //!< Bit count array indexed by threads and entries per thread.
    uint16_t bitCounts[telemetry::kNumThreads][telemetry::kNumEntriesPerThread] {};

public:
    //! The constructor to encapsulating the shared memory parameters.
    //! \public \memberof reader
    reader( void );

    //! Gather bit counts for a number of samples(frames).
    //! \param numSamples number of samples(frames).
    //! \public \memberof reader
    void gatherTelemetryBitCounts( uint32_t numSamples );

    //! Verify an incrementing pattern in shared memory.
    //! \return Verify bool result.
    //! \public \memberof reader
    bool verifyIncPattern();

    //! Print bit counts.
    //! \public \memberof reader
    void printBitCounts();

    //! The destructor.
    //! \public \memberof reader
    virtual ~reader();
};

#endif // RWSHM_H
