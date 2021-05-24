#include "Global.h"
#include <conio.h>
#include <windows.h>

Global::Global() {}
Global::~Global() {}

void Global::clrscr()
{
    system("cls");
}

int Global::getscore()
{
    int score;
    char buf[255 + 1];
    cin.getline(buf, 255);
    cin.clear();
    sscanf_s(buf, "%d", &score);
    return score;
}

string Global::getstr()
{
    char buf[255 + 1];
    cin.getline(buf, 255);
    cin.clear();
    return buf;
}

keydata Global::getkey()
{
    int key = _getch();

    if (key == 27)
        return ESC;
    if (key == 0) 
    {
        key = _getch();
        switch (key)
        {
        case 59: return F1;
        case 60: return F2;
        case 61: return F3;
        case 62: return F4;
        case 63: return F5;
        case 64: return F6;
        case 65: return F7;
        }
    }
    return NO_DEFINED;
}