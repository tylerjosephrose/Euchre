/*
This is the Round Class
Tyler Rose
Sep-23-2016
*/

#include "StringCompare.h"

#include "Round.h"

using namespace std;

//A new Round will need created each time so we set the LeadPlayer Properly (To be done in Game.cpp)
Round::Round(Owner LeadPlayer)
{
	m_currentTrick.SetLeadPlayer(LeadPlayer);
    m_teamBid = 0;
}

void Round::PlayRound(Deck &deck, vector<Player*> Players)
{
	Players[0]->GetHand(deck, Owner::Player_1);
	Players[1]->GetHand(deck, Owner::Player_2);
	Players[2]->GetHand(deck, Owner::Player_3);
	Players[3]->GetHand(deck, Owner::Player_4);
	//PrintHands(Players);

    GetBids(Players);
	
	int Team13Tricks = 0;
	int Team24Tricks = 0;
	
	//TODO: SetUpShoot and PlayTrickLone
	if(m_bidAmount == 7)
		SetUpShoot(Players, deck);
	if(m_bidAmount > 6)
	{
		for(int i = 0; i < 6; i++)
		{
			if(m_currentTrick.GetWinner() != Owner::InPlay)
				m_currentTrick.SetLeadPlayer(m_currentTrick.GetWinner());
			
			//remove player who is not in
			Players.erase(Players.begin() + ((m_playerBid + 2)%4));
			
			PlayTrickLone(Players);
			
			m_currentTrick.Evaluate(deck);
			if(m_currentTrick.GetWinner() == Owner::Player_1 || m_currentTrick.GetWinner() == Owner::Player_3)
				Team13Tricks++;
			else
				Team24Tricks++;
		}
	}
	
	//m_currentTrick.SetTrump(Suit::Hearts);
	
	for(int i = 0; i < 6; i++)
	{
		if(m_currentTrick.GetWinner() != Owner::InPlay)
			m_currentTrick.SetLeadPlayer(m_currentTrick.GetWinner());
		
		PlayTrick(Players);
		
		m_currentTrick.Evaluate(deck);
		if(m_currentTrick.GetWinner() == Owner::Player_1 || m_currentTrick.GetWinner() == Owner::Player_3)
			Team13Tricks++;
		else
			Team24Tricks++;
	}
	
	cout << "The Round is over with the scores:\nTeam13: " << Team13Tricks << "\nTeam24: " << Team24Tricks << endl;
	
	//TODO: Set the score
}

void Round::GetBids(vector<Player*> Players)
{
    int lead = m_currentTrick.GetLeadPlayer();
    //7 is shoot and 8 is alone
    int bid = 2;
    int player;
    for (int i = 0; i < 4; i++)
    {
        //stay in this loop if it was an invalid bid
        int j = 0;
        do
        {
			//Print current bidding info
            if (bid == 2)
                cout << "There is no current bid" << endl;
            else
                cout << "The current bid is: " << bid << endl;
            cout << OwnerToString(Players[(lead + i) % 4]->WhoAmI()) << ", place a bid. (enter 0 to pass)" << endl;
            cout << "Options are 3, 4, 5, 6, shoot, alone" << endl;
			//Print hand of player up
            Players[(lead + i) % 4]->PrintHand();
            string propose;
            cin >> propose;
			
			//not bidding and not the last player to go with no previous bid
            if (icompare(propose, "0") && i != 3)
                break;
			//not bidding and is the last player with no previous bid
            if (icompare(propose, "0") && i == 3 && bid == 2)
            {
                cout << "You are last and no one has made a bid. You must bid" << endl;
				bid = 3;
                j = 1;
            }
			//not bidding and last player but there is already a bid
			if (icompare(propose, "0") && i == 3)
				break;
            if (icompare(propose, "alone"))
            {
                bid = 8;
                FinalizeBid((lead + i) % 4);
                return;
            }
            else if (icompare(propose, "shoot"))
            {
                bid = 7;
                player = (lead + i) % 4;
            }
            else if (atoi(propose.c_str()) > bid)
            {
				if (atoi(propose.c_str()) > 8)
				{
					cout << "This is not a valid bid" << endl;
					j = 1;
				}
				else
				{
					bid = atoi(propose.c_str());
					player = (lead + i) % 4;
				}
            }
            else if (atoi(propose.c_str()) < bid)
            {
                cout << "You did not bid high enough" << endl;
                j = 1;
            }
        } while (j == 1);
    }
	m_playerBid = player;
	m_bidAmount = bid;
    FinalizeBid(player);
}

void Round::FinalizeBid(int playerBid)
{
    //Highest bidder choses their suit here
    switch (playerBid)
    {
    case 0:     m_teamBid = 1;
    case 1:     m_teamBid = 2;
    case 2:     m_teamBid = 1;
    case 3:     m_teamBid = 2;
    }

    string input;
    cout << "Player " << playerBid + 1 << ", What Suit do you want?" << endl;
    cin >> input;
    
    if (icompare(input, "Hearts"))
        m_currentTrick.SetTrump(Suit::Hearts);
    if (icompare(input, "Diamonds"))
        m_currentTrick.SetTrump(Suit::Diamonds);
    if (icompare(input, "Spades"))
        m_currentTrick.SetTrump(Suit::Spades);
    if (icompare(input, "Clubs"))
        m_currentTrick.SetTrump(Suit::Clubs);
    if (icompare(input, "High"))
        m_currentTrick.SetTrump(Suit::High);
    if (icompare(input, "Low"))
        m_currentTrick.SetTrump(Suit::Low);
}

void Round::PlayTrick(vector<Player*> Players)
{
	int lead = m_currentTrick.GetLeadPlayer();
	for(int i = 0; i < 4; i++)
	{
		int good = 1;
		cout << "This is  " << OwnerToString(Players[(lead+i)%4]->WhoAmI()) << endl;
		while (good == 1)
		{
			good = AskPlayCard(m_currentTrick, Players[(lead+i)%4]);
		}
	}
}

void Round::PlayTrickLone(vector<Player*> Players)
{
	//TODO: Wrong player gets to go after bid
	m_playerBid;
	
	int lead = m_currentTrick.GetLeadPlayer();
	for(int i = 0; i < 3; i++)
	{
		int good = 1;
		cout << "This is  " << OwnerToString(Players[(lead+i)%3]->WhoAmI()) << endl;
		while (good == 1)
		{
			good = AskPlayCard(m_currentTrick, Players[(lead+i)%3]);
		}
	}
}

int Round::AskPlayCard(Trick &trick, Player *player)
{
	cout << "Trump is " << SuitToString(trick.GetTrump()) << endl;
	cout << "The cards played so far are:\n";
	trick.PrintTrick();
	cout << "\nPick what card number you want to play\n";
	player->PrintHand();
	int choice;
	cin >> choice;
	int result = player->PlayCard(choice, trick);
	if(result == 1)
	{
		cout << "Did not follow Lead Suit of " << SuitToString(trick.GetLeadSuit()) << endl;
		return 1;
	}
	return 0;
}

void Round::SetUpShoot(vector<Player*> Players, Deck deck)
{
	cout << "Player " << m_playerBid + 3 << ", your teammate is shooting it in " << SuitToString(m_currentTrick.GetTrump()) << endl;
	cout << "What card will you give them?\n";
	Players[m_playerBid+2]->PrintHand();
	int choice;
	cin >> choice;
	Card temp = Players[m_playerBid+2]->GiveCard(choice);
	cout << "Player " << m_playerBid + 1 << ", your teammate is giving you the " << temp.ValueToString() << " of " << temp.SuitToString() << endl;
	cout << "What card will you discard for it?\n";
	Players[m_playerBid]->PrintHand();
	cin >> choice;
	Players[m_playerBid]->TakeCard(temp, choice, deck);
	
	//return the other Players hand to the deck
	for (int i = 0; i < 5; i++)
	{
		Card temp = Players[m_playerBid+2]->GiveCard(1);
		deck.ReturnCard(temp);
		Players[m_playerBid+2]->PrintHand();
	}
}

void Round::SetScore()
{
	//TODO
}

void Round::PrintHands(vector<Player*> players)
{
    for (int i = 0; i < 4; i++)
	{
		cout << "This is Player " << i+1 << "'s hand:\n";
		players[i]->PrintHand();
		cout << endl;
	}
}