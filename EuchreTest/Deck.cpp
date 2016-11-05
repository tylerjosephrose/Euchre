/*
		This is the Deck Class
		Tyler Rose
		Sep-22-2016
*/

#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <cassert>

#include "Deck.h"

using namespace std;

Deck* Deck::m_deckInstance = 0;

Deck::Deck()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 9; j < 15; j++)
		{
			m_cards.push_back(Card(j, i));
		}
	}
}

Deck* Deck::GetInstance()
{
	if (!m_deckInstance)
		m_deckInstance = new Deck();
	
	return m_deckInstance;
}

void Deck::Shuffle()
{
	random_device rd;
	mt19937 g(rd());
	shuffle(m_cards.begin(), m_cards.end(), g);
	shuffle(m_cards.begin(), m_cards.end(), g);
}

void Deck::PrintDeck()
{
    for (auto iter: m_cards)
		cout << iter.ValueToString() << " of " << iter.SuitToString() << endl;
}

Card Deck::DrawCard()
{
    assert(m_cards.size() != 0);
    Card temp = m_cards.at(m_cards.size()-1);
    m_cards.pop_back();
	return temp;
}

void Deck::ReturnCard(Card card)
{
	m_cards.push_back(card);
}

int Deck::DeckSize() const
{
	return (int)m_cards.size();
}
