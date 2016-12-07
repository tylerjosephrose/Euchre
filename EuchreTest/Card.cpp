/*
		This is the Card Class
		Tyler Rose
		Sep-22-2016
*/

#include <iostream>
#include <string>

#include "Card.h"

using namespace std;

Card::Card()
{

}

Card::Card(int value, int suit)
{
	
	m_value = static_cast<Value>(value);
	m_suit = static_cast<Suit>(suit);
	m_owner = Owner::MainDeck;
}

Value Card::GetValue() const
{
	return m_value;
}

Suit Card::GetSuit() const
{
	return m_suit;
}

Owner Card::GetOwner() const
{
	return m_owner;
}

void Card::SetOwner(Owner owner)
{
	m_owner = owner;
}

string Card::ValueToString() const
{
	switch(static_cast<int>(m_value))
	{
		case 9:    return "9";
		case 10:     return "10";
		case 11:    return "J";
		case 12:   return "Q";
		case 13:    return "K";
		case 14:     return "A";
	}
	return "Not a Card!! Uh Oh!";
}

string Card::SuitToString() const
{
	switch(m_suit)
	{
		case Hearts:       return "Hearts";
		case Spades:       return "Spades";
		case Diamonds:     return "Diamonds";
		case Clubs:        return "Clubs";
		case High:         return "High";
		case Low:          return "Low";
	}
    return "Not a Card!! Uh Oh!";
}

string SuitToString(Suit suit)
{
	switch(suit)
	{
		case Hearts:       return "Hearts";
		case Spades:       return "Spades";
		case Diamonds:     return "Diamonds";
		case Clubs:        return "Clubs";
		case High:         return "High";
		case Low:          return "Low";
	}
	return "Not a Card!! Uh Oh!";
}

string Card::OwnerToString() const
{
	switch(m_owner)
	{
		case Player_1:    return "Player 1";
	    case Player_2:    return "Player 2";
		case Player_3:    return "Player 3";
		case Player_4:    return "Player 4";
		case MainDeck:    return "Main Deck";
		case InPlay:      return "In Play";
	}
}

string OwnerToString(Owner owner)
{
	switch(owner)
	{
		case Player_1:    return "Player 1";
		case Player_2:    return "Player 2";
		case Player_3:    return "Player 3";
		case Player_4:    return "Player 4";
		case MainDeck:    return "Main Deck";
		case InPlay:      return "In Play";
	}
}