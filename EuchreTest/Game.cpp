/*
 This is the Game Class
 Tyler Rose
 Oct-08-2016
 */

#include "Game.h"
#include <ctime>

using namespace std;

Game::Game()
{
	
}

void Game::PlayGame()
{
	Player Player1(Owner::Player_1), Player2(Owner::Player_2), Player3(Owner::Player_3), Player4(Owner::Player_4);
	
	vector<Player*> Players;
	Players.push_back(&Player1);
	Players.push_back(&Player2);
	Players.push_back(&Player3);
	Players.push_back(&Player4);
	
	m_teamOneScore = 0;
	m_teamTwoScore = 0;
	
	//Pick the player to lead
	srand((uint)time(NULL));
	int lead = (rand() % 4) + 1;
	
	//typically 32
	int WinningScore = 32;
	int numOfRounds = 0;
	while(m_teamOneScore < WinningScore && m_teamTwoScore < WinningScore)
	{
		numOfRounds++;
		Deck::GetInstance()->Shuffle();
		cout << "Round " << numOfRounds << endl;
		Round round(static_cast<Owner>((lead + numOfRounds) % 4));
		vector<int> Points = {0, 0};
		round.PlayRound(Players, Points);
		SetScore(Points);
		PrintScore();
	}
}

void Game::PrintScore() const
{
	//This will print out the score
	cout << "\nTeam 1: " << m_teamOneScore << endl;
	cout << "Team 2: " << m_teamTwoScore << endl;
}

void Game::SetScore(vector<int> &Points)
{
	m_teamOneScore = m_teamOneScore + Points[0];
	m_teamTwoScore = m_teamTwoScore + Points[1];
}
