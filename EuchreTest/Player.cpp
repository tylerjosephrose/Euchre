/*
		This is the Player clas
		Tyler Rose
		Sep-24-2016
*/

#include "AI.h"
#include <algorithm>
#include <iostream>
#include <vector>

#include "Player.h"

using namespace std;

static map<Suit, int> suits;

Player::Player(Owner player)
{
	m_whoami = player;
    myAI = new AI();
    suits[Hearts] = 4;
    suits[Spades] = 3;
    suits[Diamonds] = 2;
    suits[Clubs] = 1;
}

Player::~Player()
{
    delete myAI;
}

// returns int to show status. if 0 then it is valid play
int Player::PlayCard(int choice, Trick &trick)
{
	//Get the Card from the choice
	Card card = m_hand[choice-1];
	
	//Find left
	Suit left = trick.GetLeft();
	
	
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
	
	trick.SetCard(m_hand.at(choice - 1));
	//begin is zero element so we use begin + desired card - 1
	m_hand.erase(m_hand.begin() + choice - 1);
	return 0;
}

Card Player::GiveCard(int choice)
{
	Card temp = m_hand[choice-1];
	m_hand.erase(m_hand.begin() + choice - 1);
	return temp;
}

void Player::TakeCard(Card card, int choice)
{
	// be sure to set ownership to us now
	Card temp = m_hand[choice-1];
	m_hand.erase(m_hand.begin() + choice - 1);
	card.SetOwner(temp.GetOwner());
	Deck::GetInstance()->ReturnCard(temp);
	m_hand.push_back(card);
	
}

void Player::GetHand(Owner owner)
{
	//get 6 cards from the deck to by my hand for the round
	Deck* deck = Deck::GetInstance();
    for (int i = 0; i < 6; i++)
    {
		Card temp = deck->DrawCard();
        temp.SetOwner(owner);
        m_hand.push_back(temp);
    }
    SortHand();
    return;
}

void Player::SortHand(Suit trump)
{
    if(trump == High)
        sort(m_hand.begin(), m_hand.end(), CompareCards);
    else
    {
        // <Tyler Rose> 08-Dec-2016
        // Do fancy sort based on trump
        int preCompareValue = suits[trump];
        suits[trump] = 5;
        bool swapped;
        do
        {
            swapped = false;
            for (int i = 0; i < 5; i++)
            {
                if (CompareCardsTrump(m_hand[i+1], m_hand[i], trump))
                {
                    Card temp = m_hand[i];
                    m_hand[i] = m_hand[i + 1];
                    m_hand[i + 1] = temp;
                    swapped = true;
                }
            }
        } while (swapped);
        suits[trump] = preCompareValue;
    }
}

bool Player::CompareCardsTrump(Card &c1, Card &c2, Suit trump)
{
    
    // Suit left = Trick::GetLeft(trump);
    Card rightBar = Card(Jack, trump);
    Card leftBar = Card(Jack, Trick::GetLeft(trump));
    // Not the same suit and not dealing with left bar
    if (c1.GetSuit() != c2.GetSuit())
    {
        if (!(c1 == leftBar || c2 == leftBar))
            return suits[c1.GetSuit()] > suits[c2.GetSuit()];
    }
    if (c1 == rightBar)
        return true;
    else if (c2 == rightBar)
        return false;
    if (c1 == leftBar)
        return true;
    if (c2 == leftBar)
        return false;
    return c1.GetValue() > c2.GetValue();
    //return true;
}

bool Player::CompareCards(Card &c1, Card &c2)
{
	// Returns true if the first card is greater than the second card
	// Sorts by suit first (hearts, spades, diamonds, clubs) then by value
	if(c1.GetSuit() != c2.GetSuit())
	{
		return c1.GetSuit() > c2.GetSuit();
	}
	else
		return c1.GetValue() > c2.GetValue();
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
