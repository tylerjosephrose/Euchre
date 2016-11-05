/*
 This is the AI Class
 Tyler Rose
 Oct 14-2016
 */

#ifndef AI_h
#define AI_h

#include "Game.h"

class AI
{
public:
	AI();
	void DeterminePlayableCards(Trick &trick, Player *player, vector<Card>& PlayableCards);
	void AIPlayCard(Trick &trick, Player *player);
	static AI* GetInstance();
private:
	static AI* m_aiInstance;
	
};

#endif // AI_h
