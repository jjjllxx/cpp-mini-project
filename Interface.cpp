#include "Interface.h"
#include "Student.h"
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void sims::Interface::enter0ToGoBack()
{
    std::cout << '\n'
              << '\n'
              << std::setw(20) << " " << "输入0返回上一层：";
    std::string str;
    while (std::cin >> str)
    {
        if (str == "0")
        {
            break;
        }
        else
        {
            std::cout << '\n'
                      << '\n'
                      << std::setw(15) << " " << "输入错误！按0返回上一层：";
        }
    }
}

void sims::Interface::showAllStudents(const std::vector<sims::Student>& students)
{
    std::cout << '\n'
              << '\n'
              << std::setw(22) << " " << "以下为所有学生名单：" << '\n';
    std::cout << std::left;
    std::cout << '\n'
              << std::setw(20) << " " << std::setw(6) << "编号" << std::setw(12) << "学号" << std::setw(10) << "姓名" << '\n';
    for (std::size_t i = 0; i < students.size(); ++i)
    {
        std::cout << std::setw(20) << "     " << std::setw(6) << i + 1 << std::setw(12) << students[i].number << std::setw(10) << students[i].name << '\n';
    }
}

void sims::Interface::showModifyMenu(const bool hasErrorBefore)
{
    std::cout << '\n'
              << std::setw(20) << "        " << std::setw(16) << "1.修改学生信息" << std::setw(10) << "2.返回" << '\n';
    hasErrorBefore == true ? std::cout << '\n'
                                       << std::setw(21) << " " << "错误输入！请重新选择："
                           : std::cout << '\n'
                                       << std::setw(25) << " " << "请选择：";
}

void sims::Interface::showModifyOption(const bool hasErrorBefore)
{
    std::cout << '\n'
              << '\n'
              << std::setw(18) << " " << std::setw(10) << "1.学号" << std::setw(10) << "2.姓名" << std::setw(10) << "3.性别" << '\n';
    std::cout << '\n'
              << std::setw(18) << " " << std::setw(10) << "4.年龄" << std::setw(10) << "5.地址" << std::setw(10) << "6.返回" << '\n';

    hasErrorBefore == true ? std::cout << '\n'
                                       << std::setw(22) << " " << "输入错误啦！请重新选择吧："
                           : std::cout << '\n'
                                       << std::setw(22) << " " << "请选择修改内容：";
}

int sims::Interface::setDegreeStandard(const std::string& degreeName)
{
    std::cout << '\n'
              << '\n'
              << std::setw(20) << ' ' << "请输入" << degreeName << "学位修满课程数：";

    std::string courseNum;

    while (std::cin >> courseNum)
    {
        bool isValid = true;
        int  cNum    = 0;

        if (courseNum.size() > 2)
        {
            isValid = false;
        }
        else
        {
            for (const char ch : courseNum)
            {
                if (std::isdigit(ch) == 0)
                {
                    isValid = false;
                    break;
                }
                cNum = cNum * 10 + (ch - '0');
            }
        }

        if (isValid == false)
        {
            std::cout << '\n'
                      << '\n'
                      << std::setw(20) << " " << "输入课程数不符合标准！" << '\n';
            std::cout << '\n'
                      << '\n'
                      << std::setw(20) << ' ' << "请输入" << degreeName << "学位修满课程数：";
            continue;
        }

        return cNum;
    }

    return -1;
}

bool sims::Interface::isStudentInfoLoaded(const std::vector<sims::Student>& students)
{
    if (students.empty() == true)
    {
        system("clear");
        std::cout << '\n'
                  << '\n'
                  << std::setw(20) << " " << "学生信息管理系统尚未建立！" << '\n';
        std::cout << '\n'
                  << '\n'
                  << std::setw(20) << " " << "请等待招生办人员建立学生管理系统！" << '\n';

        sims::Interface::enter0ToGoBack();

        return false;
    }

    return true;
}

std::size_t sims::Interface::convertStudentNumber(const std::size_t  studentsSize,
                                                  const std::string& idx)
{
    std::size_t choose = 0;

    if (idx.size() > 3)
    {
        return 0;
    }

    for (char ch : idx)
    {
        if (std::isdigit(ch) == 0)
        {
            return 0;
        }
        choose *= 10;
        choose += ch - '0';
    }

    return choose <= studentsSize ? choose : 0;
}

void sims::Interface::loadMajorScore(const std::string&                dataPath,
                                     const std::vector<sims::Student>& students,
                                     std::vector<sims::DepStudent>&    majorStudents)
{
    if (sims::Interface::isStudentInfoLoaded(students) == false
        || sims::Interface::isScoreLoaded("本系主修学生", majorStudents) == true)
    {
        return;
    }
    std::ifstream fin;
    fin.open(dataPath);

    while (!fin.eof())
    {
        int  score = 0;
        char ch    = 0;

        sims::DepStudent ds;
        fin >> ds.number;
        fin.get(ch);
        while (ch == ' ' && !fin.eof())
        {
            fin >> score;
            ds.scores.push_back(score);
            fin.get(ch);
        }

        majorStudents.push_back(ds);
    }
    fin.close();

    system("clear");
    std::cout << '\n'
              << std::setw(23) << " " << "主修学生成绩录入完毕！" << '\n';
    std::cout << '\n'
              << std::setw(23) << " " << "以下为所有主修学生成绩：" << '\n';
    std::cout << '\n'
              << std::setw(20) << " " << std::setw(10) << "学号" << "各科目成绩" << '\n';
    for (const sims::DepStudent& ds : majorStudents)
    {
        std::cout << std::setw(18) << " " << std::setw(10) << ds.number;
        for (const int score : ds.scores)
        {
            std::cout << std::setw(5) << score;
        }
        std::cout << '\n';
    }

    sims::Interface::enter0ToGoBack();
}

void sims::Interface::loadMinorScore(const std::string&                dataPath,
                                     const std::vector<sims::Student>& students,
                                     std::vector<sims::DepStudent>&    minorStudents)
{
    if (sims::Interface::isStudentInfoLoaded(students) == false
        || sims::Interface::isScoreLoaded("本系辅修学生", minorStudents) == true)
    {
        return;
    }

    system("clear");

    std::ifstream fin;
    fin.open(dataPath);

    while (!fin.eof())
    {
        int  score = 0;
        char ch    = 0;

        sims::DepStudent ds;

        fin >> ds.number;
        fin >> ds.major;

        fin.get(ch);

        while (ch == ' ' && !fin.eof())
        {
            fin >> score;
            ds.scores.push_back(score);
            fin.get(ch);
        }
        minorStudents.push_back(ds);
    }
    fin.close();

    std::cout << '\n'
              << std::setw(22) << " " << "辅修学生成绩录入完毕！" << '\n';
    std::cout << '\n'
              << std::setw(22) << " " << "以下为所有辅修学生成绩：" << '\n';
    std::cout << '\n'
              << std::setw(20) << " " << std::setw(10) << "学号" << "各科目成绩" << '\n';
    for (const sims::DepStudent& ds : minorStudents)
    {
        std::cout << std::setw(18) << " " << std::setw(10) << ds.number;
        for (const int score : ds.scores)
        {
            std::cout << std::setw(5) << score;
        }
        std::cout << '\n';
    }
    sims::Interface::enter0ToGoBack();
}

bool sims::Interface::isGoodStudent(const std::vector<int>& scores)
{
    int cnt = 0;
    for (const int score : scores)
    {
        if (score < 70)
        {
            return false;
        }

        if (score >= 85)
        {
            cnt++;
        }
    }

    return cnt > 2;
}

void sims::Interface::countGoodStudents(const std::string&                   dataPath,
                                        const std::vector<sims::Student>&    students,
                                        const std::unordered_map<long, int>& numToIdx,
                                        const std::vector<sims::DepStudent>& majorStudents,
                                        const std::vector<sims::DepStudent>& minorStudents)
{
    if (sims::Interface::isStudentInfoLoaded(students) == false
        || sims::Interface::isScoreLoaded("本系学生", majorStudents) == false)
    {
        return;
    }

    system("clear");
    std::cout << '\n'
              << '\n'
              << std::setw(18) << " " << "以下为本学期本系优秀学生：" << '\n';
    std::cout << '\n'
              << "     " << std::setw(12) << "学号" << std::setw(12) << "姓名" << std::setw(7) << "性别" << std::setw(7) << "年龄" << std::setw(20) << "各科成绩" << '\n'
              << '\n';

    std::ofstream fout;
    fout.open(dataPath);

    for (const sims::DepStudent& ds : majorStudents)
    {
        if (sims::Interface::isGoodStudent(ds.scores) == false)
        {
            continue;
        }

        const int idx = numToIdx.at(ds.number);
        sims::Interface::showScores(dataPath, students[idx], ds.scores);
    }

    for (const sims::DepStudent& ds : minorStudents)
    {
        if (sims::Interface::isGoodStudent(ds.scores) == false)
        {
            continue;
        }

        const int idx = numToIdx.at(ds.number);
        sims::Interface::showScores(dataPath, students[idx], ds.scores);
    }

    sims::Interface::enter0ToGoBack();

    fout.close();
}

void sims::Interface::showScores(const std::string&      dataPath,
                                 const sims::Student&    student,
                                 const std::vector<int>& scores)
{
    std::cout << std::left;
    std::cout << "     " << std::setw(12) << student.number << std::setw(12) << student.name;
    student.sex == 0 ? std::cout << std::setw(7) << "男" : std::cout << std::setw(7) << "女";

    std::cout << std::setw(7) << student.age;
    for (const int score : scores)
    {
        std::cout << std::setw(4) << score;
    }
    std::cout << '\n'
              << '\n';

    std::ofstream fout;
    fout.open(dataPath);
    fout << student.number << ' ' << student.name << ' ' << student.sex << ' ' << student.age;
    for (const int score : scores)
    {
        fout << ' ' << score;
    }
    fout << '\n';
    fout.close();
}

void sims::Interface::countFailure(const std::string&                   type,
                                   const std::string&                   dataPath,
                                   const std::vector<sims::Student>&    students,
                                   const std::unordered_map<long, int>& numToIdx,
                                   const std::vector<sims::DepStudent>& majorStudents)
{
    if (sims::Interface::isStudentInfoLoaded(students) == false
        || sims::Interface::isScoreLoaded("本系" + type + "学生", majorStudents) == false)
    {
        return;
    }
    system("clear");
    std::cout << '\n'
              << '\n'
              << std::setw(18) << " " << "以下为本学期需补考的" + type + "学生：" << '\n';
    std::cout << '\n'
              << "     " << std::setw(12) << "学号" << std::setw(12) << "姓名" << std::setw(7) << "性别" << std::setw(7) << "年龄" << std::setw(20) << "补考科目成绩" << '\n';

    for (const sims::DepStudent& ds : majorStudents)
    {
        std::vector<int> failures;
        for (const int scores : ds.scores)
        {
            if (scores < 60)
            {
                failures.push_back(scores);
            }
        }
        if (failures.empty() == true)
        {
            continue;
        }

        const int idx = numToIdx.at(ds.number);
        sims::Interface::showScores(dataPath, students[idx], failures);
    }
    sims::Interface::enter0ToGoBack();
}

void sims::Interface::showDegreeStandard(const int          aStandard,
                                         const int          bStandard,
                                         const int          cStandard,
                                         const std::string& type)
{
    std::cout << '\n'
              << std::setw(20) << " " << "当前各系" + type + "学位需修满课程数：" << '\n';
    std::cout << '\n'
              << std::setw(22) << " " << std::setw(5) << "A: " << std::setw(3) << aStandard << std::setw(4) << "B: " << std::setw(3) << bStandard << std::setw(4) << "C: " << std::setw(3) << cStandard << '\n';
}

void sims::Interface::showCandidates(const std::string&                   majorName,
                                     const std::vector<long>&             candidates,
                                     const std::vector<sims::Student>&    students,
                                     const std::unordered_map<long, int>& numToIdx)
{
    std::ofstream fout;
    fout.open("/proj/student-info-management-system/Data/Degree.DAT");
    for (const long num : candidates)
    {
        const int idx = numToIdx.at(num);
        std::cout << std::setw(8) << " " << std::setw(10) << num
                  << std::setw(10) << students[idx].name << std::setw(10) << majorName;
        students[idx].sex == 0 ? std::cout << std::setw(5) << "男" : std::cout << std::setw(5) << "女";

        std::cout << std::setw(5) << students[idx].age << std::setw(10) << students[idx].address << '\n';
        fout << num
             << " " << students[idx].name << " " << majorName << " " << students[idx].sex << " " << students[idx].age << " " << students[idx].address << '\n';
    }
    fout.close();
}