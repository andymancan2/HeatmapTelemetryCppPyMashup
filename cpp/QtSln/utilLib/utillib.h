#ifndef UTILLIB_H
#define UTILLIB_H

#include <thread>
#include <chrono>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <iostream>
#include <iomanip>
#include "ktelemetry.h"

//! Sleep for milliseconds.
//! \param ms Milliseconds
void sleepms( const unsigned int ms );

//! A place holder class.
class UtilLib
{
public:
    //! A place holder contructor.
    UtilLib();
};

#endif // UTILLIB_H
