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
        default: cout << "�߸��� �޴��� �����Ͽ����ϴ�." << endl;
        }

        cout << "�ƹ�Ű�� ��������" << endl;
        Global::getkey();
    }
}

keydata StuManager::SelectMenu()
{
    Global::clrscr();
    cout << "�޴� [ESC]:����" << '\n';
    cout << "[F1]:�л� �߰� [F2]:�л� ���� [F3]:�л� �˻�";
    cout << "[F4]:���� ���� [F5]:���� ���" << '\n';
    cout << "[F6]:���� ���� [F7]:���� ����" << '\n';
    cout << "�޴��� �����ϼ���" << '\n';

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
    cout << "�л� �߰��� �����ϼ̽��ϴ�." << endl;
   
    cout << "�̸��� �Է��ϼ���" << endl;
    name = Global::getstr();
    if (Exist(name))
    {
        cout << "�̹� ��ϵ� ���� �̸��� �л��� �ֽ��ϴ�." << endl;
        return;
    }

    int score1;
    cout << "����1�� �Է��ϼ���" << endl;
    score1 = Global::getscore();

    int score2;
    cout << "����2�� �Է��ϼ���" << endl;
    score2 = Global::getscore();

    int score3;
    cout << "����3�� �Է��ϼ���" << endl;
    score3 = Global::getscore();

    int total;
    total = score1 + score2 + score3;
    
    string grade = "";
        
    base.push_back(new CStudent(name, score1,score2,score3,total,grade));
}

void StuManager::RemoveStu()
{
    string name = "";
    cout << "������ �л� �̸��� �Է��ϼ���" << endl;
    name = Global::getstr();

    CStudent* stu;
    for (int i = 0; i < (int)base.size(); i++) {
        stu = base[i];
        if (stu->getName() == name)
        {
            base.erase(base.begin() + i);
            cout << "�����Ǿ����ϴ�." << endl;
            return;
        }
    }
    cout << name << " �л��� ������ ��ϵ��� �ʾҽ��ϴ�." << endl;
}

void StuManager::SearchStuByName()
{
    string name = "";
    cout << "�˻��� �л� �̸��� �Է��ϼ���: " << endl;
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
    cout << "���� ��ϵ� �л��� �ִ밪, ��հ�, ǥ�������� ������ �����ϴ�." << '\n';
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

    cout << '\t' << "�ִ밪" << '\t' << "��հ�" << '\t' << "ǥ������" << '\n';
    cout << "����1 :   " << maxscore1 << '\t' << avgscore1 << '\t' << sdevscore1 << '\n';
    cout << "����2 :   " << maxscore2 << '\t' << avgscore2 << '\t' << sdevscore2 << '\n';
    cout << "����3 :   " << maxscore3 << '\t' << avgscore3 << '\t' << sdevscore3 << '\n';
}

void StuManager::Save()
{
    ofstream saveFile("C:\\Users\\PC\\source\\repos\\Project2\\test.txt");
    if (!saveFile.is_open())
    {
        cout << "������ �����ϴµ� �����߽��ϴ�." << '\n';
    }
    else cout << "������ ���������� �����մϴ�." << '\n';
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
        cout << "������ �ε��ϴµ� �����߽��ϴ�." << '\n';
    }
    else cout << "������ ���������� �ε��մϴ�." << '\n';
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



