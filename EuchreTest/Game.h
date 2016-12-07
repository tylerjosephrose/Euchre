#ifndef GAME_H
#define GAME_H

/*
		This is the Game Class
		Tyler Rose
		Sep-22-2016
*/

#include <iostream>
#include "Deck.h"
#include "Player.h"
#include "Trick.h"
#include "Round.h"

struct GameSettings
{
    friend class Game;

public:
    static bool GetAllowLow() { return m_allowLow; }
    static bool GetAllowHigh() { return m_allowHigh; }
    static bool GetScrewTheDealer() { return m_screwTheDealer; }

private:
    static bool m_allowLow;
    static bool m_allowHigh;
    static bool m_screwTheDealer;
    static void SetAllowLow(bool input) { m_allowLow = input; }
    static void SetAllowHigh(bool input) { m_allowHigh = input; }
    static void SetScrewTheDealer(bool input) { m_screwTheDealer = input; }
};

class Game
{
public:
	Game();
	void PlayGame();
	void PrintScore() const;
	void SetScore(vector<int> &Points);
	
private:
	int m_teamOneScore;
	int m_teamTwoScore;
};

#endif
