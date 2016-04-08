
/*
			DEV103 Thermonuclear Wars
			by Joseph Khanh Dat Ho, ID #107089
			Qantm College Melbourne


			GAME CONDITIONS:
			Max Width: 16, Max Height: 10
			Max Cities (per side): 15
			Radar per 5 turns
			numNukes = numCities + 5
			if --numCities, --numNukes
			C for non-nuked cities, * for nuked cities
			Endgame, output order of nuked cities
			Score based on population of city (randomised)


			BONUS MARKS:
			DYNAMIC ARRAYYYYYYAYAYAYAY
			IMPLEMENT FSTREAM


			ACS TO-DO LIST:
			•	Players can specify max number of cities per side for each game.
			•	Player can specify the size of the game board (grid) at run-time.

			•	Grid within code stores pointers to the memory location of a dynamically allocated City object.

			•	User can specify board size on the command line or via prompted input.
*/

#include "Game.h"

int main()
{
	Game myGame;

	myGame.PlayTheGame();
	
	return 0;
}