/* 		This is the main function to run Euchre
		Created by Tyler Rose
		Sep-22-2016
*/

#include <iostream>
#include "Game.h"

bool Windows = false;
#ifdef _WIN32
	Windows = true;
#endif

using namespace std;

void PrintHands(vector<Player> &players);

int main()
{
	Deck deck = Deck();
	deck.Shuffle();
	//deck.PrintDeck();

	Player Player1(Owner::Player_1), Player2(Owner::Player_2), Player3(Owner::Player_3), Player4(Owner::Player_4);
	
	vector<Player*> Players;
	Players.push_back(&Player1);
	Players.push_back(&Player2);
	Players.push_back(&Player3);
	Players.push_back(&Player4);
	
	
	Round round1(Owner::Player_1);
	round1.PlayRound(deck, Players);
	/*
	Player1.GetHand(deck, Owner::Player_1);
	Player2.GetHand(deck, Owner::Player_2);
	Player3.GetHand(deck, Owner::Player_3);
	Player4.GetHand(deck, Owner::Player_4);
	vector<Player> players;
	players.push_back(Player1);
	players.push_back(Player2);
	players.push_back(Player3);
	players.push_back(Player4);
	PrintHands(players);
	
	cin.get();
	
	Trick trick1;
    Player1.PlayCard(1, trick1);
	Player2.PlayCard(2, trick1);
	Player3.PlayCard(3, trick1);
	Player4.PlayCard(4, trick1);
	
	//trick1.PrintTrick();
	
	vector<Player> players2;
	players2.push_back(Player1);
	players2.push_back(Player2);
	players2.push_back(Player3);
	players2.push_back(Player4);
	PrintHands(players2);
	
	trick1.Evaluate(deck);
	
	deck.PrintDeck();
	*/
	if(Windows)
    	cin.get();
	return 0;
}

void PrintHands(vector<Player> &players )
{
    for (int i = 0; i < 4; i++)
	{
		cout << "This is Player " << i+1 << "'s hand:\n";
		players.at(i).PrintHand();
		cout << endl;
	}
}