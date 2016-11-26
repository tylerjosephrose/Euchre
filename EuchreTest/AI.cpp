/*
 This is the AI Class
 Tyler Rose
 Oct-14-2016
 */

#include "AI.h"

using namespace std;

//AI* AI::m_aiInstance = 0;

AI::AI()
{
	
}

/*AI* AI::GetInstance()
{
	if(!m_aiInstance)
		m_aiInstance = new AI();
	return m_aiInstance;
}*/

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

void AI::AIBid(Trick &trick, Player *player, int &currentBid)
{
	// Bidding for the AI will work by scoring the hand based on each suit. A given score will result in the bid amount and the suit picked or no pick.
	m_bidScoring.clear();
	BidScoring(trick, player);
	
	// Is this the last player with no current bid?
	bool forceBid;
	player->WhoAmI() == (trick.GetLeadPlayer() - 1) % 4 && currentBid == 2 ? forceBid = true : forceBid = false;
	
	int highest = 0;
	if(m_bidScoring.size() > 6)
		cout << "Map should not have more than 6 choices" << endl;
	
	for(auto iter: m_bidScoring)
	{
		if(iter.second > highest)
		{
			highest = iter.second;
			m_bestSuit = iter.first;
		}
	}
	// Needs to check if last to bid and force bid
	if(highest > 89)
	{
		// TODO: call loner in bestSuit
		if(currentBid < 8)
			currentBid = 8;
	}
	else if(highest > 80)
	{
		// TODO: call shoot in bestSuit
		if(currentBid < 7)
			currentBid = 7;
	}
	else if(highest > 70)
	{
		// TODO: bid 5 in bestSuit
		if(currentBid < 5)
			currentBid = 5;
	}
	else if(highest > 60)
	{
		// TODO: bid 4 in bestSuit
		if(currentBid < 4)
			currentBid = 4;
	}
	else if(highest > 50 || forceBid)
	{
		// TODO: bid 3 in bestSuit
		if(currentBid < 3)
			currentBid = 3;
	}
	else
	{
		// TODO: pass
		return;
	}
}

void AI::BidScoring(Trick &trick, Player *player)
{
	// Score the hand on each suit
	for (int i = 0; i < 4; i++)
	{
		int score = 0;
		Suit right = (Suit) i;
		Suit left = Trick::GetLeft(right);
		for (auto iter: player->m_hand)
		{
			// Card is left bar
			if(iter.GetSuit() == left && iter.GetValue() == Jack)
			{
				score += 20;
				break;
			}
			// If card is in suit of right
			if(iter.GetSuit() == right)
			{
				if(iter.GetValue() == Jack)
				{
					score += 40;
					break;
				}
				else if(iter.GetValue() == Ace)
				{
					score += 10;
					break;
				}
				else if(iter.GetValue() == King)
				{
					score += 9;
					break;
				}
				else if(iter.GetValue() == Queen)
				{
					score += 8;
					break;
				}
				else if (iter.GetValue() == Ten)
				{
					score += 7;
					break;
				}
				else if(iter.GetValue() == Nine)
				{
					score += 6;
					break;
				}
				else
					cout << "Error occurred. Should never have uncaught right suit" << endl;
			}
			else if(iter.GetValue() == Ace)
			{
				score += 5;
				break;
			}
		}
		m_bidScoring[right] = score;
	}
}

void AI::AIFinalizeBid(Trick &trick, Player *player)
{
	trick.SetTrump(m_bestSuit);
}
