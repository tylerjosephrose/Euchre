/*
 This is the AI Class
 Tyler Rose
 Oct 14-2016
 */

#ifndef AI_h
#define AI_h

#include "Game.h"

#include <map>

class AI
{
public:
	AI();
	void DeterminePlayableCards(Trick &trick, Player *player, vector<Card>& PlayableCards);
	void AIBid(Trick &trick, Player *player, int &currentBid);
	void BidScoring(Trick &trick, Player *player);
	void AIPlayCard(Trick &trick, Player *player);
	void AIFinalizeBid(Trick &trick, Player *player);
	Card AIPassCard(Trick &trick, Player *player);
	void CleanupHand(Player *player);
	//static AI* GetInstance();
private:
	//static AI* m_aiInstance;
	std::map<Suit, int> m_bidScoring;
	Suit m_bestSuit;
};

#endif // AI_h
