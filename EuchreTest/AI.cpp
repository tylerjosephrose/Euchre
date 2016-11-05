/*
 This is the AI Class
 Tyler Rose
 Oct-14-2016
 */

#include "AI.h"

using namespace std;

AI* AI::m_aiInstance = 0;

AI::AI()
{
	
}

AI* AI::GetInstance()
{
	if(!m_aiInstance)
		m_aiInstance = new AI();
	return m_aiInstance;
}

void AI::DeterminePlayableCards(Trick &trick, Player *player, vector<Card>& PlayableCards)
{
	//Find left
	Suit left = trick.GetLeft();
	
	//logic for if the card is valid
	if(trick.GetLeadPlayer() != player->m_whoami)
	{
		for(auto iter: player->m_hand)
		{
			if(iter.GetSuit() == trick.GetLeadSuit() && !(iter.GetSuit() == left && iter.GetValue() == Value::Jack))
			{
				PlayableCards.push_back(iter);
			}
			//if this card is the left bar and lead is trump
			if(trick.GetLeadSuit() == trick.GetTrump() && (iter.GetSuit() == left && iter.GetValue() == Value::Jack))
			{
				PlayableCards.push_back(iter);
			}
		}
		if(PlayableCards.size() == 0)
			for( auto iter: player->m_hand )
				PlayableCards.push_back(iter);
	}
	else
	{
        for (auto iter : player->m_hand)
        {
            PlayableCards.push_back(iter);
        }
	}
}

void AI::AIPlayCard(Trick &trick, Player *player)
{
	vector<Card> PlayableCards;
	DeterminePlayableCards(trick, player, PlayableCards);
    //initially just pick one of the playable cards (no logic yet)
	trick.SetCard(PlayableCards[0]);
	//erase the played card
    int cardnum = -1;
    for (auto iter : player->m_hand)
    {
        cardnum++;
        Card test(1, 1);
        if(iter == PlayableCards[0])
		{
            player->m_hand.erase(player->m_hand.begin() + cardnum);
			break;
		}
    }
}
