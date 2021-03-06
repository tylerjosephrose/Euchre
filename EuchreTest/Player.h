#ifndef PLAYER_H
#define PLAYER_H

/*
		This is the Player Class
		Tyler Rose
		Sep-24-2016
*/

#include <vector>

#include "Deck.h"
#include "Trick.h"

using namespace std;

class Player
{
	friend class AI;
public:
	Player(Owner player);
	int PlayCard(int choice, Trick &trick);
	Card GiveCard(int choice);
	void TakeCard(Card card, int choice);
	void GetHand(Owner owner);
	void PrintHand() const;
	Owner WhoAmI() const;
	
	static bool CompareCards(Card &c1, Card &c2);
	
private:
	vector<Card>m_hand;
	Owner m_whoami;
};

#endif
