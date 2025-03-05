#include "Staff.h"
#include "Student.h"
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

void sims::Staff::showStartMenu(const bool isFirstTime,
                                const bool hasErrorBefore)
{
    if (isFirstTime == true)
    {
        std::cout << '\n'
                  << std::setw(20) << " " << std::left << std::setw(30) << "欢迎进入学生信息管理系统！\n\n";
    }
    else
    {
        system("clear");
    }

    std::cout << '\n'
              << '\n'
              << std::setw(18) << " " << std::left << std::setw(20) << "1.用户选择" << std::setw(30) << "2.退出系统" << '\n';

    hasErrorBefore == true ? std::cout << '\n'
                                       << std::setw(20) << " " << "输入错误啦！重新选择吧："
                           : std::cout << '\n'
                                       << std::setw(25) << " " << "请选择：";
}

void sims::Staff::showLoginMenu(const bool hasErrorBefore)
{
    system("clear");
    std::cout << '\n'
              << '\n'
              << std::setw(22) << " " << std::left << std::setw(30) << "用户登录账号选择中..." << '\n';
    std::cout << '\n'
              << std::setw(15) << " " << std::left << std::setw(25) << "1.招生办工作人员" << "2.系教务员" << '\n';
    std::cout << '\n'
              << std::setw(15) << " " << std::left << std::setw(25) << "3.学位办工作人员" << "4.返回上一层" << '\n';

    hasErrorBefore == true ? std::cout << '\n'
                                       << std::setw(20) << " " << "输入错误啦！重新选择吧："
                           : std::cout << '\n'
                                       << std::setw(20) << " " << "请选择登录账号：";
}

void sims::Staff::showAdmissionsMenu(const bool hasErrorBefore)
{
    system("clear");
    std::cout << '\n'
              << '\n'
              << std::setw(25) << " " << std::left << std::setw(30) << "1.建立学生信息管理系统" << '\n';
    std::cout << '\n'
              << std::setw(25) << " " << std::left << std::setw(30) << "2.修改学生资料" << '\n';
    std::cout << '\n'
              << std::setw(25) << " " << std::left << std::setw(30) << "3.返回上一层" << '\n';

    hasErrorBefore == true ? std::cout << '\n'
                                       << std::setw(25) << " " << "输入错误啦！重新选择吧："
                           : std::cout << '\n'
                                       << std::setw(25) << " " << "请选择：";
}

void sims::Staff::operateAsAdmissionsStaff(sims::StudentMIS& sysu)
{
    sims::Staff::showAdmissionsMenu();

    std::string choice;
    while (std::cin >> choice)
    {
        if (choice.size() != 1 || choice[0] < '1' || choice[0] > '3')
        {
            system("clear");
            sims::Staff::showAdmissionsMenu(true);

            continue;
        }

        sims::StudentBase* pStudentBase = &sysu;
        if (choice == "1")
        {
            pStudentBase->loadBaseData();
        }
        else if (choice == "2")
        {
            pStudentBase->modifyData();
        }
        else
        {
            break;
        }

        sims::Staff::showAdmissionsMenu();
    }
}

void sims::Staff::showRegistrarSelect(const bool hasErrorBefore)
{
    system("clear");
    std::cout << '\n'
              << '\n'
              << std::setw(15) << " " << std::left << std::setw(25) << "1.A系教务员" << "2.B系教务员" << '\n';
    std::cout << '\n'
              << std::setw(15) << " " << std::left << std::setw(25) << "3.C系教务员" << "4.返回上一层" << '\n';
    hasErrorBefore == true ? std::cout << '\n'
                                       << std::setw(20) << " " << "输入错误啦！重新选择吧："
                           : std::cout << '\n'
                                       << std::setw(25) << " " << "请选择：";
}

void sims::Staff::operateAsRegistrar(sims::StudentMIS& sysu)
{
    sims::Staff::showRegistrarSelect();

    std::string choice;

    while (std::cin >> choice)
    {
        if (choice.size() != 1 || choice[0] < '1' || choice[0] > '4')
        {
            sims::Staff::showRegistrarSelect(true);

            continue;
        }

        if (choice == "1")
        {
            sims::DepA* pFirstA = &sysu;
            sims::Staff::operateAsDepARegistrar(pFirstA);
        }
        else if (choice == "2")
        {
            sims::DepB* pFirstB = &sysu;
            sims::Staff::operateAsDepBRegistrar(pFirstB);
        }
        else if (choice == "3")
        {
            sims::DepC* pFirstC = &sysu;
            sims::Staff::operateAsDepCRegistrar(pFirstC);
        }
        else
        {
            break;
        }

        sims::Staff::showRegistrarSelect();
    }
}

void sims::Staff::showRegistrarMenu(const bool hasErrorBefore)
{
    system("clear");
    std::cout << '\n'
              << '\n'
              << std::setw(15) << " " << std::left << std::setw(25) << "1.录入主修学生成绩" << "2.录入辅修学生成绩" << '\n';
    std::cout << '\n'
              << std::setw(15) << " " << std::left << std::setw(25) << "3.统计优秀学生" << "4.统计主修补考学生" << '\n';
    std::cout << '\n'
              << std::setw(15) << " " << std::left << std::setw(25) << "5.统计辅修补考学生" << "6.返回上一层" << '\n';
    hasErrorBefore == true ? std::cout << '\n'
                                       << std::setw(20) << " " << "输入错误啦！重新选择吧："
                           : std::cout << '\n'
                                       << std::setw(25) << " " << "请选择：";
}

void sims::Staff::operateAsDepARegistrar(sims::DepA* pFirstA)
{
    sims::Staff::showRegistrarMenu();
    std::string choice;
    while (std::cin >> choice)
    {
        if (choice.size() != 1 || choice[0] < '1' || choice[0] > '6')
        {
            sims::Staff::showRegistrarMenu(true);
        }
        if (choice == "1")
        {
            pFirstA->inputA_MajorScore();
        }
        else if (choice == "2")
        {
            pFirstA->inputA_SecondScore();
        }
        else if (choice == "3")
        {
            pFirstA->outputA_Good();
        }
        else if (choice == "4")
        {
            pFirstA->outputA_MajorFail();
        }
        else if (choice == "5")
        {
            pFirstA->outputA_SecondFail();
        }
        else
        {
            break;
        }
        sims::Staff::showRegistrarMenu();
    }
}

void sims::Staff::operateAsDepBRegistrar(sims::DepB* pFirstB)
{
    sims::Staff::showRegistrarMenu();
    std::string choice;
    while (std::cin >> choice)
    {
        if (choice.size() != 1 || choice[0] < '1' || choice[0] > '6')
        {
            sims::Staff::showRegistrarMenu(true);

            continue;
        }
        if (choice == "1")
        {
            pFirstB->inputB_MajorScore();
        }
        else if (choice == "2")
        {
            pFirstB->inputB_SecondScore();
        }
        else if (choice == "3")
        {
            pFirstB->outputB_Good();
        }
        else if (choice == "4")
        {
            pFirstB->outputB_MajorFail();
        }
        else if (choice == "5")
        {
            pFirstB->outputB_SecondFail();
        }
        else
        {
            break;
        }
        sims::Staff::showRegistrarMenu();
    }
}
void sims::Staff::operateAsDepCRegistrar(sims::DepC* pFirstC)
{
    sims::Staff::showRegistrarMenu();
    std::string choice;
    while (std::cin >> choice)
    {
        if (choice.size() != 1 || choice[0] < '1' || choice[0] > '6')
        {
            sims::Staff::showRegistrarMenu(true);

            continue;
        }
        if (choice == "1")
        {
            pFirstC->inputC_MajorScore();
        }
        else if (choice == "2")
        {
            pFirstC->inputC_SecondScore();
        }
        else if (choice == "3")
        {
            pFirstC->outputC_Good();
        }
        else if (choice == "4")
        {
            pFirstC->outputC_MajorFail();
        }
        else if (choice == "5")
        {
            pFirstC->outputC_SecondFail();
        }
        else
        {
            break;
        }

        sims::Staff::showRegistrarMenu();
    }
}

void sims::Staff::showDegreeMenu(const bool hasErrorBefore)
{
    system("clear");
    std::cout << '\n'
              << '\n'
              << std::setw(12) << " " << std::left << std::setw(30) << "1.设置主修学位需修课程数" << "2.设置辅修学位需修课程数" << '\n';
    std::cout << '\n'
              << std::setw(12) << " " << std::left << std::setw(30) << "3.统计相关学位信息" << "4.返回上一层" << '\n';
    hasErrorBefore == true ? std::cout << '\n'
                                       << std::setw(20) << " " << "输入错误啦！重新选择吧："
                           : std::cout << '\n'
                                       << std::setw(25) << " " << "请选择：";
}

void sims::Staff::operateAsDegreeStaff(sims::StudentMIS& sysu)
{
    sims::Staff::showDegreeMenu();
    std::string choice;
    while (std::cin >> choice)
    {
        if (choice.size() != 1 || choice[0] < '1' || choice[0] > '4')
        {
            sims::Staff::showDegreeMenu(true);
        }

        sims::StudentMIS* pStudentMIS = &sysu;

        if (choice == "1")
        {
            pStudentMIS->setMajorStandard();
        }
        else if (choice == "2")
        {
            pStudentMIS->setMinorStandard();
        }
        else if (choice == "3")
        {
            pStudentMIS->degree();
        }
        else
        {
            break;
        }

        sims::Staff::showDegreeMenu();
    }
}