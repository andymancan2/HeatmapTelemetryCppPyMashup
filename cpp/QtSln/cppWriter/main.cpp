#include <iostream>
#include "utillib.h"
#include "rwshm.h"

using namespace std;

int main()
{
    writer w;

    cout << "cppWriter, Hello World!" << endl;
    w.initIncPattern();

    return 0;
}
