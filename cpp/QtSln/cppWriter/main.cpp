//! @file main.cpp
//! @author Andrew Louder
//! @mainpage The main() for the cppWriter executable.
//! @section intro_sec Introduction
//! Writes an incrementing pattern to shared memory.

#include <iostream>
#include "utillib.h"
#include "rwshm.h"

using namespace std;

//! main() Writes an incrementing pattern to shared memory.
//! \param argc The argument count.
//! \param argv A list of arguments.
//! \return An exit code of 0.
int main( int argc, char *argv[])
{
    writer w;

    cout << "cppWriter, Hello World!" << endl;
    w.initIncPattern();

    return 0;
}
