## @file pyreader.py
# Script to verify an incrementing pattern in shared memory.

from rwshm import *

## main()
def main():
   """
   Instatiate a reader object and call method to verify
   an incrementing pattern in shared memory.
   """
   r = reader() 
   print("Verify = %r" % r.verifyIncPattern())
   #del reader
   del r

main()


