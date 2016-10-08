#ifndef TRICK_H
#define TRICK_H

/*
This is the Trick Class
Tyler Rose
Sep-23-2016
*/

#include <iostream>
#include <vector>

#include "Deck.h"

class Trick
{
public:
    Trick();
    Suit GetLeadSuit() const;
    Owner GetLeadPlayer() const;
	Suit GetTrump() const;
	Owner GetWinner() const;
    void Evaluate(Deck &deck);
	void SetLeadSuit(Suit suit);
	void SetLeadPlayer(Owner owner);
	void SetCard(Card card);
	void SetTrump(Suit suit);
	void PrintTrick();

private:
	void ReturnCards(Deck &deck);
	
    vector<Card>m_trick;
	Suit m_leadSuit;
	Owner m_leadPlayer;
	Suit m_trump;
	Owner m_winner;
};

#endif
