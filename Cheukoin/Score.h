#ifndef __Cheuckoin_Score__
#define __Cheuckoin_Score__

#include <iostream>

#include "Game.h"
#include "Trick.h"
#include "Rules.h"
#include "Application.h"

using namespace std;

class Score {
public:
    Score();
    ~Score();
    std::vector<int> getScores;
    int computeScore(Trick trick);
    Team computeWinner(Trick trick);
    void displayScore();
    void updateScore();

private:
};

#endif