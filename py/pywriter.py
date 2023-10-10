


from telemetry import *
from rwshm import *

w = writer() #("telemetry", telemetry.kTotalByteSize)
w.initIncPattern()

del writer
