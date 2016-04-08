
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <Windows.h>
using namespace std;

#include "Game.h"

/*Game::Game()
{
}

Game::~Game()
{
}*/

void Game::DirtyRender()
{
	COORD coord;
	coord.X = 0;
	coord.Y = m_createGrid.m_randomY + 11;	// 11 lines for the title and Y co-ordinates

	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );

	// Writes over all the text AFTER the title and grid
	for (int i = 0; i < 30; ++i)
	{
		cout << "                                                                      " << endl;
	}
	
	coord.X = 0;
	coord.Y = 0;

	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}

void Game::DisplayTitle()
{
	while (true)
	{
		if (m_username == "Beau")
		{
			ColourRMagenta;
			cout << "                                                                                "			;
			cout << "                       _                                              _  _      "			;
			cout << "      _  _  ___  _  _ ( )_ _  ___   ___ __  _ _  ___ __ __ __ ___  __| || |     "			;
			cout << "     | || |/ _ \\| || ||/| '_|/ -_) (_-</ _|| '_|/ -_)\\ V  V // -_)/ _` ||_|     "		;
			cout << "      \\_, |\\___/ \\_,_|  |_|  \\___| /__/\\__||_|  \\___| \\_/\\_/ \\___|\\__,_|(_)     ";
			cout << "      |__/                                                                      "			;
			cout << "                                                                                "			;
			cout << "                                                                                "			<< endl;
			break;
		}
		else if (m_username == "Faggot")
		{
			ColourWMagenta;
		}
		else
		{
			ColourDRed;
		}
		cout << "        ___       ___  __         __             __        ___       __         "       ;
		cout << "         |  |__| |__  |__)  |\\/| /  \\ |\\ | |  | /  ` |    |__   /\\  |__)        "   ;
		cout << "         |  |  | |___ |  \\  |  | \\__/ | \\| \\__/ \\__, |___ |___ /~~\\ |  \\        ";
		cout << "                                                                                "       ;
		cout << "                                        __   __                                 "       ;
		cout << "                             |  |  /\\  |__) /__`                                "      ;
		cout << "                             |/\\| /~~\\ |  \\ .__/                                "    ;
		cout << "                                                                                "       << endl;
		break;
	}
}

void Game::UseRadar()
{
	// Reveal spaces from the centre [0] outwards (diamond shaped)
	m_radarHit[0] = (m_enterRadarY * m_createGrid.m_randomX) + m_enterRadarX;	// Centre of UAV
	m_radarHit[1] = m_radarHit[0] - m_createGrid.m_randomX;						// Up
	m_radarHit[2] = m_radarHit[0] - (2 * m_createGrid.m_randomX);				// Up Up
	m_radarHit[3] = m_radarHit[0] + m_createGrid.m_randomX;						// Down
	m_radarHit[4] = m_radarHit[0] + (2 * m_createGrid.m_randomX);				// Down Down
	m_radarHit[5] = m_radarHit[0] - 1;											// Left
	m_radarHit[6] = m_radarHit[0] - 2;											// Left Left
	m_radarHit[7] = m_radarHit[0] + 1;											// Right
	m_radarHit[8] = m_radarHit[0] + 2;											// Right Right
	m_radarHit[9] = m_radarHit[0] - m_createGrid.m_randomX - 1;					// Up Left
	m_radarHit[10] = m_radarHit[0] - m_createGrid.m_randomX + 1;				// Up Right
	m_radarHit[11] = m_radarHit[0] + m_createGrid.m_randomX - 1;				// Down Left
	m_radarHit[12] = m_radarHit[0] + m_createGrid.m_randomX + 1;				// Down Right

	// Won't reveal if trying to exceed grid bounds (left)
	if (m_enterRadarX == 0)
	{
		m_radarHit[5] = m_radarHit[0];
		m_radarHit[6] = m_radarHit[0];
		m_radarHit[9] = m_radarHit[0];
		m_radarHit[11] = m_radarHit[0];
	}
	if (m_enterRadarX == 1)
	{
		m_radarHit[6] = m_radarHit[0];
	}
	// Won't reveal if trying to exceed grid bounds (right)
	if (m_enterRadarX == m_createGrid.m_randomX-1)
	{
		m_radarHit[7] = m_radarHit[0];
		m_radarHit[8] = m_radarHit[0];
		m_radarHit[10] = m_radarHit[0];
		m_radarHit[12] = m_radarHit[0];
	}
	if (m_enterRadarX == m_createGrid.m_randomX-2)
	{
		m_radarHit[8] = m_radarHit[0];
	}
	// Won't reveal if trying to exceed grid bounds (up)
	if (m_enterRadarY == 0)
	{
		m_radarHit[1] = m_radarHit[0];
		m_radarHit[2] = m_radarHit[0];
		m_radarHit[9] = m_radarHit[0];
		m_radarHit[10] = m_radarHit[0];
	}
	if (m_enterRadarY == 1)
	{
		m_radarHit[2] = m_radarHit[0];
	}
	// Won't reveal if trying to exceed grid bounds (up)
	if (m_enterRadarY == m_createGrid.m_randomY-1)
	{
		m_radarHit[3] = m_radarHit[0];
		m_radarHit[4] = m_radarHit[0];
		m_radarHit[11] = m_radarHit[0];
		m_radarHit[12] = m_radarHit[0];
	}
	if (m_enterRadarY == m_createGrid.m_randomY-2)
	{
		m_radarHit[4] = m_radarHit[0];
	}

	for (int i = 0; i < 13; ++i)
	{
		if (m_createGrid.m_playerGrid[ m_radarHit[i] ] == 1)
		{
			m_createGrid.m_playerGrid[ m_radarHit[i] ] = 4;
		}
		if (m_createGrid.m_playerGrid[ m_radarHit[i] ] == 0)
		{
			m_createGrid.m_playerGrid[ m_radarHit[i] ] = 5;
		}
	}
}

void Game::EnterXForRadar()
{

	ColourYellow;
	cout << "Enter the X co-ordinate for the UAV: ";
	m_enterRadarX = 0;
	ColourWhite;
	cin >> m_enterRadarX;
}

void Game::EnterYForRadar()
{
	ColourYellow;
	cout << "Enter the Y co-ordinate for the UAV: ";
	m_enterRadarY = 0;
	ColourWhite;
	cin >> m_enterRadarY;
}

void Game::ResetRadar()
{
	for (int i = 0; i < (m_createGrid.m_randomX * m_createGrid.m_randomY); ++i)
	{
		if (m_createGrid.m_playerGrid[i] == 4)
		{
			m_createGrid.m_playerGrid[i] = 1;
		}
		if (m_createGrid.m_playerGrid[i] == 5)
		{
			m_createGrid.m_playerGrid[i] = 0;
		}
	}
}

void Game::CheckInput()
{
	if ( cin.good() )
	{
	}
	else
	{
		cin.sync();
		cin.clear();
	}
}

void Game::EnterXForNuke()
{
	ColourGreen;
	cout << "Enter the X co-ordinate: ";
	m_enterX = 0;
	ColourWhite;
	cin >> m_enterX;
}

void Game::EnterYForNuke()
{
	ColourGreen;
	cout << "Enter the Y co-ordinate: ";
	m_enterY = 0;
	ColourWhite;
	cin >> m_enterY;
}

void Game::ConfirmPlayerNuke()
{
	// Player nuke missed! :(
	if (!m_playerNukeHit)
	{
		ColourCyan;
		cout << "Our nuke has missed." << endl << endl;
	}
	// Player nuke successful! Enemy city destroyed ^_^
	else if (m_playerNukeHit)
	{
		ColourGreen;
		string playerCityName = GenerateCity(3);
		m_playerDestroyedCityList.push_back( playerCityName );
		cout << "We have destroyed " << playerCityName << "!" << endl;
		m_playerPopList.push_back( GeneratePopulation(3) );
		cout << "Population: " << GeneratePopulation(3) << endl << endl;
	}
}

void Game::ConfirmBeauModeNuke()
{
	// All nukes have missed!
	if (!m_beauModeNukeA && !m_beauModeNukeB && !m_beauModeNukeC)
	{
		ColourCyan;
		cout << "The enemy nukes have missed." << endl << endl;
	}
	// One or more of the nukes have hit!
	if (m_beauModeNukeA)
	{
		ColourRed;
		string enemyCityName = GenerateCity(5);
		m_enemyDestroyedCityList.push_back( enemyCityName );
		cout << "The enemy has destroyed " << enemyCityName << "!" << endl;
		m_enemyPopList.push_back( GeneratePopulation(5) );
		cout << "Population: " << GeneratePopulation(5) << endl << endl;
				
		ColourYellow;
		cout << "Commander " << m_username << ", they destroyed one of our silos." << endl;
		cout << "We've lost a nuke!" << endl << endl;
		--m_numNukes;
	}
	if (m_beauModeNukeB)
	{
		ColourRed;
		string enemyCityName = GenerateCity(6);
		m_enemyDestroyedCityList.push_back( enemyCityName );
		cout << "The enemy has destroyed " << enemyCityName << "!" << endl;
		m_enemyPopList.push_back( GeneratePopulation(6) );
		cout << "Population: " << GeneratePopulation(6) << endl << endl;
				
		ColourYellow;
		cout << "Commander " << m_username << ", they destroyed one of our silos." << endl;
		cout << "We've lost a nuke!" << endl << endl;
		--m_numNukes;
	}
	if (m_beauModeNukeC)
	{
		ColourRed;
		string enemyCityName = GenerateCity(7);
		m_enemyDestroyedCityList.push_back( enemyCityName );
		cout << "The enemy has destroyed " << enemyCityName << "!" << endl;
		m_enemyPopList.push_back( GeneratePopulation(7) );
		cout << "Population: " << GeneratePopulation(7) << endl << endl;
		
		ColourYellow;
		cout << "Commander " << m_username << ", they destroyed one of our silos." << endl;
		cout << "We've lost a nuke!" << endl << endl;
		--m_numNukes;
	}
}

void Game::ConfirmEnemyNuke()
{
	// Enemy nuke failed! ^_^
	if (!m_enemyNukeHit)
	{
		ColourCyan;
		cout << "The enemy nuke has missed." << endl << endl;
	}
	// Enemy nuke successful! Player city destroyed :(
	else if (m_enemyNukeHit)
	{
		ColourRed;
		string enemyCityName = GenerateCity(5);
		m_enemyDestroyedCityList.push_back( enemyCityName );
		cout << "The enemy has destroyed " << enemyCityName << "!" << endl;
		m_enemyPopList.push_back( GeneratePopulation(5) );
		cout << "Population: " << GeneratePopulation(5) << endl << endl;
		
		if (m_username == "Faggot")
		{
			ColourWMagenta;
			cout << "Commander " << m_username << ", they destroyed one of our panty factory outlets." << endl;
			cout << "We've lost a nuke!" << endl << endl;
		}
		else
		{
			ColourYellow;
			cout << "Commander " << m_username << ", they destroyed one of our silos." << endl;
			cout << "We've lost a nuke!" << endl << endl;
		}
	}
}

void Game::CheckNumberOfNukes()
{
	if (m_numNukes > 1)
	{
		ColourWhite;
		cout << "We have ";
		ColourGreen;
		cout << m_numNukes;
		ColourWhite;
		cout << " nukes remaining." << endl << endl;
	}
	else if (m_numNukes == 1)
	{
		ColourWhite;
		cout << "We only have ";
		ColourGreen;
		cout << m_numNukes;
		ColourWhite;
		cout << " nuke remaining, Commander " << m_username << ". Make it count!" << endl << endl;
	}
}

void Game::CheckWinner()
{
	// Lose message:
	ColourWhite;
	if (m_playerScore < m_enemyScore)
	{
		cout << "I'm sorry, Commander " << m_username << ". We couldn't hold them off..." << endl << endl;
	}
	
	// Win message:
	else if (m_playerScore > m_enemyScore)
	{
		if (m_username == "Beau")
		{
			cout << "Congratulations, Commander " << m_username << "!" << endl;
			cout << "You're the best around, nothing's ever gonna keep you down!" << endl << endl;
		}
		else if (m_username == "Faggot")
		{
			ColourWMagenta;
			cout << "Congratulations, Sailor " << m_username << "! Panties for you!" << endl << endl;
		}
		else
		{
			cout << "Congratulations, Commander " << m_username << "! We are victorious!" << endl << endl;
		}
	}

	// Draw message:
	else if (m_playerScore == m_enemyScore)
	{
		cout << "Commander " << m_username << ", both sides have taken similar casualties..." << endl;
		cout << "We've ended in a draw." << endl << endl;
	}
}

string Game::GenerateCity(int x)
{
	if (m_cityList.size() == 0)									// Replenish cities when list is empty
	{
		m_cityList.push_back("Ausdell");
		m_cityList.push_back("Balshire");
		m_cityList.push_back("Baltihill");
		m_cityList.push_back("Baybury");
		m_cityList.push_back("Bowhill");
		m_cityList.push_back("Bradhurst");
		m_cityList.push_back("Brownstown");
		m_cityList.push_back("Butcott Springs");
		m_cityList.push_back("Calshire");
		m_cityList.push_back("Clearbank");
		m_cityList.push_back("Conde");
		m_cityList.push_back("Doverdale");
		m_cityList.push_back("East Bradhurst");
		m_cityList.push_back("Ellingmere");
		m_cityList.push_back("Fulmark");
		m_cityList.push_back("Galyn");
		m_cityList.push_back("Garshill");
		m_cityList.push_back("Glencaster");
		m_cityList.push_back("Grand Malmond");
		m_cityList.push_back("Greenster");
		m_cityList.push_back("Haland");
		m_cityList.push_back("Hamswell");
		m_cityList.push_back("Hamville");
		m_cityList.push_back("Indiancrest");
		m_cityList.push_back("Kanana");
		m_cityList.push_back("Little Ausmyra");
		m_cityList.push_back("Loganfield");
		m_cityList.push_back("Lyage");
		m_cityList.push_back("Madifield");
		m_cityList.push_back("Madison Gardens");
		m_cityList.push_back("Madiswell");
		m_cityList.push_back("Markerark");
		m_cityList.push_back("Mosshurst Village");
		m_cityList.push_back("Orchardtree");
		m_cityList.push_back("Palmore");
		m_cityList.push_back("Philboro");
		m_cityList.push_back("Pleasantmore");
		m_cityList.push_back("Ralton");
		m_cityList.push_back("Richlinev");
		m_cityList.push_back("Rivercrest Falls");
		m_cityList.push_back("Rockson");
		m_cityList.push_back("Roseboro");
		m_cityList.push_back("Stetbourne");
		m_cityList.push_back("Tamill");
		m_cityList.push_back("Troyville");
		m_cityList.push_back("Wardell Grove");
		m_cityList.push_back("West Lymore");
		m_cityList.push_back("Woldell");
		m_cityList.push_back("Woodcrest");
		m_cityList.push_back("Woolcott");
	}

	srand( unsigned int( time(NULL) * x ) );						// Seed random different for player and enemy

	int cityValue = rand() % m_cityList.size();						// Grabs a random city
	string cityHit = m_cityList[cityValue];

	m_cityList[cityValue] = m_cityList[m_cityList.size()-1];		// Replace called city with last city
	m_cityList.pop_back();											// Delete last city from vector

	return cityHit;
}

int Game::GeneratePopulation(int x)
{
	// Population value between 250,000 - 1,000,000
	srand( unsigned int( time(NULL) * x ) );
	
	int cityPop = ( ( (rand() % 751) + 250 ) * 1000 ) + ( (rand() % 1000) / 3 );

	return cityPop;
}