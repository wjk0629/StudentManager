#pragma once
#include <string>
#include <iostream>
using namespace std;

enum keydata
{
    NO_DEFINED, F1, F2, F3, F4, F5, F6, F7, ESC
};

class Global
{
 private:
    Global();
    ~Global();

public:
    static void clrscr();
    static int getscore();
    static string getstr();
    static keydata getkey();
};
