/*
This is the Round Class
Tyler Rose
Sep-23-2016
*/

#include "Round.h"

using namespace std;

Round::Round(Owner LeadPlayer)
{
	m_currentTrick.SetLeadPlayer(LeadPlayer);
}

void Round::PlayRound(Deck deck, vector<Player*> Players)
{
	//TODO: Figure out bids and trump
	Players[0]->GetHand(deck, Owner::Player_1);
	Players[1]->GetHand(deck, Owner::Player_2);
	Players[2]->GetHand(deck, Owner::Player_3);
	Players[3]->GetHand(deck, Owner::Player_4);
	//PrintHands(Players);
	
	int Team13Tricks = 0;
	int Team24Tricks = 0;
	
	m_currentTrick.SetTrump(Suit::Hearts);
	
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