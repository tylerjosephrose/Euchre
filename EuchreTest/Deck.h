#ifndef DECK_H
#define DECK_H

/*
		This is the Deck Class
		Tyler Rose
		Sep-22-2016
*/

#include <string>
#include <vector>

#include "Card.h"

using namespace std;

//Class for the Deck Structure
class Deck
{
public:
	//default constructor
	Deck();
	void Shuffle();
	Card DrawCard();
	void ReturnCard(Card card);
	void PrintDeck();
	
private:
	vector<Card> m_cards;
};


#endif