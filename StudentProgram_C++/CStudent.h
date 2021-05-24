#pragma once
#include "Global.h"

class CStudent
{  
    string name, grade;
    const int score1, score2, score3; 
    int total;
 
public:
    CStudent(string name, int score1, int score2, int score3,int total,string grade)
        :name(name), score1(score1), score2(score2), score3(score3), total(total), grade(grade)
    {}
   
public:
    string getName() { return name; }
    int getScore1() { return score1; }
    int getScore2() { return score2; }
    int getScore3() { return score3; }
    int  getTotal() { return total; }
    string getGrade() { return grade;  }
    void setGrade(string grade) { this->grade = grade; }

public:
    friend ostream& operator<<(ostream& os, CStudent* stu)
    {
        os << "[�̸�]: " << stu->name <<
            "  [����1]: " << stu->score1 <<
            "  [����2]: " << stu->score2 <<
            "  [����3]: " << stu->score3 <<
            "  [���]: " << stu->grade << '\n';
        return os;
    }
};

