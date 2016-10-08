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
public:
	Player(Owner player);
	int PlayCard(int choice, Trick &trick);
	Card GiveCard(int choice);
	void TakeCard(Card card, int choice, Deck &deck);
	void GetHand(Deck &deck, Owner owner);
	void PrintHand() const;
	Owner WhoAmI() const;
	
private:
	vector<Card>m_hand;
	Owner m_whoami;
};

#endif
