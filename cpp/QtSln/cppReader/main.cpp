#include <iostream>
#include "utillib.h"
#include "rwshm.h"

using namespace std;

int main()
{
    cout << "cppReader, Hello World!" << endl;
    reader r;
    r.gatherTelemetryBitCounts(2);
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
