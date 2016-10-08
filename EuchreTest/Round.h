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
	void PlayRound(Deck &deck, vector<Player*> Players, vector<int> &Points);
	void PlayTrick(vector<Player*> Players);
    void GetBids(vector<Player*> Players);
    void FinalizeBid(int playerBid);
	void SetScore(int team1Tricks, int team2Tricks, vector<int> Points);
	void PrintHands(vector<Player*> Players);
	
private:
	int AskPlayCard(Trick &trick, Player *player);
	void SetUpShoot(vector<Player*> Players, Deck deck);
	void PlayTrickLone(vector<Player*> Players);
	Trick m_currentTrick;
    int m_teamBid;
	int m_bidAmount;
	int m_playerBid;
};

#endif
