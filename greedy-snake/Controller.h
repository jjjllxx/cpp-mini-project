#pragma once

namespace gs
{
class Controller
{
public:
    void init();
    void selectMode();
    void drawGame() const;
    bool playGame();
    void updateScore(const int coef);
    void rewriteScore() const;
    int  showMenu();
    void gameLoop();
    bool endGame() const;

private:
    int interval = 200;

    int mode  = 1;
    int score = 0;
};
} // namespace gs
