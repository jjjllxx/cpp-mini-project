#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>

namespace sims
{
struct Student
{
    int  sex;
    int  age;
    long number;

    std::string name;
    std::string address;
    std::string major;
};

class StudentBase
{
private:
    std::unordered_map<long, int> numToIdx;
    std::vector<sims::Student>    students;

public:
    void loadBaseData();
    void modifyData();

    std::vector<sims::Student>    getStudents();
    std::unordered_map<long, int> getNumToIdx();
};

struct DepStudent
{
    long             number;
    std::string      major;
    std::vector<int> scores;
};

class DepA : virtual public StudentBase
{
private:
    std::string majorAName = "mmmmmm";

    std::vector<sims::DepStudent> majorStudents;
    std::vector<sims::DepStudent> minorStudents;

public:
    DepA() = default;
    void inputA_MajorScore();
    void inputA_SecondScore();
    void outputA_Good();
    void outputA_MajorFail();
    void outputA_SecondFail();

    std::string                   getMajorAName();
    std::vector<sims::DepStudent> getMajorAStudents();
    std::vector<sims::DepStudent> getMinorAStudents();
};

class DepB : virtual public StudentBase
{
private:
    std::string majorBName = "ffffff";

    std::vector<sims::DepStudent> majorStudents;
    std::vector<sims::DepStudent> minorStudents;

public:
    DepB() = default;
    void inputB_MajorScore();
    void inputB_SecondScore();
    void outputB_Good();
    void outputB_MajorFail();
    void outputB_SecondFail();

    std::string                   getMajorBName();
    std::vector<sims::DepStudent> getMajorBStudents();
    std::vector<sims::DepStudent> getMinorBStudents();
};

class DepC : virtual public StudentBase
{
private:
    std::string majorCName = "cccccc";

    std::vector<sims::DepStudent> majorStudents;
    std::vector<sims::DepStudent> minorStudents;

public:
    DepC() = default;

    void inputC_MajorScore();
    void inputC_SecondScore();
    void outputC_Good();
    void outputC_MajorFail();
    void outputC_SecondFail();

    std::string                   getMajorCName();
    std::vector<sims::DepStudent> getMajorCStudents();
    std::vector<sims::DepStudent> getMinorCStudents();
};

class StudentMIS : public DepA, public DepB, public DepC
{
private:
    int majorAStd, majorBStd, majorCStd;
    int minorAStd, minorBStd, minorCStd;

public:
    StudentMIS();
    void setMajorStandard();
    void setMinorStandard();
    void degree();

    std::vector<long> countMajorDegreeCandidates(const int                            majorStd,
                                                 const std::string&                   majorName,
                                                 const std::vector<sims::DepStudent>& majorStudents);

    void countMinorDegreeCandidates(const int                            minorStd,
                                    const std::string&                   majorName,
                                    const std::unordered_set<long>&      unqualifiedCandidates,
                                    const std::vector<sims::DepStudent>& minorStudents);
};
} // namespace sims
