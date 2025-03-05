#pragma once

namespace sims
{
class StudentMIS;
class DepA;
class DepB;
class DepC;

namespace Staff
{
    void showStartMenu(const bool isFirstTime    = false,
                       const bool hasErrorBefore = false);
    void showLoginMenu(const bool hasErrorBefore = false);

    void showAdmissionsMenu(const bool hasErrorBefore = false);
    void operateAsAdmissionsStaff(sims::StudentMIS& sysu);

    void showRegistrarSelect(const bool hasErrorBefore = false);
    void operateAsRegistrar(sims::StudentMIS& sysu);
    void showRegistrarMenu(const bool hasErrorBefore = false);
    void operateAsDepARegistrar(sims::DepA* pFirstA);
    void operateAsDepBRegistrar(sims::DepB* pFirstB);
    void operateAsDepCRegistrar(sims::DepC* pFirstC);

    void showDegreeMenu(const bool hasErrorBefore = false);
    void operateAsDegreeStaff(sims::StudentMIS& sysu);
} // namespace Staff
} // namespace sims