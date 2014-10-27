#ifndef __Cheuckoin_Score__
#define __Cheuckoin_Score__

#include <iostream>

#include "Game.h"
#include "Trick.h"
#include "Team.h"
#include "Rules.h"
#include "Application.h"

using namespace std;

class Score {
public:
    Score(Team const& team);
    ~Score();
    std::vector<int> getScores;
    int computeScore(Trick trick);
    Team computeWinner(Trick trick);
    void displayScore();
    void updateScore();

private:
    Team _biddingTeam;
    std::vector<int> _scores;
    sf::Sprite _scoreBoard;
};

#endif