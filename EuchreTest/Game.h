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

class Game
{
public:
	Game();
	int GetScore();
	
private:
	int m_teamOneScore;
	int m_teamTwoScore;
};

#endif