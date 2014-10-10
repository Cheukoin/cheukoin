#ifndef __Cheuckoin_Score__
#define __Cheuckoin_Score__

#include "Bid.h"
#include "Trick.h"
#include "Team.h"

using namespace std;

class Score {
public:
    Score();
    ~Score();
    Bid getRetainedBid();
    int computeScore(Trick trick);
    Team computeWinner(Trick trick);
    void addOutcome(string equipe, int score);
    std::map<int, std::string> getOutcome();

private:
    Bid _retainedBid;
    Team _biddingTeam;
    std::map<int, std::string> _gameOutcome; // ensemble des pairs de pairs {équipe, score}
};

#endif