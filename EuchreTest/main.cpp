/* 		This is the main function to run Euchre
		Created by Tyler Rose
		Sep-22-2016
*/

#include <iostream>
#include "Game.h"

//bool Windows = false;
//#ifdef _WIN32
//	Windows = true;
//#endif

using namespace std;

int main()
{
	Deck::GetInstance()->Shuffle();
	
	Game game = Game();
	game.PlayGame();

	//if(Windows)
    	cin.get();
	return 0;
}
