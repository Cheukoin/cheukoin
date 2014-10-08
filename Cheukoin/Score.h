#pragma once
#include "Trick.h"
#include "Team.h"
#include <vector>
#include <string>
#include <map>

class Score {
public:
<<<<<<< HEAD
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
    
=======
    Score();
    ~Score();
    Bid getRetainedBid();
    void computeScore(Trick trick);
    void addOutcome(std::string equipe, int score);
    std::vector<std::pair<int, std::string> > getOutcome();

private:
    Bid m_retainedBid;
    std::vector<std::pair<int, std::string> > m_gameOutcome; // ensemble des pairs de pairs {équipe, score}
>>>>>>> master
};
