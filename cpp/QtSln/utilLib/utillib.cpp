#include "utillib.h"

void hwTst( void )
{
    printf("hwTst\n");
}

void sleepms( const unsigned int ms )
{
    using millis = std::chrono::milliseconds;
    std::this_thread::sleep_for( millis(ms) );
}

UtilLib::UtilLib()
{
}
