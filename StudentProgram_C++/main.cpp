#include <iostream>
using namespace std;
#include "StuManager.h"
int main()
{
    StuManager* pman = new StuManager;

    pman->Run();

    delete pman;
    return 0;
}