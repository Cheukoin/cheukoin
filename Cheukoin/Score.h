#pragma once
#include "Bid.h"
#include "Trick.h"
#include <vector>
#include <string>

class Score {
public:
    Score();
    ~Score();
    Bid getRetainedBid();
    void computeScore(Trick trick);
    void addOutcome(std::string equipe, int score);
    std::vector<std::pair<int, std::string> > getOutcome();

private:
    Bid m_retainedBid;
    std::vector<std::pair<int, std::string> > m_gameOutcome; // ensemble des pairs de pairs {équipe, score}
};
