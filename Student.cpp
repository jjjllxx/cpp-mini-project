#include "Student.h"
#include "Interface.h"
#include <cmath>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_set>
#include <vector>

void sims::StudentBase::loadBaseData()
{
    if (this->students.size() > 0)
    {
        system("clear");
        std::cout << '\n'
                  << '\n'
                  << std::setw(25) << " " << "学生信息管理系统已建立！" << '\n';

        sims::Interface::enter0ToGoBack();

        return;
    }
    sims::Student stu;

    std::ifstream fin;
    fin.open("/proj/student-info-management-system/Data/Basefile.DAT");
    while (fin.eof() == false)
    {
        fin >> stu.number >> stu.name >> stu.sex >> stu.age >> stu.major >> stu.address;
        this->students.push_back(stu);
        this->numToIdx.insert(std::make_pair(stu.number, this->students.size() - 1));
    }
    fin.close();

    system("clear");
    std::cout << '\n'
              << '\n'
              << std::setw(25) << " " << "学生信息录入完毕！" << '\n';
    sims::Interface::showAllStudents(students);
    std::cout
        << '\n'
        << std::setw(25) << " " << "本届新生共有" << this->students.size() << "人!" << '\n';

    sims::Interface::enter0ToGoBack();
}

void sims::StudentBase::modifyData()
{
    if (sims::Interface::isStudentInfoLoaded(this->getStudents()) == false)
    {
        return;
    }

    system("clear");
    sims::Interface::showAllStudents(students);
    sims::Interface::showModifyMenu();

    std::string idx;
    while (std::cin >> idx)
    {
        if (idx != "1" && idx != "2")
        {
            sims::Interface::showModifyMenu(true);
            continue;
        }
        if (idx == "2")
        {
            break;
        }
        std::cout << '\n'
                  << std::setw(20) << " " << "请输入您要修改的学生编号：";
        std::cin >> idx;

        const std::size_t choose = sims::Interface::convertStudentNumber(this->students.size(), idx);

        if (choose == 0)
        {
            system("clear");
            std::cout << '\n'
                      << std::setw(22) << " " << "无效输入！请重新选择！";

            sims::Interface::showModifyMenu();

            continue;
        }

        sims::Student& choosenStu = this->students[choose - 1];

        std::cout << std::left << '\n';
        
        system("clear");
        std::cout << std::setw(18) << " " << "学号：" << std::setw(20) << choosenStu.number << "姓名：" << choosenStu.name << '\n';
        std::cout << '\n'
                  << std::setw(18) << " " << "性别：";
        choosenStu.sex == 0 ? std::cout << std::setw(20) << "男" : std::cout << std::setw(20) << "女";
        std::cout << "年龄：" << choosenStu.age << '\n';
        std::cout << '\n'
                  << std::setw(18) << " " << "地址：" << choosenStu.address << '\n';

        sims::Interface::showModifyOption();

        while (std::cin >> idx)
        {
            if (idx.size() != 1 || idx[0] < '1' || idx[0] > '6')
            {
                sims::Interface::showModifyOption(true);
                continue;
            }

            if (idx == "1")
            {
                std::cout << '\n'
                          << std::setw(20) << " " << "请输入学号：";
                std::cin >> choosenStu.number;
            }
            else if (idx == "2")
            {
                std::cout << '\n'
                          << std::setw(20) << " " << "请输入姓名： ";
                std::cin >> choosenStu.name;
            }
            else if (idx == "3")
            {
                std::cout << '\n'
                          << std::setw(20) << " " << "请输入性别（0 代表 男， 1 代表 女）：";
                while (std::cin >> idx)
                {
                    if (idx != "0" && idx != "1")
                    {
                        std::cout << '\n'
                                  << std::setw(20) << " " << "输入错误啦！请重新输入性别吧（1 代表 男， 0 代表 女）：";
                        continue;
                    }

                    choosenStu.sex = idx[0] - '0';
                    break;
                }
            }
            else if (idx == "4")
            {
                std::cout << '\n'
                          << std::setw(20) << " " << "请输入年龄：";
                while (std::cin >> idx)
                {
                    if (idx.size() != 2 || std::isdigit(idx[0]) == 0 || std::isdigit(idx[1]) == 0)
                    {
                        std::cout << '\n'
                                  << std::setw(20) << " " << "输入错误啦！请重新输入年龄吧：";
                        continue;
                    }

                    choosenStu.age = idx[1] - '0' + (idx[0] - '0') * 10;
                    break;
                }
            }
            else if (idx == "5")
            {
                std::cout << '\n'
                          << std::setw(20) << " " << "请输入地址：";
                std::cin >> choosenStu.address;
            }
            else if (idx == "6")
            {
                break;
            }

            sims::Interface::showModifyOption(false);
        }

        system("clear");
        sims::Interface::showAllStudents(students);
        sims::Interface::showModifyMenu();
    }

    std::ofstream fout;
    fout.open("/proj/student-info-management-system/Data/Basefile.DAT");
    for (const sims::Student& student : this->students)
    {
        fout << student.number << ' ' << student.name << ' ' << student.sex << ' ' << student.age << ' ' << student.major << ' ' << student.address << '\n';
    }
    fout.close();
}

std::vector<sims::Student> sims::StudentBase::getStudents()
{
    return this->students;
}

std::unordered_map<long, int> sims::StudentBase::getNumToIdx()
{
    return this->numToIdx;
}

void sims::DepA::inputA_MajorScore()
{
    sims::Interface::loadMajorScore("/proj/student-info-management-system/Data/AMajor.DAT",
                                    this->getStudents(),
                                    this->majorStudents);
}

void sims::DepA::inputA_SecondScore()
{
    sims::Interface::loadMinorScore("/proj/student-info-management-system/Data/AMinor.DAT",
                                    this->getStudents(),
                                    this->minorStudents);
}

void sims::DepA::outputA_Good()
{
    sims::Interface::countGoodStudents("/proj/student-info-management-system/Data/AGood.DAT",
                                       this->getStudents(),
                                       this->getNumToIdx(),
                                       this->majorStudents,
                                       this->minorStudents);
}

void sims::DepA::outputA_MajorFail()
{
    sims::Interface::countFailure("主修",
                                  "/proj/student-info-management-system/Data/AMajorFail.DAT",
                                  this->getStudents(),
                                  this->getNumToIdx(),
                                  this->majorStudents);
}

void sims::DepA::outputA_SecondFail()
{
    sims::Interface::countFailure("辅修",
                                  "/proj/student-info-management-system/Data/AMinorFail.DAT",
                                  this->getStudents(),
                                  this->getNumToIdx(),
                                  this->minorStudents);
}

std::string sims::DepA::getMajorAName()
{
    return majorAName;
}

std::vector<sims::DepStudent> sims::DepA::getMajorAStudents()
{
    return this->majorStudents;
}

std::vector<sims::DepStudent> sims::DepA::getMinorAStudents()
{
    return this->minorStudents;
}

void sims::DepB::inputB_MajorScore()
{
    sims::Interface::loadMajorScore("/proj/student-info-management-system/Data/BMajor.DAT",
                                    this->getStudents(),
                                    this->majorStudents);
}

void sims::DepB::inputB_SecondScore()
{
    sims::Interface::loadMinorScore("/proj/student-info-management-system/Data/BMinor.DAT",
                                    this->getStudents(),
                                    this->minorStudents);
}

void sims::DepB::outputB_Good()
{
    sims::Interface::countGoodStudents("/proj/student-info-management-system/Data/BGood.DAT",
                                       this->getStudents(),
                                       this->getNumToIdx(),
                                       this->majorStudents,
                                       this->minorStudents);
}

void sims::DepB::outputB_MajorFail()
{
    sims::Interface::countFailure("主修",
                                  "/proj/student-info-management-system/Data/BMajorFail.DAT",
                                  this->getStudents(),
                                  this->getNumToIdx(),
                                  this->majorStudents);
}

void sims::DepB::outputB_SecondFail()
{
    sims::Interface::countFailure("辅修",
                                  "/proj/student-info-management-system/Data/BMinorFail.DAT",
                                  this->getStudents(),
                                  this->getNumToIdx(),
                                  this->minorStudents);
}

std::string sims::DepB::getMajorBName()
{
    return majorBName;
}

std::vector<sims::DepStudent> sims::DepB::getMajorBStudents()
{
    return this->majorStudents;
}

std::vector<sims::DepStudent> sims::DepB::getMinorBStudents()
{
    return this->minorStudents;
}

void sims::DepC::inputC_MajorScore()
{
    sims::Interface::loadMajorScore("/proj/student-info-management-system/Data/CMajor.DAT",
                                    this->getStudents(),
                                    this->majorStudents);
}

void sims::DepC::inputC_SecondScore()
{
    sims::Interface::loadMinorScore("/proj/student-info-management-system/Data/CMinor.DAT",
                                    this->getStudents(),
                                    this->minorStudents);
}

void sims::DepC::outputC_Good()
{
    sims::Interface::countGoodStudents("/proj/student-info-management-system/Data/CGood.DAT",
                                       this->getStudents(),
                                       this->getNumToIdx(),
                                       this->majorStudents,
                                       this->minorStudents);
}

void sims::DepC::outputC_MajorFail()
{
    sims::Interface::countFailure("主修",
                                  "/proj/student-info-management-system/Data/CMajorFail.DAT",
                                  this->getStudents(),
                                  this->getNumToIdx(),
                                  this->majorStudents);
}

void sims::DepC::outputC_SecondFail()
{
    sims::Interface::countFailure("辅修",
                                  "/proj/student-info-management-system/Data/CMinorFail.DAT",
                                  this->getStudents(),
                                  this->getNumToIdx(),
                                  this->minorStudents);
}

std::string sims::DepC::getMajorCName()
{
    return majorCName;
}

std::vector<sims::DepStudent> sims::DepC::getMajorCStudents()
{
    return this->majorStudents;
}

std::vector<sims::DepStudent> sims::DepC::getMinorCStudents()
{
    return this->minorStudents;
}

sims::StudentMIS::StudentMIS() :
    majorAStd(5), majorBStd(5), majorCStd(5), minorAStd(4), minorBStd(4), minorCStd(4)
{
}

void sims::StudentMIS::setMajorStandard()
{
    if (sims::Interface::isStudentInfoLoaded(this->getStudents()) == false)
    {
        return;
    }

    system("clear");
    sims::Interface::showDegreeStandard(this->majorAStd, this->majorBStd, this->majorCStd, "主修");

    this->majorAStd = sims::Interface::setDegreeStandard("A系主修");
    this->majorBStd = sims::Interface::setDegreeStandard("B系主修");
    this->majorCStd = sims::Interface::setDegreeStandard("C系主修");

    sims::Interface::showDegreeStandard(this->majorAStd, this->majorBStd, this->majorCStd, "主修");

    sims::Interface::enter0ToGoBack();
}

void sims::StudentMIS::setMinorStandard()
{
    if (sims::Interface::isStudentInfoLoaded(this->getStudents()) == false)
    {
        return;
    }

    system("clear");
    sims::Interface::showDegreeStandard(this->minorAStd, this->minorBStd, this->minorCStd, "辅修");

    this->minorAStd = sims::Interface::setDegreeStandard("A系辅修");
    this->minorBStd = sims::Interface::setDegreeStandard("B系辅修");
    this->minorCStd = sims::Interface::setDegreeStandard("C系辅修");

    sims::Interface::showDegreeStandard(this->minorAStd, this->minorBStd, this->minorCStd, "辅修");

    sims::Interface::enter0ToGoBack();
}

void sims::StudentMIS::degree()
{
    if (sims::Interface::isStudentInfoLoaded(this->getStudents()) == false)
    {
        return;
    }

    if (this->getMajorAStudents().empty() == true
        && this->getMajorBStudents().empty() == true
        && this->getMajorCStudents().empty() == true)
    {
        system("clear");
        std::cout << '\n'
                  << '\n'
                  << std::setw(18) << " " << "未找到任何主修学生成绩信息！" << '\n';
        std::cout << '\n'
                  << '\n'
                  << std::setw(20) << " " << "请通知各系教务员录入成绩！" << '\n';
        sims::Interface::enter0ToGoBack();
        return;
    }

    std::ofstream fout;
    fout.open("/proj/student-info-management-system/Data/Degree.DAT");
    fout << "主修学位获得学生：" << '\n';
    system("clear");
    std::cout << '\n'
              << '\n'
              << std::setw(20) << " " << "主修学位获得学生：" << '\n';
    std::cout << std::left;
    std::cout << '\n'
              << std::setw(8) << " " << std::setw(10) << "学号" << std::setw(10) << "姓名" << std::setw(10) << "专业" << std::setw(5) << "性别" << std::setw(5) << "年龄" << std::setw(10) << "地址" << '\n';

    fout.close();

    std::unordered_set<long> unqualifiedCandidates;

    for (const long candidates : sims::StudentMIS::countMajorDegreeCandidates(this->majorAStd,
                                                                              getMajorAName(),
                                                                              this->getMajorAStudents()))
    {
        unqualifiedCandidates.insert(candidates);
    }

    for (const long candidates : sims::StudentMIS::countMajorDegreeCandidates(this->majorBStd,
                                                                              getMajorBName(),
                                                                              this->getMajorBStudents()))
    {
        unqualifiedCandidates.insert(candidates);
    }

    for (const long candidates : sims::StudentMIS::countMajorDegreeCandidates(this->majorCStd,
                                                                              getMajorCName(),
                                                                              this->getMajorCStudents()))
    {
        unqualifiedCandidates.insert(candidates);
    }

    fout.open("/proj/student-info-management-system/Data/Degree.DAT");
    fout << '\n'
         << "辅修学位获得学生：" << '\n';
    std::cout << '\n'
              << '\n'
              << std::setw(20) << " " << "辅修学位获得学生：" << '\n'
              << '\n';
    std::cout << std::left;
    std::cout << std::setw(8) << " " << std::setw(10) << "学号" << std::setw(10) << "姓名" << std::setw(10) << "辅修专业" << std::setw(5) << "性别" << std::setw(5) << "年龄" << std::setw(10) << "地址" << '\n';
    fout.close();

    sims::StudentMIS::countMinorDegreeCandidates(this->minorAStd,
                                                 getMajorAName(),
                                                 unqualifiedCandidates,
                                                 this->getMinorAStudents());

    sims::StudentMIS::countMinorDegreeCandidates(this->minorBStd,
                                                 getMajorBName(),
                                                 unqualifiedCandidates,
                                                 this->getMinorBStudents());
    sims::StudentMIS::countMinorDegreeCandidates(this->minorCStd,
                                                 getMajorCName(),
                                                 unqualifiedCandidates,
                                                 this->getMinorCStudents());

    fout.open("/proj/student-info-management-system/Data/Degree.DAT");
    fout << '\n'
         << "不能获得主修学位学生：" << '\n';
    std::cout << '\n'
              << '\n'
              << std::setw(20) << " " << "不能获得主修学位学生：" << '\n'
              << '\n';
    std::cout << std::left;
    std::cout << std::setw(8) << " " << std::setw(10) << "学号" << std::setw(10) << "姓名" << std::setw(5) << "性别" << std::setw(5) << "年龄" << std::setw(10) << "地址" << '\n';

    std::vector<long> uc;
    uc.reserve(unqualifiedCandidates.size());
    for (const long num : unqualifiedCandidates)
    {
        uc.push_back(num);
    }

    sims::Interface::showCandidates("", uc, this->getStudents(), this->getNumToIdx());
    fout.close();
    sims::Interface::enter0ToGoBack();
}

std::vector<long> sims::StudentMIS::countMajorDegreeCandidates(const int                            majorStd,
                                                               const std::string&                   majorName,
                                                               const std::vector<sims::DepStudent>& majorStudents)
{
    std::vector<long> unqualifiedCandidates;
    std::vector<long> candidates;

    for (const sims::DepStudent& ds : majorStudents)
    {
        int cnt = 0;
        for (const int score : ds.scores)
        {
            if (score >= 60)
            {
                cnt++;
            }
        }

        if (cnt >= majorStd)
        {
            candidates.push_back(ds.number);
        }
        else
        {
            unqualifiedCandidates.push_back(ds.number);
        }
    }

    sims::Interface::showCandidates(majorName, candidates, this->getStudents(), this->getNumToIdx());

    return unqualifiedCandidates;
}

void sims::StudentMIS::countMinorDegreeCandidates(const int                            minorStd,
                                                  const std::string&                   majorName,
                                                  const std::unordered_set<long>&      unqualifiedCandidates,
                                                  const std::vector<sims::DepStudent>& minorStudents)
{
    std::vector<long> candidates;

    for (const sims::DepStudent& ds : minorStudents)
    {
        if (unqualifiedCandidates.find(ds.number) != unqualifiedCandidates.end())
        {
            continue;
        }

        int cnt = 0;
        for (int j : ds.scores)
        {
            if (j >= 60)
            {
                cnt++;
            }
        }

        if (cnt >= minorStd)
        {
            candidates.push_back(ds.number);
        }
    }

    sims::Interface::showCandidates(majorName, candidates, this->getStudents(), this->getNumToIdx());
}