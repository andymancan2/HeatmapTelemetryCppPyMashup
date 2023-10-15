## @file pywriter.py
# Script to write an incrementing pattern to shared memory.

from telemetry import *
from rwshm import *

w = writer() #("telemetry", telemetry.kTotalByteSize)
w.initIncPattern()

del writer
