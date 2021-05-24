#pragma once

#include <vector>
using namespace std;

#include "Global.h"
#include "CStudent.h"

class StuManager
{
    vector<CStudent*> base;
public:
    StuManager();
    ~StuManager();

public:
    void Run();

private:
    keydata SelectMenu();
    bool Exist(string name);

    void AddStu();
    void RemoveStu();
    void SearchStuByName();
    void ListAll();
    void Statics();
    void Save();
    void Load();
};