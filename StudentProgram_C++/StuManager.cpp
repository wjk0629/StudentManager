#include "StuManager.h"
#include "Compare.h"
#include <algorithm>
#include <fstream>

StuManager::StuManager()
{
}


StuManager::~StuManager()
{
}

void StuManager::Run()
{
    keydata key = keydata::NO_DEFINED;
    while ((key = SelectMenu()) != ESC)
    {
        switch (key)
        {
        case F1: AddStu();   break;
        case F2: RemoveStu();  break;
        case F3: SearchStuByName(); break;
        case F4: ListAll(); break;
        case F5: Statics();   break;
        case F6: Save();   break;
        case F7: Load();   break;
        default: cout << "잘못된 메뉴를 선택하였습니다." << endl;
        }

        cout << "아무키나 누르세요" << endl;
        Global::getkey();
    }
}

keydata StuManager::SelectMenu()
{
    Global::clrscr();
    cout << "메뉴 [ESC]:종료" << '\n';
    cout << "[F1]:학생 추가 [F2]:학생 삭제 [F3]:학생 검색";
    cout << "[F4]:성적 보기 [F5]:성적 통계" << '\n';
    cout << "[F6]:파일 저장 [F7]:파일 열기" << '\n';
    cout << "메뉴를 선택하세요" << '\n';

    return  Global::getkey();
}

bool StuManager::Exist(string name)
{
    vector<CStudent*>::iterator seek;
    seek = base.begin();
    CStudent* stu = NULL;
    for (seek = base.begin(); seek!=base.end(); ++seek)
    {
        stu = *seek;
        if (stu->getName() == name)
            return true;
    }
    return false;
}

void StuManager::AddStu()
{
    string name = "";
    cout << "학생 추가를 선택하셨습니다." << endl;
   
    cout << "이름을 입력하세요" << endl;
    name = Global::getstr();
    if (Exist(name))
    {
        cout << "이미 등록된 같은 이름의 학생이 있습니다." << endl;
        return;
    }

    int score1;
    cout << "점수1을 입력하세요" << endl;
    score1 = Global::getscore();

    int score2;
    cout << "점수2을 입력하세요" << endl;
    score2 = Global::getscore();

    int score3;
    cout << "점수3을 입력하세요" << endl;
    score3 = Global::getscore();

    int total;
    total = score1 + score2 + score3;
    
    string grade = "";
        
    base.push_back(new CStudent(name, score1,score2,score3,total,grade));
}

void StuManager::RemoveStu()
{
    string name = "";
    cout << "삭제할 학생 이름을 입력하세요" << endl;
    name = Global::getstr();

    CStudent* stu;
    for (int i = 0; i < (int)base.size(); i++) {
        stu = base[i];
        if (stu->getName() == name)
        {
            base.erase(base.begin() + i);
            cout << "삭제되었습니다." << endl;
            return;
        }
    }
    cout << name << " 학생의 성적은 기록되지 않았습니다." << endl;
}

void StuManager::SearchStuByName()
{
    string name = "";
    cout << "검색할 학생 이름을 입력하세요: " << endl;
    name = Global::getstr();



    vector<CStudent*>::iterator seek;
    seek = base.begin();
    CStudent* stu = NULL;
    for (seek = base.begin(); seek != base.end(); ++seek)
    {
        stu = *seek;
        if (stu->getName() == name)
            cout << stu << endl;
    }
}

void StuManager::ListAll()
{
    CStudent* stu = NULL;
    int n;
    n = (int)base.size();
   
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((j + 1) < n)
            {
                if (base[j]->getTotal() < base[j + 1]->getTotal())
                {
                    swap(base[j], base[j + 1]);
                }
            }
        }
    }

    int comparegrade1 = floor(((int)base.size() * 0.3) + 0.5);
    int comparegrade2 = floor(((int)base.size() * 0.4) + 0.5);

    for (int i = 0; i < base.size(); i++)
    {
        if (base[i]->getGrade() == "")
        {
            if (i < comparegrade1) { base[i]->setGrade("A"); }
            else if (i < (comparegrade1 + comparegrade2)) { base[i]->setGrade("B"); }
            else base[i]->setGrade("C");
        }
    }
    
    for (int i = 0; i < (int)base.size(); i++)
    {
        stu = base[i];
        cout << stu << endl;
    }
}

void StuManager::Statics()
{
    CStudent* stu = NULL;
    cout << "현재 등록된 학생의 최대값, 평균값, 표준편차는 다음과 같습니다." << '\n';
    int totalscore1 = 0; int totalscore2 = 0; int totalscore3 = 0;
    int maxscore1 = 0; int maxscore2 = 0; int maxscore3 = 0;
    double avgscore1 = 0; double avgscore2 = 0; double avgscore3 = 0;
    double sdevscore1 = 0; double sdevscore2 = 0; double sdevscore3 = 0;

    int n;
    n = (int)base.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((j + 1) < n)
            {
                if (base[j]->getTotal() < base[j + 1]->getTotal())
                {
                    swap(base[j], base[j + 1]);
                }
            }
        }
    }

    maxscore1 = base[0]->getScore1();
    maxscore2 = base[0]->getScore2();
    maxscore3 = base[0]->getScore3();

    for (int i = 0; i < (int)base.size(); i++) {
        totalscore1 = totalscore1 + base[i]->getScore1();
    }
    avgscore1 = totalscore1 / (int)base.size();
    for (int i = 0; i < (int)base.size(); i++) {
        totalscore2 += base[i]->getScore2();
    }
    avgscore2 = totalscore2 / (int)base.size();
    for (int i = 0; i < (int)base.size(); i++) {
        totalscore3 += base[i]->getScore3();
    }
    avgscore3 = totalscore3 / (int)base.size();

    for (int j = 0; j < (int)base.size(); j++) {
        sdevscore1 = pow((base[j]->getScore1() - avgscore1), 2);
        totalscore1 += sdevscore1;
    }sdevscore1 = sqrt(totalscore1 / (int)base.size());
    for (int j = 0; j < (int)base.size(); j++) {
        sdevscore2 = pow((base[j]->getScore2() - avgscore2), 2);
        totalscore2 += sdevscore2;
    }sdevscore2 = sqrt(totalscore2 / (int)base.size());
    for (int j = 0; j < (int)base.size(); j++) {
        sdevscore3 = pow((base[j]->getScore3() - avgscore3), 2);
        totalscore3 += sdevscore3;
    }  sdevscore3 = sqrt(totalscore3 / (int)base.size());

    cout << '\t' << "최대값" << '\t' << "평균값" << '\t' << "표준편차" << '\n';
    cout << "점수1 :   " << maxscore1 << '\t' << avgscore1 << '\t' << sdevscore1 << '\n';
    cout << "점수2 :   " << maxscore2 << '\t' << avgscore2 << '\t' << sdevscore2 << '\n';
    cout << "점수3 :   " << maxscore3 << '\t' << avgscore3 << '\t' << sdevscore3 << '\n';
}

void StuManager::Save()
{
    ofstream saveFile("C:\\Users\\PC\\source\\repos\\Project2\\test.txt");
    if (!saveFile.is_open())
    {
        cout << "파일을 저장하는데 실패했습니다." << '\n';
    }
    else cout << "파일을 성공적으로 저장합니다." << '\n';
    for (int i = 0; i < (int)base.size(); i++)
    {
        saveFile << base[i] << '\n';
    }
    saveFile.close();

}

void StuManager::Load()
{
    ifstream loadFile("C:\\Users\\PC\\source\\repos\\Project2\\test.txt");
    if (!loadFile)
    {
        cout << "파일을 로드하는데 실패했습니다." << '\n';
    }
    else cout << "파일을 성공적으로 로드합니다." << '\n';
    string temp;
    int temp2;
    string name, grade;
    int score1, score2, score3, total;
    
    while ((temp2 = loadFile.get()) != EOF)
    {
        loadFile >> temp >> name >> temp >> score1 >> temp >> score2 >> temp >> score3 >> temp >> grade;
        total = score1 + score2 + score3;
        
        base.push_back(new CStudent(name, score1, score2, score3, total, grade));
    }
    loadFile.close();
}



