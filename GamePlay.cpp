
#include <iostream>
#include <time.h>
#include <iomanip>
#include <Windows.h>

#include "Game.h"
#include "GameSettings.h"

void Game::PlayTheGame()
{
	bool continuePlay = true;
	bool beauMode = false;
	m_turns = 0;
	m_radarActive = false;

	SetWindowSize();
	DisplayTitle();
	
	ColourCyan;
	cout << setw(52) << "[COMMUNICATIONS NOW ONLINE]" << endl << endl;

	// Enter name
	ColourWhite;
	cout << "Please type in your name: ";
	getline (cin, m_username);

	if (m_username == "Beau")
	{
		beauMode = true;
	}

	while (continuePlay)
	{
		// Begin the game
		m_createGrid.InitialiseGrid();
		DirtyRender();
		DisplayTitle();
		m_createGrid.RenderGrid();
		m_createGrid.DisplayGrid();
		
		ColourCyan;
		cout << setw(48) << "[BEGIN TRANSMISSION]" << endl << endl;

		ColourWhite;
		if (m_username == "Beau" && beauMode)
		{
			cout << "Commander, our enemy has launched ";
			ColourRed;
			cout << "BEAU MODE! GAME OVER MAN GAME OVER!" << endl << endl;
		}
		else if (m_username == "Faggot")
		{
			ColourWMagenta;
			cout << "Hiya, Commander " << m_username << "!" << endl;
			cout << "They've raided our panty factories, our secret's out!" << endl << endl;
		}
		else
		{
			cout << "Welcome, Commander " << m_username << "." << endl;
			cout << "Our enemy has launched an all out offensive, we must strike back!" << endl << endl;
		}

		// Take your turn
		bool gameOver = false;
		m_numNukes = 5 + m_createGrid.m_numCities;
		
		while (!gameOver && m_numNukes)
		{
			// Radar online (every 5 turns)
			if (beauMode && m_radarActive)
			{
				ColourYellow;
				cout << "Commander " << m_username << ", our enemy has disabled our UAV! WE'RE DOOMED!" << endl << endl;
			}
			else if (m_radarActive)
			{
				ColourCyan;
				cout << "Commander " << m_username << ", our UAV is now online." << endl << endl;
				EnterXForRadar();
				CheckInput();
			
				// Co-ordinate cannot exceed x-axis bounds
				if (m_enterRadarX < 0 || m_enterRadarX > m_createGrid.m_randomX-1)
				{
					cout << "Commander " << m_username << ", that is not a valid co-ordinate!" << endl << endl;
					continue;
				}
			
				EnterYForRadar();
				CheckInput();

				// Co-ordinate cannot exceed y-axis bounds
				if (m_enterRadarY < 0 || m_enterRadarY > m_createGrid.m_randomY-1)
				{
					cout << "Commander " << m_username << ", that is not a valid co-ordinate!" << endl << endl;
					continue;
				}
				
				DirtyRender();
				DisplayTitle();
				UseRadar();
				m_createGrid.RenderGrid();
				m_createGrid.DisplayGrid();
				ResetRadar();

				ColourYellow;
				cout << "Commander " << m_username << ", our UAV has revealed the area." << endl << endl;
					
				m_radarActive = false;
			}

			// Enter co-ordinates
			EnterXForNuke();
			CheckInput();

			// Co-ordinate cannot exceed x-axis bounds
			if (m_enterX < 0 || m_enterX > m_createGrid.m_randomX-1)
			{
				ColourYellow;
				cout << endl << "Commander " << m_username << ", that is not a valid co-ordinate!" << endl << endl;
				continue;
			}
			
			EnterYForNuke();
			CheckInput();

			// Co-ordinate cannot exceed y-axis bounds
			if (m_enterY < 0 || m_enterY > m_createGrid.m_randomY-1)
			{
				ColourYellow;
				cout << endl << "Commander " << m_username << ", that is not a valid co-ordinate!" << endl << endl;
				continue;
			}

			// To get the array number for the co-ordinate
			int gridHit = (m_enterY * m_createGrid.m_randomX) + m_enterX;
			
			// Cannot target same co-ordinate
			if (m_createGrid.m_playerGrid[gridHit] == 2 || m_createGrid.m_playerGrid[gridHit] == 3)
			{
				ColourYellow;
				cout << endl << "Commander " << m_username << ", you have already launched a nuke there! Try again!" << endl << endl;
				continue;
			}

			// Did the player's nuke hit?
			m_playerNukeHit = false;
			
			// Nuke landed in empty space:
			if (m_createGrid.m_playerGrid[gridHit] == 0)	
			{
				m_createGrid.m_playerGrid[gridHit] = 2;
			}
			// Nuke landed in city space OR UAV-revealed city space:
			if (m_createGrid.m_playerGrid[gridHit] == 1 || m_createGrid.m_playerGrid[gridHit] == 4)
			{
				m_createGrid.m_playerGrid[gridHit] = 3;
				m_playerNukeHit = true;
			}

			// Did the enemy's nuke hit?
			m_enemyTurn = true;
			m_enemyNukeHit = false;

			while (m_enemyTurn)
			{
				srand( unsigned int( time(NULL) ) );

				// Picks random spot on the grid to attack
				if (beauMode)
				{
					m_beauModeNukeA = false;
					m_beauModeNukeB = false;
					m_beauModeNukeC = false;

					while (m_enemyTurn)
					{
						int beauModeY = rand() % (m_createGrid.m_randomY);			// Access to all Y co-ordinates
						int beauModeX = (rand() % (m_createGrid.m_randomX-3)) + 1;	// Access from 2nd to 2nd last X co-ordinates
						int beauModeGridHitA = (m_createGrid.m_randomX * beauModeY) + beauModeX;
						int beauModeGridHitB = beauModeGridHitA - 1;
						int beauModeGridHitC = beauModeGridHitA + 1;

						if (m_createGrid.m_enemyGrid[beauModeGridHitB] == 2 || m_createGrid.m_enemyGrid[beauModeGridHitB] == 3 ||
							m_createGrid.m_enemyGrid[beauModeGridHitC] == 2 || m_createGrid.m_enemyGrid[beauModeGridHitC] == 3)
						{
							continue;
						}
						else if (m_createGrid.m_enemyGrid[beauModeGridHitA] == 0)
						{
							m_createGrid.m_enemyGrid[beauModeGridHitA] = 2;
						}
						else if (m_createGrid.m_enemyGrid[beauModeGridHitA] == 1)
						{
							m_createGrid.m_enemyGrid[beauModeGridHitA] = 3;
							m_beauModeNukeA = true;
						}
						if (m_createGrid.m_enemyGrid[beauModeGridHitB] == 0)
						{
							m_createGrid.m_enemyGrid[beauModeGridHitB] = 2;
						}
						else if (m_createGrid.m_enemyGrid[beauModeGridHitB] == 1)
						{
							m_createGrid.m_enemyGrid[beauModeGridHitB] = 3;
							m_beauModeNukeB = true;
						}
						if (m_createGrid.m_enemyGrid[beauModeGridHitC] == 0)
						{
							m_createGrid.m_enemyGrid[beauModeGridHitC] = 2;
						}
						else if (m_createGrid.m_enemyGrid[beauModeGridHitC] == 1)
						{
							m_createGrid.m_enemyGrid[beauModeGridHitC] = 3;
							m_beauModeNukeC = true;
						}
						m_enemyTurn = false;
					}
				}
				else
				{
					while (m_enemyTurn)
					{
						int enemyGridHit = rand() % (m_createGrid.m_randomX * m_createGrid.m_randomY);
						
						if (m_createGrid.m_enemyGrid[enemyGridHit] == 2 || m_createGrid.m_enemyGrid[enemyGridHit] == 3)
						{
							continue;
						}
						else if (m_createGrid.m_enemyGrid[enemyGridHit] == 0)
						{
							m_createGrid.m_enemyGrid[enemyGridHit] = 2;
						}
						else if (m_createGrid.m_enemyGrid[enemyGridHit] == 1)
						{
							m_createGrid.m_enemyGrid[enemyGridHit] = 3;
							m_enemyNukeHit = true;
						}
						m_enemyTurn = false;
					}
				}
			}

			DirtyRender();
			DisplayTitle();
			m_createGrid.RenderGrid();
			m_createGrid.DisplayGrid();

			ConfirmPlayerNuke();

			if (beauMode)
			{
				ConfirmBeauModeNuke();
			}
			else
			{
				ConfirmEnemyNuke();
			}

			--m_numNukes;
			++m_turns;

			if ((m_turns % 5 == 0) && (m_turns != 0))
			{
				m_radarActive = true;
			}

			if (m_numNukes < 0)
			{
				m_numNukes = 0;
			}

			CheckNumberOfNukes();
		}
		
		ColourYellow;
		cout << "Commander " << m_username << ", we've run out of nukes." << endl << endl;
		
		ColourWhite;
		system("PAUSE");
		DirtyRender();
		DisplayTitle();
		m_createGrid.DisplayGrid();

		// Player score total
		m_playerScore = 0;
		for (int i = 0; i < m_playerPopList.size(); ++i)
		{
			m_playerScore = m_playerScore + m_playerPopList[i];
		}
		// Enemy score total
		m_enemyScore = 0;
		for (int i = 0; i < m_enemyPopList.size(); ++i)
		{
			m_enemyScore = m_enemyScore + m_enemyPopList[i];
		}

		// List of cities nuked:
		ColourWhite;
		cout << "The following cities were destroyed:" << endl << endl;
		ColourGreen;
		for (int i = 0; i < m_playerDestroyedCityList.size(); ++i)
		{
			cout << setw(20) << m_playerDestroyedCityList[i] << "     Population: " << m_playerPopList[i] << endl;
		}
		cout << endl << setw(27) << m_username << "'s score: " << m_playerScore << endl << endl;

		ColourRed;
		for (int i = 0; i < m_enemyDestroyedCityList.size(); ++i)
		{
			cout << setw(20) << m_enemyDestroyedCityList[i] << "     Population: " << m_enemyPopList[i] << endl;
		}
		cout << endl << setw(37) << "Opponent's score: " << m_enemyScore << endl << endl;

		CheckWinner();

		// Replay (with new grid)
		string answer;

		ColourWhite;
		cout << "Do you wish to continue, Commander " << m_username << "? (y/n)" << endl;
		cin >> answer;
		CheckInput();

		if (answer == "y")
		{
			continuePlay = true;

			// Reset everything for new game
			system("CLS");							// Cannot use DirtyRender incase grid size changes

			m_turns = 0;
			m_radarActive = false;

			m_playerDestroyedCityList.clear();
			m_playerPopList.clear();
			m_enemyDestroyedCityList.clear();
			m_enemyPopList.clear();
			m_cityList.resize(0);
		}
		else
		{
			continuePlay = false;
			gameOver = true;
			
			DirtyRender();
			DisplayTitle();
			m_createGrid.DisplayGrid();
			//m_createGrid.DeleteAndResetArrays();
			
			ColourWhite;
			cout << "Farewell, Commander " << m_username << ". Till next time." << endl << endl;
			ColourCyan;
			cout << setw(47) << "[END TRANSMISSION]" << endl << endl;
			
			cin.ignore();
			cin.get();
		}
	}
}