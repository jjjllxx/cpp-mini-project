#pragma once

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace sims
{
struct Student;
struct DepStudent;
struct DepStudent;

namespace Interface
{
    void        enter0ToGoBack();
    void        showAllStudents(const std::vector<sims::Student>& students);
    void        showModifyMenu(const bool hasErrorBefore = false);
    void        showModifyOption(const bool hasErrorBefore = false);
    std::size_t convertStudentNumber(const std::size_t  studentsSize,
                                     const std::string& idx);
    bool        isStudentInfoLoaded(const std::vector<sims::Student>& students);

    template<typename T>
    bool isScoreLoaded(const std::string& scoreName, const std::vector<T>& scores)
    {
        if (scores.empty() == true)
        {
            system("clear");
            std::cout << '\n'
                      << std::setw(18) << " " << scoreName << "成绩尚未录入！" << '\n';
            std::cout << '\n'
                      << std::setw(18) << " " << "请先录入成绩！" << '\n';
            sims::Interface::enter0ToGoBack();
            return false;
        }
        else
        {
            system("clear");
            std::cout << '\n'
                      << std::setw(18) << " " << scoreName << "成绩已录入！" << '\n';
            sims::Interface::enter0ToGoBack();
            return true;
        }
    }
    int setDegreeStandard(const std::string& degreeName);

    void loadMajorScore(const std::string&                dataPath,
                        const std::vector<sims::Student>& students,
                        std::vector<sims::DepStudent>&    majorStudents);

    void loadMinorScore(const std::string&                dataPath,
                        const std::vector<sims::Student>& students,
                        std::vector<sims::DepStudent>&    minorStudents);

    bool isGoodStudent(const std::vector<int>& scores);

    void countGoodStudents(const std::string&                   dataPath,
                           const std::vector<sims::Student>&    students,
                           const std::unordered_map<long, int>& numToIdx,
                           const std::vector<sims::DepStudent>& majorStudents,
                           const std::vector<sims::DepStudent>& minorStudents);

    void showScores(const std::string&      dataPath,
                    const sims::Student&    student,
                    const std::vector<int>& scores);

    void countFailure(const std::string&                   type,
                      const std::string&                   dataPath,
                      const std::vector<sims::Student>&    students,
                      const std::unordered_map<long, int>& numToIdx,
                      const std::vector<sims::DepStudent>& majorStudents);

    void showDegreeStandard(const int          aStandard,
                            const int          bStandard,
                            const int          cStandard,
                            const std::string& type);

    void showCandidates(const std::string&                   majorName,
                        const std::vector<long>&             candidates,
                        const std::vector<sims::Student>&    students,
                        const std::unordered_map<long, int>& numToIdx);

} // namespace Interface
} // namespace sims