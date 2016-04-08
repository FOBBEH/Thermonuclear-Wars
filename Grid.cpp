
#include <iostream>
#include <time.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

#include "Grid.h"

/*Grid::Grid()
{
}

Grid::~Grid()
{
}*/

void Grid::InitialiseGrid()
{
	srand( unsigned int( time(NULL) ) );

	// Creating the random values for the grid -> X-axis and Y-axis
	m_randomX = ( rand() % 6 ) + 5;		// Generate X-value between 5-10
	m_randomY = ( rand() % 9 ) + 8;		// Generate Y-value between 8-16
	m_gridSize = m_randomX * m_randomY;

	m_playerGrid = new int[m_gridSize];
	m_enemyGrid = new int[m_gridSize];

	// Nullify playerGrid and enemyGrid: Empty spaces are set to 0
	for (int i = 0; i < m_gridSize; ++i)
	{
		m_playerGrid[i] = 0;
	}

	for (int i = 0; i < m_gridSize; ++i)
	{
		m_enemyGrid[i] = 0;
	}

	float m_numCitiesFloat = m_gridSize / 10.0f;
	m_numCities = ceil (m_numCitiesFloat);		// Round the float down to nearest integral value

	// City spaces are set to 1
	int gridSpace = 10;

	for (int i = 0; i <= m_numCities; i++)
	{
		// Every 10 (gridSpace) spaces a city is placed
		int cityCount = rand() % ((gridSpace * i) - (gridSpace * i - gridSpace)) + (gridSpace * i - gridSpace);
		
		m_playerGrid[cityCount] = 1;
	}

	for (int i = 0; i <= m_numCities; i++)
	{
		int cityCount = rand() % ((gridSpace * i) - (gridSpace * i - gridSpace)) + (gridSpace * i - gridSpace);
		
		m_enemyGrid[cityCount] = 1;
	}
}

void Grid::RenderGrid()
{
	m_playerGridRender = new char[m_gridSize];
	m_enemyGridRender = new char[m_gridSize];

	for (int i = 0; i < m_gridSize; ++i)
	{
		// Place characters in grid spaces
		switch ( m_playerGrid[i] )
		{
			case 0:
				m_playerGridRender[i] = ' ';	// Empty space
				break;
			case 1:
				m_playerGridRender[i] = ' ';	// City space (not revealed)
				break;
			case 2:
				m_playerGridRender[i] = '-';	// Nuke miss
				break;
			case 3:
				m_playerGridRender[i] = '*';	// Nuke hit
				break;
			case 4:
				m_playerGridRender[i] = 'C';	// Reveal city space for UAV
				break;
			case 5:
				m_playerGridRender[i] = '=';	// Reveal empty space for UAV
				break;
			default:
				break;
		}

		switch ( m_enemyGrid[i] )
		{
			case 0:
				m_enemyGridRender[i] = ' ';
				break;
			case 1:
				m_enemyGridRender[i] = 'C';
				break;
			case 2:
				m_enemyGridRender[i] = '-';
				break;
			case 3:
				m_enemyGridRender[i] = '*';
				break;
			default:
				break;
		}
	}
}

void Grid::DisplayGrid()
{
	int playerGridCount = 0, enemyGridCount = 0;

	// Print x co-ordinates (horizontal)
	for (int i = 0; i < m_randomX; i++)
	{
		// Colour co-ordinates:	CYAN
		ColourCyan;
		if (i == 0)
		{
			cout << "     " << i << "  ";
		}
		else
		{
			cout << i << "  ";
		}
	}
	cout << "                                " << endl << endl;

	// Print y co-ordinates (vertical)
	for (int i = 0; i < m_randomY; ++i)
	{
		if (i < 10)
		{
			// Colour co-ordinates:	CYAN
			ColourCyan;
			cout << "  " << i << " ";
		}
		else if (i >= 10)
		{
			ColourCyan;
			cout << " " << i << " ";
		}
		
		// Display player grid and render with new char
		for (int i = 0; i < m_randomX; ++i)
		{
			// Colour player grid (brackets): GREEN
			ColourGreen;
			cout << "[";
			if ((m_playerGridRender[playerGridCount] == '-') || (m_playerGridRender[playerGridCount] == '='))
			{
				// Colour empty/missed spaces: GREY
				ColourGrey;
				cout << m_playerGridRender[playerGridCount];
			}
			else if (m_playerGridRender[playerGridCount] == '*')
			{
				// Colour nuked cities: YELLOW
				ColourYellow;
				cout << m_playerGridRender[playerGridCount];
			}
			else
			{
				ColourWhite;
				cout << m_playerGridRender[playerGridCount];
			}
			ColourGreen;
			cout << "]";
			++playerGridCount;
		}

		ColourYellow;
		cout << "     |     "; // Space inbetween grids

		// Display enemy grid
		for (int i = 0; i < m_randomX; ++i)
		{
			// Colour enemy grid (brackets): RED
			ColourRed;
			cout << "[";
			if (m_enemyGridRender[enemyGridCount] == '-')
			{
				// Colour empty/missed spaces: GREY
				ColourGrey;
				cout << m_enemyGridRender[enemyGridCount];
			}
			else if (m_enemyGridRender[enemyGridCount] == '*')
			{
				// Colour nuked cities: YELLOW
				ColourYellow;
				cout << m_enemyGridRender[enemyGridCount];
			}
			else
			{
				ColourWhite;
				cout << m_enemyGridRender[enemyGridCount];
			}
			ColourRed;
			cout << "]";
			++enemyGridCount;
		}
		cout << endl;
	}
	cout << endl;
}

void Grid::DeleteAndResetArrays()
{
	delete [] m_playerGrid;
	delete [] m_enemyGrid;
	delete [] m_playerGridRender;
	delete [] m_enemyGridRender;
	
	m_playerGrid = NULL;
	m_enemyGrid = NULL;
	m_playerGridRender = NULL;
	m_enemyGridRender = NULL;
}