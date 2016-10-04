#ifndef ROUND_H
#define ROUND_H

/*
This is the Round Class
Tyler Rose
Sep-23-2016
*/

#include "Deck.h"
#include "Player.h"

class Round
{
public:
	Round(Owner LeadPlayer);
	void PlayRound(Deck deck, vector<Player*> Players);
	void PlayTrick(vector<Player*> Players);
	void SetScore();
	void PrintHands(vector<Player*> Players);
	
private:
	int AskPlayCard(Trick &trick, Player *player);
	Trick m_currentTrick;
};

#endif