//! \file utillib.h
//! \author Andrew Louder
//! \mainpage The top-level header file for this library is utillib.h
//! \section intro_sec Introduction
//! General utilities.
//!

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
//! \param ms Milliseconds.
//! \return none
void sleepms( const unsigned int ms );

//! A place holder class.
class UtilLib
{
public:
    //! A place holder contructor.
    UtilLib();
};

#endif // UTILLIB_H
