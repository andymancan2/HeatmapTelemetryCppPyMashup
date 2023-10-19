//! @file main.cpp
//! @author Andrew Louder
//! @mainpage The main() for the cppReader executable.
//! @section intro_sec Introduction
//! Reads and verifies an incrementing pattern in shared memory.

#include <iostream>
#include "utillib.h"
#include "rwshm.h"

using namespace std;

//! main() Reads and verifies an incrementing pattern in shared memory.
//! \param argc The argument count.
//! \param argv A list of arguments.
//! \return An exit code of 0.
int main( int argc, char *argv[])
{
    reader r; //!< Instance of reader.

    cout << "cppReader, Hello World!" << endl;
    if ( r.verifyIncPattern() )
    {
        cout << "Verified SUCCEEDED" << endl;
    }
    else
    {
        cout << "Verified FAILED" << endl;
    }

    return 0;
}
