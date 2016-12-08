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

Owner Trick::GetBidder() const
{
    return m_bidder;
}

Suit Trick::GetTrump() const
{
	return m_trump;
}

Suit Trick::GetLeft() const
{
	switch(m_trump)
	{
		case Hearts:
			return Suit::Diamonds;
		case Spades:
			return Suit::Clubs;
		case Diamonds:
			return Suit::Hearts;
		case Clubs:
			return Suit::Spades;
		case High:
			return Suit::High;
		case Low:
			return Suit::Low;
	}
}

Suit Trick::GetLeft(Suit suit)
{
	switch(suit)
	{
		case Hearts:
			return Suit::Diamonds;
		case Spades:
			return Suit::Clubs;
		case Diamonds:
			return Suit::Hearts;
		case Clubs:
			return Suit::Spades;
		case High:
			return Suit::High;
		case Low:
			return Suit::Low;
	}
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
	// if this is the first card laid then we need to set it as the lead suit
	if(m_trick.size() == 1)
	{
		if(card.GetValue() == Value::Jack && card.GetSuit() == GetLeft())
			SetLeadSuit(m_trump);
		else
			SetLeadSuit(card.GetSuit());
	}
}

void Trick::SetTrump(Suit suit)
{
	m_trump = suit;
}

void Trick::SetBidder(Owner owner)
{
    m_bidder = owner;
}

void Trick::PrintTrick()
{
	for (auto iter : m_trick)
		cout << iter.ValueToString() << " of " << iter.SuitToString() << " from " << iter.OwnerToString() << endl;
}

void Trick::Evaluate()
{
	PrintTrick();
	//TODO: fix this assertion
	assert(m_trick.size() > 2 && m_trick.size() < 4);
	cout << endl;
	Card Highest = m_trick.at(0);
	if(Highest.GetSuit() == m_trump && Highest.GetValue() == Value::Jack)
	{
		m_winner = Highest.GetOwner();
		cout << Highest.OwnerToString() << " is the winner with a " << 		Highest.ValueToString() << " of " << Highest.SuitToString() << endl;
		ReturnCards();
		return;
	}
	if(m_trump != Suit::High && m_trump != Suit::Low)
	{
		//look for left bar
		Suit left = GetLeft();
		
		for (unsigned int i = 1; i < m_trick.size(); i++)
		{
			if(m_trick[i].GetValue() == Value::Jack && m_trick[i].GetSuit() == m_trump)
			{
				Highest = m_trick[i];
				m_winner = Highest.GetOwner();
				cout << Highest.OwnerToString() << " is the winner with a " << 		Highest.ValueToString() << " of " << Highest.SuitToString() << endl;
				ReturnCards();
				return;
			}
			
			//decide if the current card is the left bar
			bool isLeft = false;
			if(m_trick[i].GetValue() == Value::Jack && m_trick[i].GetSuit() == left)
				isLeft = true;
			
			//for non trump find highest
			if(m_trick.at(i).GetSuit() == Highest.GetSuit() && Highest.GetSuit() != m_trump && !isLeft && !(Highest.GetValue() == Jack && Highest.GetSuit() == left))
				if(m_trick.at(i).GetValue() > Highest.GetValue())
					Highest = m_trick.at(i);
			
			//for trump
			//need this check in case not followed suit and not trump
			if(m_trick.at(i).GetSuit() == m_trump || isLeft)
			{
				if(Highest.GetSuit() != m_trump && !(Highest.GetSuit() == left && Highest.GetValue() == Value::Jack))
					Highest = m_trick.at(i);
				//This is for trump vs trump decisions
				else
				{
					if(isLeft && Highest.GetValue() != Value::Jack)
						Highest = m_trick[i];
					else if(m_trick.at(i).GetValue() > Highest.GetValue() && Highest.GetValue() != Value::Jack)
						Highest = m_trick.at(i);
				}
			}
		}
	}
	else if(m_trump != Suit::Low)
	{
		for (unsigned int i = 1; i < m_trick.size(); i++)
		{
			if(m_trick[i].GetSuit() == Highest.GetSuit())
				if(m_trick[i].GetValue() > Highest.GetValue())
					Highest = m_trick[i];
		}
	}
	else
	{
		for (unsigned int i = 1; i < m_trick.size(); i++)
		{
			if(m_trick[i].GetSuit() == Highest.GetSuit())
				if(m_trick[i].GetValue() < Highest.GetValue())
					Highest = m_trick[i];
		}
	}
	m_winner = Highest.GetOwner();
	cout << Highest.OwnerToString() << " is the winner with a " << 		Highest.ValueToString() << " of " << Highest.SuitToString() << endl;
	ReturnCards();
}

Owner Trick::GetWinner() const
{
	return m_winner;
}

void Trick::ReturnCards()
{
	Deck* deck = Deck::GetInstance();
	for (int i = (int)m_trick.size()-1; i >= 0; i--)
	{
		Card temp = m_trick.at(i);
		m_trick.pop_back();
		deck->ReturnCard(temp);
	}
}
