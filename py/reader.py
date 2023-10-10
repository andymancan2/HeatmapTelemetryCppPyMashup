
import rwshm
from telemetry import *

reader = rwshm.reader("telemetry", telemetry.kTotalByteSize)
reader.gatherTelemetrySamples( 10000 )
reader.printBitCounts()
if reader.verifyIncBitCounts():
   print("Verified inc bits PASSED.")
else:
   print("Verified inc bits FAILED.")


del reader

