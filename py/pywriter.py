## @file pywriter.py
# Script to write an incrementing pattern to shared memory.

from rwshm import *

## main()
def main():
   """
   Instaniate a writer class, then call a method to
   initialize shared memory with an incrementing pattern.
   """
   w = writer()
   w.initIncPattern()

   del w

main()
