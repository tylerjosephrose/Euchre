/*
This is the Round Class
Tyler Rose
Sep-23-2016
*/

#include "AI.h"
#include "StringCompare.h"
#include "Round.h"

using namespace std;

//A new Round will need created each time so we set the LeadPlayer Properly (To be done in Game.cpp)
Round::Round(Owner LeadPlayer)
{
	m_currentTrick.SetLeadPlayer(LeadPlayer);
    m_teamBid = 0;
}
Round::~Round()
{

}

void Round::PlayRound(vector<Player*> Players, vector<int> &Points)
{
	Players[0]->GetHand(Owner::Player_1);
	Players[1]->GetHand(Owner::Player_2);
	Players[2]->GetHand(Owner::Player_3);
	Players[3]->GetHand(Owner::Player_4);

    GetBids(Players);
	
	int Team1Tricks = 0;
	int Team2Tricks = 0;
	
	//SetUpShoot and PlayTrickLone
	if(m_bidAmount == 7)
		SetUpShoot(Players);
	if(m_bidAmount > 6)
	{
		for(int i = 0; i < 6; i++)
		{
			if(m_currentTrick.GetWinner() != Owner::InPlay)
				m_currentTrick.SetLeadPlayer(m_currentTrick.GetWinner());
			
			PlayTrickLone(Players);
			
			m_currentTrick.Evaluate();
			if(m_currentTrick.GetWinner() == Owner::Player_1 || m_currentTrick.GetWinner() == Owner::Player_3)
				Team1Tricks++;
			else
				Team2Tricks++;
		}
	}
	else
	{
		for(int i = 0; i < 6; i++)
		{
			if(m_currentTrick.GetWinner() != Owner::InPlay)
				m_currentTrick.SetLeadPlayer(m_currentTrick.GetWinner());
			
			PlayTrick(Players);
			
			m_currentTrick.Evaluate();
			if(m_currentTrick.GetWinner() == Owner::Player_1 || m_currentTrick.GetWinner() == Owner::Player_3)
				Team1Tricks++;
			else
				Team2Tricks++;
		}
	}
	
	SetScore(Team1Tricks, Team2Tricks, Points);
}

void Round::GetBids(vector<Player*> Players)
{
    int lead = m_currentTrick.GetLeadPlayer();
    //7 is shoot and 8 is alone
    m_currentBid = 2;
    int playerUp;
    int player = (lead - 1) % 4;
    for (int i = 0; i < 4; i++)
    {
        playerUp = (lead + i) % 4;
        //stay in this loop if it was an invalid bid
        int j = 1;
		if(playerUp != 0)
		{
			int temp = m_currentBid;
			Players[playerUp]->myAI->AIBid(m_currentTrick, Players[playerUp], m_currentBid);
			if(m_currentBid == 8)
			{
				FinalizeBid(playerUp, Players);
				break;
			}
			if(temp != m_currentBid)
				player = playerUp;
			j = 0;
		}
        while(j == 1)
        {
			//Print current bidding info
            if (m_currentBid == 2)
                cout << "There is no current bid" << endl;
            else
                cout << "The current bid is: " << m_currentBid << " by Player " << (m_playerBid + 1) % 4 << endl;
            cout << OwnerToString(Players[playerUp]->WhoAmI()) << ", place a bid. (enter 0 to pass)" << endl;
            cout << "Options are 3, 4, 5, 6, shoot, alone" << endl;
			//Print hand of player up
            Players[playerUp]->PrintHand();
            string propose;
            cin >> propose;
			
			//not bidding and not the last player to go with no previous bid
            if (icompare(propose, "0") && i != 3)
			{
				j = 0;
                break;
			}
			//not bidding and is the last player with no previous bid
            if (icompare(propose, "0") && i == 3 && m_currentBid == 2)
            {
                cout << "You are last and no one has made a bid. You must bid" << endl;
				m_currentBid = 3;
                j = 1;
            }
			//not bidding and last player but there is already a bid
			if (icompare(propose, "0") && i == 3)
			{
				j = 0;
				break;
			}
            if (icompare(propose, "alone"))
            {
                m_currentBid = 8;
				player = playerUp;
				m_playerBid = player;
				m_bidAmount = m_currentBid;
				FinalizeBid(player, Players);
                return;
            }
            else if (icompare(propose, "shoot"))
            {
				j = 0;
                m_currentBid = 7;
                player = playerUp;
            }
            else if (atoi(propose.c_str()) > m_currentBid)
            {
				if (atoi(propose.c_str()) > 8)
				{
					cout << "This is not a valid bid" << endl;
					j = 1;
				}
				else
				{
					j = 0;
					m_currentBid = atoi(propose.c_str());
					player = playerUp;
				}
            }
            else if (atoi(propose.c_str()) < m_currentBid)
            {
                cout << "You did not bid high enough" << endl;
                j = 1;
            }
        }
    }
	m_playerBid = player;
	m_bidAmount = m_currentBid;
    FinalizeBid(player, Players);
}

void Round::FinalizeBid(int playerBid, vector<Player*> Players)
{
    //Highest bidder choses their suit here
    switch (playerBid)
    {
    case 0:
		{
			m_teamBid = 1;
			break;
		}
    case 1:
		{
			m_teamBid = 2;
			break;
		}
    case 2:
		{
			m_teamBid = 1;
			break;
		}
    case 3:
		{
			m_teamBid = 2;
			break;
		}
    }
	
	if(playerBid != 0)
	{
		Players[playerBid]->myAI->AIFinalizeBid(m_currentTrick, Players[playerBid]);
        return;
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
        int playerUp = (lead + i) % 4;
		int good = 1;
		//cout << "This is  " << OwnerToString(Players[(lead+i)%4]->WhoAmI()) << endl;
        if (playerUp != 0)
        {
			Players[playerUp]->myAI->AIPlayCard(m_currentTrick, Players[playerUp]);
        }
		else
		{
			while (good == 1)
			{
				good = AskPlayCard(m_currentTrick, Players[playerUp]);
			}
		}
	}
}

void Round::PlayTrickLone(vector<Player*> Players)
{
	// <Tyler Rose> 07-Dec-2016
    //Now all 4 players are passed in and skip the player if his partner is the one going alone
	
	int lead = m_currentTrick.GetLeadPlayer();
	
	for(int i = 0; i < 4; i++)
	{
        int playerUp = (lead + i) % 4;
        if (playerUp == (m_playerBid + 2) % 4)
            continue;
		int good = 1;
		cout << "This is  " << OwnerToString(Players[playerUp]->WhoAmI()) << endl;
		if (playerUp != 0)
		{
			Players[playerUp]->myAI->AIPlayCard(m_currentTrick, Players[playerUp]);
		}
		else
		{
			while (good == 1)
			{
				good = AskPlayCard(m_currentTrick, Players[playerUp]);
			}
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

void Round::SetUpShoot(vector<Player*> Players)
{
	int givingPlayer = (m_playerBid + 2) % 4;
    Card temp;
    if (givingPlayer != 0)
    {
        temp = Players[givingPlayer]->myAI->AIPassCard(m_currentTrick, Players[givingPlayer]);
    }
    else
    {
        cout << "Your teammate is shooting it in " << SuitToString(m_currentTrick.GetTrump()) << endl;
        cout << "What card will you give them?\n";
        Players[0]->PrintHand();
        int choice;
        cin >> choice;
        temp = Players[0]->GiveCard(choice);
    }

    // This part is for recieving the card
    // TODO: Allow AI to recieve a card if they shoot it
	cout << "Player " << m_playerBid + 1 << ", your teammate is giving you the " << temp.ValueToString() << " of " << temp.SuitToString() << endl;
	cout << "What card will you discard for it?\n";
	Players[m_playerBid]->PrintHand();
    int choice;
	cin >> choice;
	Players[m_playerBid]->TakeCard(temp, choice);
    Players[m_playerBid]->SortHand();
	
	//return the other Players hand to the deck
    if (givingPlayer == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            Card temp = Players[(m_playerBid + 2) % 4]->GiveCard(1);
            Deck::GetInstance()->ReturnCard(temp);
            //Players[(m_playerBid+2) % 4]->PrintHand();
        }
    }
}

void Round::SetScore(int team1Tricks, int team2Tricks, vector<int> &Points)
{
	//Loner
	if(m_bidAmount == 8)
	{
		if(m_teamBid == 1 && team1Tricks < 6)
		{
			Points[0] = -12;
			Points[1] = team2Tricks;
			return;
		}
		else if(m_teamBid == 2 && team2Tricks < 6)
		{
			Points[0] = team1Tricks;
			Points[1] = -12;
			return;
		}
		else if(m_teamBid == 1)
		{
			Points[0] = 12;
			return;
		}
		else
		{
			Points[1] = 12;
			return;
		}
	}
	
	//shoot
	if(m_bidAmount == 7)
	{
		if(m_teamBid == 1 && team1Tricks < 6)
		{
			Points[0] = -8;
			Points[1] = team2Tricks;
			return;
		}
		else if(m_teamBid == 2 && team2Tricks < 6)
		{
			Points[0] = team1Tricks;
			Points[1] = -8;
			return;
		}
		else if(m_teamBid == 1)
		{
			Points[0] = 8;
			return;
		}
		else
		{
			Points[1] = 8;
			return;
		}
	}
	
	//team1 fails bid
	if(m_teamBid == 1 && m_bidAmount > team1Tricks)
	{
		Points[0] = m_bidAmount*-1;
		Points[1] = team2Tricks;
		return;
	}
	
	//team2 fails bid
	else if(m_teamBid == 2 && m_bidAmount > team2Tricks)
	{
		Points[0] = team1Tricks;
		Points[1] = m_bidAmount*-1;
		return;
	}
	
	//either team completes the bid
	else
	{
		Points[0] = team1Tricks;
		Points[1] = team2Tricks;
		return;
	}
}
