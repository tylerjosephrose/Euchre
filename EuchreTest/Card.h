#ifndef CARD_H
#define CARD_H

/*
		This is the Card Class
		Tyler Rose
		Sep-22-2016
*/

#include <string>

using namespace std;

enum Value { Nine = 9, Ten = 10, Jack = 11, Queen = 12, King = 13, Ace = 14 };
enum Suit { Hearts = 4, Diamonds = 2, Spades = 3, Clubs = 1, High = 5, Low = 6 };
enum Owner { Player_1 = 0, Player_2 = 1, Player_3 = 2, Player_4 = 3, MainDeck = 4, InPlay = 5 };

// Class for the Card Structure
class Card
{
public:
	//Constructor
	Card(int value, int suit);
	
	Value GetValue() const;
	Suit GetSuit() const;
	Owner GetOwner() const;
	string ValueToString() const;
	string SuitToString() const;
	string OwnerToString() const;
    void SetOwner(Owner owner);

    bool operator==(const Card& rhs)
    {
        if (m_suit == rhs.GetSuit() && m_value == rhs.GetValue() && m_owner == rhs.GetOwner())
            return true;
        else
            return false;
    }
	
private:
	Value m_value;
	Suit m_suit;
	Owner m_owner;
};

string SuitToString(Suit suit);
string OwnerToString(Owner owner);


#endif
