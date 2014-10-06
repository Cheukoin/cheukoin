#pragma once
#include "Bid.h"
#include "Trick.h"
#include <vector>
#include <string>

using namespace std;

class Score
{
public:
	Score();
	~Score();
	Bid getRetainedBid(); 
	void computeScore(Trick trick);
	void addOutcome(string equipe, int score);
	vector<string, int> getOutcome();

private:
	Bid m_retainedBid; 
	vector<string, int> m_gameOutcome; // ensemble des pairs de pairs {équipe, score}
};

