#ifndef ROUND_H
#define ROUND_H

/*
This is the Round Class
Tyler Rose
Sep-23-2016
*/

#include "AI.h"
#include "Deck.h"
#include "Player.h"

class AI;

class Round
{
public:
	Round(Owner LeadPlayer);
	~Round();
	void PlayRound(vector<Player*> Players, vector<int> &Points);
	void PlayTrick(vector<Player*> Players);
    void GetBids(vector<Player*> Players);
    void FinalizeBid(int playerBid, vector<Player*> Players);
	void SetScore(int team1Tricks, int team2Tricks, vector<int> &Points);
	
private:
	int AskPlayCard(Trick &trick, Player *player);
	void SetUpShoot(vector<Player*> Players);
	void PlayTrickLone(vector<Player*> Players);
	Trick m_currentTrick;
    int m_teamBid;
	int m_bidAmount;
	int m_currentBid;
	int m_playerBid;
	vector<AI*> Computers;
};

#endif
