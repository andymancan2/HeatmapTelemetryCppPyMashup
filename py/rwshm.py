## @package rwshm - read write shared memory.
# `

from multiprocessing import Process
from multiprocessing.shared_memory import SharedMemory
from multiprocessing import shared_memory, resource_tracker
import numpy as np

#import telemetry
from telemetry import *

## rshm == read shared memory
class rshm:
    ## The constructor
    # @param self The object pointer
    # @param shmMapFilename A text string of the shared memory filename.
    # @param shmValueSize The shared memory size in bytes.
    def __init__(self, shmMapFilename, shmValueSize ):
        ## Member for SharedMemory object.
        self.shm = SharedMemory(name=shmMapFilename, create=False)
        ## Member for shared memory size in bytes.
        self.valueSize = shmValueSize
        ## Member for number of integers for shared memory.
        self.numInts = int(shmValueSize / 4)
        ## Member for array of integers mapped to shared memory.
        self.arr = np.ndarray([self.numInts], 'u4', buffer = self.shm.buf)

    ## Method to get read access to shared memory.
    # @param self The object pointer
    def getMapPtr(self):
        return self.arr;

    ## The destructor
    # @param self The object pointer
    def __del__(self):
        self.shm.close();
        self.shm.unlink();

## wshm == write shared memory.
class wshm:
    ## The constructor
    # @param self The object pointer
    # @param shmMapFilename A text string of the shared memory filename.
    # @param shmValueSize The shared memory size in bytes.
    def __init__(self, shmMapFilename='/shmem-example', shmValueSize=4 ):
        ## Member for SharedMemory object.
        self.shm = SharedMemory(size=shmValueSize*4, name=shmMapFilename, create=True)
        ## Member for shared memory size in bytes.
        self.valueSize = shmValueSize
        ## Member for number integers in shared memory.
        self.numInts = int( shmValueSize / 4 );
        ## Member array mapped to shared memory
        self.arr = np.ndarray([self.numInts], 'u4', buffer = self.shm.buf)
        for i in range(telemetry.kNumEntries):
           self.arr[i] = 0

    ## Method to get write access to shared memory.
    # @param self The object pointer
    def getMapPtr(self):
        return self.arr;

    ## The destructor
    # @param self The object pointer
    def __del__(self):
        self.shm.close();
        # The following statement needed so writing process can terminate
        # with shared memory in tact for later reading.
        resource_tracker.unregister(self.shm._name, 'shared_memory')
        #self.shm.unlink(); # Only unlink after reading.

## Writer for shared memory.
class writer(wshm):
    ## The constructor
    def __init__(self):
       wshm.__init__(self, shmMapFilename="/telemetry", shmValueSize=telemetry.kTotalByteSize)

    ## The destructor.
    # @param self The object pointer
    def __del__(self):
       wshm.__del__(self)

    ## Method for simple initialization for later verification.
    # @param self The object pointer
    def initIncPattern(self):
        for i in range(telemetry.kNumEntries):
           self.arr[i] = i

## Reader for reading telemetry data shared memory to compute bit counts.
class reader(rshm):
    ## The constructor
    def __init__(self):
       rshm.__init__(self, shmMapFilename="/telemetry", shmValueSize=telemetry.kTotalByteSize)
       self.clearTelemetry()

    ## The destructor
    # @param self The object pointer
    def __del__(self):
       rshm.__del__(self)

    ## Initialize the bit counts to zero.
    # @param self The object pointer
    def clearTelemetry( self ):
       ## Member array for storing bit counts
       self.bitCounts = np.zeros( [telemetry.kNumThreads,telemetry.kNumEntriesPerThread], dtype = int )

    ## Method to count 1 for every bit that is on for a sample(frame).
    # @param self The object pointer
    # @param sampleIdx The sample(frame) to analyze.
    def gatherTelemetryBitCounts( self, sampleIdx ):
       row = 0
       col = 0
       entryIdx = (sampleIdx * telemetry.kNumEntriesPerFrame)
       for entry in range(telemetry.kNumEntriesPerFrame):
          entryValue = self.arr[ entryIdx ]
          entryIdx += 1
          bitMask = 0x01
          count = 0;
          for bitIdx in range( 32 ):
             if ((entryValue & bitMask) != 0):
                count += 1
             bitMask = bitMask << 1
          self.bitCounts[row][col] += count
          col += 1
          if (col >= telemetry.kNumEntriesPerThread):
             col = 0
             row += 1

    ## Method to verify a simple pattern.
    # @param self The object pointer
    def verifyIncPattern( self ):
        RV = True
        for i in range(telemetry.kNumEntries):
            if (self.arr[i] != i):
                RV = False;
                break;
        return RV

    ## Print bit counts.
    # @param self The object pointer
    def printBitCounts( self ):
       for row in range(telemetry.kNumThreads):
          print( "ROW: %04x, " % row )
          line = "   "
          for col in range(telemetry.kNumEntriesPerThread):
             line += "%04x, " % self.bitCounts[row][col]
          print(line)



