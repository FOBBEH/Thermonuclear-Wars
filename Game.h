
#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
using namespace std;

#include "Grid.h"

class Game
{
public:
	// Game();
	// ~Game();

	bool			m_playerNukeHit;				// Determines whether player nuke has hit
	bool			m_enemyNukeHit;					// Determines whether enemy nuke has hit
	bool			m_enemyTurn;
	bool			m_radarActive;

	bool			m_beauModeNukeA;				// Determines whether Beau Mode nukes have hit
	bool			m_beauModeNukeB;
	bool			m_beauModeNukeC;

	string			m_username;						// Name the player types in
	int				m_turns;						// Current turns of the player
	int				m_numNukes;						// Number of nukes for the player

	int				m_enterRadarX;					// Co-ordinates for radar
	int				m_enterRadarY;
	int				m_radarHit[13];					// Array to activate the radar
	int				m_enterX;						// Co-ordinates for nuke
	int				m_enterY;

	int				m_playerScore;					// Score totals
	int				m_enemyScore;
	
	vector<string>	m_cityList;						// Store a list of cities
	vector<string>	m_playerDestroyedCityList;		// Store and output cities destroyed
	vector<string>	m_enemyDestroyedCityList;
	vector<int>		m_playerPopList;				// Store and output populations
	vector<int>		m_enemyPopList;

	void			PlayTheGame();					// Play the entire damn game!

	void			DirtyRender();					// Draw over screen instead of refreshing				(alternate to system("CLS"))
	void			DisplayTitle();					// Display title screen	at the top
	
	void			UseRadar();						// Use the radar to reveal space on the grid
	void			EnterXForRadar();				// Enter the co-ordinates for the radar
	void			EnterYForRadar();
	void			ResetRadar();					// Reset all the values so radar only lasts one turn
	void			CheckInput();					// Incase a non-integer value is typed in				(set to 0)
	
	void			EnterXForNuke();				// Enter the co-ordinates for the nuke
	void			EnterYForNuke();
	void			ConfirmPlayerNuke();			// Confirm whether the nukes have hit or missed
	void			ConfirmEnemyNuke();
	void			ConfirmBeauModeNuke();
	
	void			CheckNumberOfNukes();			// Check if nukes are still available to launch
	void			CheckWinner();					// Determine the winner

	string			GenerateCity(int x);			// Generate a random city when called
	int				GeneratePopulation(int x);		// Generate a random population when called

	Grid			m_createGrid;					// Generate the grid									(access grid variables, functions, etc.)

private:
};

// COLOURED TEXT!
#define		ColourDRed		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 132)	// BG Black		TXT Red
#define		ColourRMagenta	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 197)	// BG Red		TXT Magenta
#define		ColourWMagenta	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 223)	// BG Magenta	TXT White

#endif // GAME_H