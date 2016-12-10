/*
 This is the AI Class
 Tyler Rose
 Oct-14-2016
 */

#include "AI.h"
#include <algorithm>

using namespace std;

AI::AI()
{
	
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

Card AI::DetermineBestCard(Trick &trick, Player *player, vector<Card>& PlayableCards)
{
    // This does NOT look at the cards played already to find the best match!!!
    // This is also heavily dependent on the hand being sorted according to trump

    // Find trump and left
    Suit trump = trick.GetTrump();
    Suit left = trick.GetLeft();

    // If no choices then play the card
    if (PlayableCards.size() == 1)
        return PlayableCards[0];

    // Leading and it is the first hand or leading and not the bidder
    if (trick.GetLeadPlayer() == player->WhoAmI() && (player->m_hand.size() == 6 || trick.GetBidder() != player->WhoAmI()))
    {
        // <Tyler Rose> 07-Dec-2016
        // Hold on to one card in case player is leading with all trump but no right bar
        Card temp = PlayableCards[0];
        for (unsigned int i = 0; i < PlayableCards.size(); i++)
        {
            if (PlayableCards[i].GetSuit() == trump && PlayableCards[i].GetValue() == Jack)
                return PlayableCards[i];
            if (PlayableCards[i].GetSuit() == trump || (PlayableCards[i].GetSuit() == left && PlayableCards[i].GetValue() == Jack))
            {
                PlayableCards.erase(PlayableCards.begin() + i);
                continue;
            }
            if (PlayableCards[i].GetValue() == Ace)
            {
                return PlayableCards[i];
            }
        }
        if (PlayableCards.size() == 0)
        {
            return temp;
        }
        else
        {
            // <Tyler Rose> 07-Dec-2016
            // If there are no good cards then just play a random card left
            random_shuffle(PlayableCards.begin(), PlayableCards.end());
            return PlayableCards[0];
        }
    }

    // Leading and bidder
    else if (trick.GetLeadPlayer() == player->WhoAmI() && trick.GetBidder() == player->WhoAmI())
    {
        // Dependent on Sort by trump
        for (unsigned int i = 0; i < PlayableCards.size(); i++)
        {
            if (PlayableCards[i].GetSuit() == trump || (PlayableCards[i].GetSuit() == left && PlayableCards[i].GetValue() == Jack))
                return PlayableCards[i];
            if (PlayableCards[i].GetValue() == Ace)
                return PlayableCards[i];
        }
        // No trump or aces left so lets throw something out there and bank on our partner!
        return PlayableCards[0];
    }

     // Not leading (don't see any reason to distinguish between bidder and non bidder in this case)
    else// if (trick.GetBidder() == player->WhoAmI())
    {
        if (trick.GetLeadSuit() != trump)
        {
            Card trumpCard;
            for (auto iter : PlayableCards)
            {
                if (iter.GetSuit() == trump)
                    trumpCard = iter;
                if (iter.GetSuit() == trick.GetLeadSuit() && iter.GetValue() == Ace)
                    return iter;
            }
            if (trumpCard.GetSuit() == trump)
                return trumpCard;
            else
                return PlayableCards[PlayableCards.size() - 1];
        }
        else
        {
            if (PlayableCards[0].GetSuit() == trump)
                return PlayableCards[0];
            else
                return PlayableCards[PlayableCards.size() - 1];
        }
    }
}

void AI::AIPlayCard(Trick &trick, Player *player)
{
	vector<Card> PlayableCards;
	DeterminePlayableCards(trick, player, PlayableCards);

    //initially just pick one of the playable cards (no logic yet)
    Card toPlay = DetermineBestCard(trick, player, PlayableCards);
	trick.SetCard(toPlay);

	//erase the played card
    int cardnum = -1;
    for (auto iter : player->m_hand)
    {
        cardnum++;
        Card test(1, 1);
        if(iter == toPlay)
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
	player->WhoAmI() == (trick.GetLeadPlayer() + 3) % 4 && currentBid == 2 ? forceBid = true : forceBid = false;
	
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
	if(highest > 88)
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
	else if(highest > 75)
	{
		// TODO: bid 5 in bestSuit
		if(currentBid < 5)
			currentBid = 5;
	}
	else if(highest > 62)
	{
		// TODO: bid 4 in bestSuit
		if(currentBid < 4)
			currentBid = 4;
	}
	else if(highest > 55 || forceBid)
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
	for (int i = 1; i < 5; i++)
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
				continue;
			}
			// If card is in suit of right
			if(iter.GetSuit() == right)
			{
				if(iter.GetValue() == Jack)
				{
					score += 40;
					continue;
				}
				else if(iter.GetValue() == Ace)
				{
					score += 10;
					continue;
				}
				else if(iter.GetValue() == King)
				{
					score += 9;
					continue;
				}
				else if(iter.GetValue() == Queen)
				{
					score += 8;
					continue;
				}
				else if (iter.GetValue() == Ten)
				{
					score += 7;
					continue;
				}
				else if(iter.GetValue() == Nine)
				{
					score += 6;
					continue;
				}
				else
					cout << "Error occurred. Should never have uncaught right suit" << endl;
			}
			else if(iter.GetValue() == Ace)
			{
				score += 5;
				continue;
			}
		}
		m_bidScoring[right] = score;
	}
	
	// Score the hand on high
    if (GameSettings::GetAllowHigh())
    {
        int score = 0;
        if (trick.GetLeadPlayer() == player->WhoAmI())
            score += 10;

        vector<Suit> Aces;
        vector<Suit> AceKings;

        for (auto iter : player->m_hand)
        {
            if (iter.GetValue() == Ace)
            {
                score += 20;
                Aces.push_back(iter.GetSuit());
                break;
            }
            else if (iter.GetValue() == King)
            {
                score += 10;
                if (find(Aces.begin(), Aces.end(), iter.GetSuit()) != Aces.end())
                {
                    score += 5;
                    AceKings.push_back(iter.GetSuit());
                }
                break;
            }
            else if (iter.GetValue() == Queen)
            {
                score += 2;
                if (find(AceKings.begin(), AceKings.end(), iter.GetSuit()) != AceKings.end())
                    score += 5;
                break;
            }
        }
        m_bidScoring[High] = score;
    }
	
	// Score the hand on low
    if (GameSettings::GetAllowLow())
    {
        //int score = 0;
    }
}

void AI::AIFinalizeBid(Trick &trick, Player *player)
{
	trick.SetTrump(m_bestSuit);
}

Card AI::AIPassCard(Trick &trick, Player *player)
{
	vector<Card> trumpCards;
	vector<Card> offAces;
	for(auto card: player->m_hand)
	{
		Suit left = Trick::GetLeft(trick.GetTrump());
		if(card.GetValue() == Jack && (card.GetSuit() == trick.GetTrump() || left))
		{
			Card temp = card;
			CleanupHand(player);
			return temp;
		}
		if(card.GetSuit() == trick.GetTrump())
			trumpCards.push_back(card);
        if (card.GetValue() == Ace && card.GetSuit() != trick.GetTrump())
            offAces.push_back(card);
	}
    if (trumpCards.size() > 0)
    {
        Card temp = trumpCards[0];
        CleanupHand(player);
        return temp;
    }
    else if (offAces.size() > 0)
    {
        Card temp = offAces[0];
        CleanupHand(player);
        return temp;
    }
    else
    {
        Card temp = player->m_hand[0];
        CleanupHand(player);
        return temp;
    }
}

void AI::AITakeCard(Trick &trick, Player *player, Card card)
{
    int cardnum = -1;
    int lastCard = 0;
    Suit left = trick.GetLeft();
    vector<Card> possibilities;
    for (auto iter : player->m_hand)
    {
        cardnum++;
        if (iter.GetSuit() != trick.GetTrump() || !(iter.GetSuit() == left && iter.GetValue() == Jack) || iter.GetValue() != Ace)
        {
            possibilities.push_back(iter);
            lastCard = cardnum;
        }
    }

    Card temp;
    if (possibilities.size() > 0)
    {
        temp = possibilities[possibilities.size() - 1];
        player->m_hand.erase(player->m_hand.begin() + lastCard);
        card.SetOwner(temp.GetOwner());
        Deck::GetInstance()->ReturnCard(temp);
        player->m_hand.push_back(card);
    }
    else
    {
        temp = player->m_hand[player->m_hand.size() - 1];
        player->m_hand.erase(player->m_hand.begin() + 5);
        card.SetOwner(temp.GetOwner());
        Deck::GetInstance()->ReturnCard(temp);
        player->m_hand.push_back(card);
    }
}
				
void AI::CleanupHand(Player *player)
{
	while(player->m_hand.size() > 0)
	{
		Card temp = player->m_hand[0];
		player->m_hand.erase(player->m_hand.begin());
		Deck::GetInstance()->ReturnCard(temp);
	}
}
