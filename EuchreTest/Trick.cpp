/*
 This is the Trick Class
 Tyler Rose
 Sep-23-2016
 */

#include <cassert>
#include <iostream>
#include <vector>

#include "Trick.h"

using namespace std;

Trick::Trick()
{
	m_winner = Owner::InPlay;
}

Suit Trick::GetLeadSuit() const
{
	return m_leadSuit;
}

Owner Trick::GetLeadPlayer() const
{
	return m_leadPlayer;
}

Suit Trick::GetTrump() const
{
	return m_trump;
}

void Trick::SetLeadSuit(Suit suit)
{
	m_leadSuit = suit;
}

void Trick::SetLeadPlayer(Owner owner)
{
	m_leadPlayer = owner;
	m_winner = Owner::InPlay;
}

void Trick::SetCard(Card card)
{
	// don't set owner so we can declare the winner card.SetOwner(Owner::InPlay);
	m_trick.push_back(card);
}

void Trick::SetTrump(Suit suit)
{
	m_trump = suit;
}

void Trick::PrintTrick()
{
	for (auto iter : m_trick)
		cout << iter.ValueToString() << " of " << iter.SuitToString() << " from " << iter.OwnerToString() << endl;
}

void Trick::Evaluate(Deck deck)
{
	//TODO: factor in left and right bar take presidence
	PrintTrick();
	//TODO: fix this assertion
	//assert(m_trick.size() > 2 && m_trick.size() < 4);
	cout << endl;
	Card Highest = m_trick.at(0);
	if(m_trump != Suit::High && m_trump != Suit::Low)
	{
		//look for left bar
		Suit left;
		switch(m_trump)
		{
			case Hearts:
			{
				left = Suit::Diamonds;
				break;
			}
			case Spades:
			{
				left = Suit::Clubs;
				break;
			}
			case Diamonds:
			{
				left = Suit::Hearts;
				break;
			}
			case Clubs:
			{
				left = Suit::Spades;
				break;
			}
		}
		
		
		for (int i = 1; i < m_trick.size(); i++)
		{
			//decide if the current card is the left bar
			bool isLeft = false;
			if(m_trick[i].GetValue() == Value::Jack && m_trick[i].GetSuit() == left)
				isLeft = true;
			
			//decide if the current card is the right bar
			bool isRight = false;
			if(m_trick[i].GetValue() == Value::Jack && m_trick[i].GetSuit() == m_trump)
				isRight = true;
			
			//for non trump find highest
			if(m_trick.at(i).GetSuit() == Highest.GetSuit() && Highest.GetSuit() != m_trump && !isLeft)
				if(m_trick.at(i).GetValue() > Highest.GetValue())
					Highest = m_trick.at(i);
			
			//for trump
			//need this check in case not followed suit and not trump
			if(m_trick.at(i).GetSuit() == m_trump || isLeft)
			{
				if(Highest.GetSuit() != m_trump || isLeft)
					Highest = m_trick.at(i);
				//This is for trump vs trump decisions
				else
				{
					if(isRight)
						Highest = m_trick[i];
					else if(isLeft && Highest.GetValue() != Value::Jack)
						Highest = m_trick[i];
					else if(m_trick.at(i).GetValue() > Highest.GetValue() && Highest.GetValue() != Value::Jack)
						Highest = m_trick.at(i);
				}
			}
		}
	}
	else if(m_trump != Suit::Low)
	{
		for (int i = 1; i < m_trick.size(); i++)
		{
			if(m_trick[i].GetSuit() == Highest.GetSuit())
				if(m_trick[i].GetValue() > Highest.GetValue())
					Highest = m_trick[i];
		}
	}
	else
	{
		for (int i = 1; i < m_trick.size(); i++)
		{
			if(m_trick[i].GetSuit() == Highest.GetSuit())
				if(m_trick[i].GetValue() < Highest.GetValue())
					Highest = m_trick[i];
		}
	}
	m_winner = Highest.GetOwner();
	cout << Highest.OwnerToString() << " is the winner with a " << 		Highest.ValueToString() << " of " << Highest.SuitToString() << endl;
	ReturnCards(deck);
}

Owner Trick::GetWinner() const
{
	return m_winner;
}

void Trick::ReturnCards(Deck deck)
{
	for (int i = m_trick.size()-1; i >= 0; i--)
	{
		Card temp = m_trick.at(i);
		m_trick.pop_back();
		deck.ReturnCard(temp);
	}
}
