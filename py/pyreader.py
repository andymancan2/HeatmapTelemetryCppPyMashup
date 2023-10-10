

from rwshm import *

r = reader() #("/telemetry", telemetry.kTotalByteSize)
print("Verify = %r" % r.verifyIncPattern())
del reader


