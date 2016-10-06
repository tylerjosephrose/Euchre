/*
		This is the Player clas
		Tyler Rose
		Sep-24-2016
*/

#include <iostream>
#include <vector>

#include "Player.h"

using namespace std;

Player::Player(Owner player)
{
	m_whoami = player;
}

// returns int to show status. if 0 then it is valid play
int Player::PlayCard(int choice, Trick &trick)
{
	//Get the Card from the choice
	Card card = m_hand[choice-1];
	
	//Find left
	Suit left;
	switch(trick.GetTrump())
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
		case High:
		{
			left = Suit::High;
			break;
		}
		case Low:
		{
			left = Suit::Low;
			break;
		}
	}
	
	//logic for if the card is valid
	if(trick.GetLeadPlayer() != m_whoami)
	{
		bool CanFollowSuit = false;
		for(auto iter: m_hand)
		{
			if(iter.GetSuit() == trick.GetLeadSuit() && !(iter.GetSuit() == left && iter.GetValue() == Value::Jack))
			{
				CanFollowSuit = true;
				break;
			}
			//if this card is the left bar and lead is trump
			if(trick.GetLeadSuit() == trick.GetTrump() && (iter.GetSuit() == left && iter.GetValue() == Value::Jack))
			{
				CanFollowSuit = true;
				break;
			}
		}
	
	
		if(CanFollowSuit)
		{
			bool validCard = true;
			if(card.GetSuit() != trick.GetLeadSuit())
				validCard = false;
			if(trick.GetLeadSuit() != trick.GetTrump() && (card.GetSuit() == left && card.GetValue() == Value::Jack))
				validCard = false;
			if(trick.GetLeadSuit() == trick.GetTrump() && (card.GetSuit() == left && card.GetValue() == Value::Jack))
				validCard = true;
			if(!validCard)
				return 1;
		}
	}
	else
	{
		if(card.GetValue() == Value::Jack && card.GetSuit() == left)
			trick.SetLeadSuit(trick.GetTrump());
		else
			trick.SetLeadSuit(card.GetSuit());
	}
	
	trick.SetCard(m_hand.at(choice - 1));
	//begin is zero element so we use begin + desired card - 2
	m_hand.erase(m_hand.begin() + choice - 1);
	return 0;
}

Card Player::GiveCard(int choice)
{
	Card temp = m_hand[choice-1];
	m_hand.erase(m_hand.begin() + choice - 1);
	return temp;
}

void Player::TakeCard(Card card, int choice, Deck deck)
{
	//does not change owner since same team will still get point
	Card temp = m_hand[choice-1];
	m_hand.erase(m_hand.begin() + choice - 1);
	deck.ReturnCard(temp);
	m_hand.push_back(card);
	
}

void Player::GetHand(Deck &deck, Owner owner)
{
	//get 6 cards from the deck to by my hand for the round
    for (int i = 0; i < 6; i++)
    {
        Card temp = deck.DrawCard();
        temp.SetOwner(owner);
        m_hand.push_back(temp);
    }
    return;
}

Owner Player::WhoAmI() const
{
	return m_whoami;
}

void Player::PrintHand() const
{
	int i = 0;
	for (auto iter : m_hand)
	{
		i = i+1;
		cout << i << ": " << iter.ValueToString() << " of " << iter.SuitToString() << endl;
	}
}