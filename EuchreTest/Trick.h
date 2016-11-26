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
	Suit GetLeft() const;
	static Suit GetLeft(Suit suit);
	Owner GetWinner() const;
    void Evaluate();
	void SetLeadSuit(Suit suit);
	void SetLeadPlayer(Owner owner);
	void SetCard(Card card);
	void SetTrump(Suit suit);
	void PrintTrick();

private:
	void ReturnCards();
	
    vector<Card>m_trick;
	Suit m_leadSuit;
	Owner m_leadPlayer;
	Suit m_trump;
	Owner m_winner;
};

#endif
