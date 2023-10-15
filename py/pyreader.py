## @file pyreader.py
# Script to verify an incrementing pattern in shared memory.

from rwshm import *

r = reader() #("/telemetry", telemetry.kTotalByteSize)
print("Verify = %r" % r.verifyIncPattern())
del reader


