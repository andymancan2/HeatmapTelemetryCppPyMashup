//! @file utillib.cpp
//! General utility details.
//! \author Andrew Louder

#include "utillib.h"

void sleepms( const unsigned int ms )
{
    using millis = std::chrono::milliseconds;
    std::this_thread::sleep_for( millis(ms) );
}

UtilLib::UtilLib()
{
}
